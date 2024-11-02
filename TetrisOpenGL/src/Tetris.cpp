#include <Engine/Color.hpp>
#include <Engine/EngineEnums.hpp>

#include <Tetris/Cube.hpp>
#include <Tetris/JsonWrapper.hpp>
#include <Tetris/TetriminoCreator.hpp>
#include <Tetris/TetriminoCube.hpp>
#include <Tetris/TetriminoCubeGroup.hpp>
#include <Tetris/Tetris.hpp>

#include <algorithm>
#include <chrono>
#include <thread>

//---------------------------------------------------------------

const char* Tetris::s_name = "TetrisOpenGL";

//---------------------------------------------------------------

Tetris::Tetris()
    : Game(3200, 1800, "Tetris OpenGL")
    , m_uiElementColor(30, 30, 30)
    , m_uiElementColorOnHover(80, 80, 80)
    , m_uiElementTextColor(200, 200, 200)
    , m_uiElementBorderColor(10, 10, 10)
    , m_targetFPS(150)
    , m_score(0)
    , m_scoreCombo(1)
    , m_playGame(false)
    , m_exitClicked(false)
{
    m_jsonWrapper.LoadFromFile();

    m_guiManager.AddFunction(MenuGui());
    m_guiManager.AddFunction(ScoreboardGui());
    m_guiManager.AddFunction(GameScoreGui());
    m_guiManager.AddFunction(SettingsGui());
    m_guiManager.AddFunction(SaveScoreGui());
}

//---------------------------------------------------------------

void Tetris::AddCube()
{
    TetriminoCreator::Create(m_cubeGroup, m_cubes, m_scaleFactorX, m_scaleFactorY);
}

//---------------------------------------------------------------

void Tetris::CheckForRowToDelete()
{
    // Flag to track if points were added
    bool pointsAdded = false;

    // Infinite loop to continuously check for filled rows
    while (true)
    {
        // Iterate over the y-coordinates of the game board
        for (int yCoord = -10; yCoord <= 10; yCoord++)
        {
            bool rowEmpty = true;
            bool columnEmpty = false;

            // Check each cell in the current row
            for (int xCoord = -5; xCoord <= 5; xCoord++)
            {
                bool cubeFound = false;

                // Iterate over all cubes to find if any occupy the current cell
                for (const auto& cube : m_cubes)
                {
                    if (cube->IsStatic())
                        continue;

                    const auto tetriminoCube = std::dynamic_pointer_cast<TetriminoCube>(cube);
                    if (tetriminoCube->GetYLocation() == yCoord && tetriminoCube->GetXLocation() == xCoord)
                    {
                        // Cell is not empty
                        rowEmpty = false;
                        cubeFound = true;
                    }
                }
                if (!cubeFound)
                    columnEmpty = true;
            }

            // If the row is empty, reset combo (if points were added) and return
            if (rowEmpty)
            {
                if (pointsAdded)
                    m_scoreCombo = 1; // Reset combo if points were added
                return;
            }

            // If the column is empty, continue to the next row
            if (columnEmpty)
                continue;

            // Collect cubes from the filled row for deletion
            std::vector<long long> indexToErase;
            indexToErase.reserve(11);
            for (const auto& cube : m_cubes)
            {
                if (cube->IsStatic())
                    continue;

                const auto tetriminoCube = std::dynamic_pointer_cast<TetriminoCube>(cube);
                if (tetriminoCube->GetYLocation() == yCoord)
                {
                    // Store cube index for deletion and cube pointers for deletion
                    const long long index = std::ranges::find(m_cubes, cube) - m_cubes.begin();
                    indexToErase.emplace_back(index);
                }
            }

            // Sort indices in descending order for correct deletion
            std::ranges::sort(indexToErase, std::ranges::greater());
            for (int i = 0; i < 11; i++)
                m_cubes.erase(m_cubes.begin() + indexToErase[i]); // Remove cube from game board

            // Update score and set pointsAdded flag
            AddScore(); // Increment score
            pointsAdded = true;
            ++yCoord; // Move to the next row

            // Move cubes above the deleted row down
            std::vector<std::shared_ptr<TetriminoCube>> movableCubes;
            for (const auto& entity : m_cubes)
            {
                if (entity->IsStatic())
                    continue;

                const auto cube = std::dynamic_pointer_cast<TetriminoCube>(entity);
                if (cube->GetYLocation() >= yCoord)
                {
                    cube->MoveForce(m_scaleFactorY); // Move cube down
                    movableCubes.emplace_back(cube); // Add cube to movable cubes list
                }
            }

            // Handle cube movement
            bool cubeMoved = true;
            while (cubeMoved)
            {
                cubeMoved = false;
                bool cubeInRow = true;
                if (yCoord > -9)
                    --yCoord;
                for (int i = yCoord; i <= 10 && cubeInRow; i++)
                {
                    cubeInRow = false;
                    for (const auto& movableCube : movableCubes)
                    {
                        if (movableCube->GetYLocation() != i)
                            continue;

                        cubeInRow = true;
                        bool shouldBeMovable = true;
                        for (const auto& entity : m_cubes)
                        {
                            if (entity->IsStatic())
                                continue;

                            const auto cube = std::dynamic_pointer_cast<TetriminoCube>(entity);

                            if (cube->GetXLocation() == movableCube->GetXLocation() &&
                                cube->GetYLocation() == movableCube->GetYLocation() - 1)
                            {
                                shouldBeMovable = false;
                                break;
                            }
                        }
                        if (shouldBeMovable)
                        {
                            movableCube->MoveForce(m_scaleFactorY); // Move cube down
                            cubeMoved = true;
                        }
                    }
                }
            }
            break; // Exit the loop after processing the row
        }
    }
}

//---------------------------------------------------------------

void Tetris::CheckPressedKey(const Key keyPressed, const double& scaleFactor)
{
    if (!Game::CheckPressedKey(keyPressed))
        return;

    switch (keyPressed)
    {
        case Key::UP:
        case Key::DOWN:
        case Key::LEFT:
        case Key::RIGHT:
        {
            m_cubeGroup.MoveCubes(m_cubes, scaleFactor, keyPressed);

            if (m_cubeGroup.ShouldBeMovable(m_cubes))
                return;

            m_cubeGroup.SetMove(false);
            m_cubeGroup.ResetCubes();
            CheckForRowToDelete();
            TetriminoCreator::Create(m_cubeGroup, m_cubes, m_scaleFactorX, m_scaleFactorY);
            break;
        }
        case Key::ROTATE:
        {
            TetriminoCreator::RotateIfPossible(m_cubes, m_cubeGroup, m_scaleFactorX, m_scaleFactorY);
            break;
        }
        case Key::DEBUG_KEY_1:
        {
#ifdef _DEBUG
            m_cubeGroup.SetMove(false);
            m_cubeGroup.ResetCubes();
            TetriminoCreator::Create(m_cubeGroup, m_cubes, m_scaleFactorX, m_scaleFactorY);
#endif
            break;
        }
        case Key::ESC:
        {
            m_guiManager.PopFunctionId();
            if (m_guiManager.CurrentFunctionId() == 2)
                m_playGame = true;
            else
                m_playGame = false;

            break;
        }
    }
}

//---------------------------------------------------------------

void Tetris::CreateBorder()
{
    m_cubes = std::vector<std::shared_ptr<Cube>>();
    // Reserve std::vector, so the array is not going to expand during runtime
    // Border - 13 cubes
    // Max possible cube entities from tetrimino - 11 X 21 -> 231 (11 X 21 is the board size)
    // Total 238 cubes (reserve 240 to have some extra space just in case)
    // If, std::vector will expand over 240, this could mean potential memory leak
    m_cubes.reserve(240);

    std::vector<double> positions;
    positions.reserve(8);

    // Bottom left cube
    positions.insert(positions.end(), { -6.5, -11.5, -5.5, -11.5, -6.5, -10.5, -5.5, -10.5 });
    m_borderCubes[0] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY);

    // Bottom bar
    positions.clear();
    positions.insert(positions.end(), { -4.5, -11.5, 4.5, -11.5, -4.5, -10.5, 4.5, -10.5 });
    auto cube = Cube(true, positions, m_scaleFactorX, m_scaleFactorY, Settings::GetMiddleColor());
    cube.RotateClockwise();
    m_borderCubes[1] = cube;

    // Bottom bar - left part
    positions.clear();
    positions.insert(positions.end(), { -5.5, -11.5, -4.5, -11.5, -5.5, -10.5, -4.5, -10.5 });
    cube = Cube(true, positions, m_scaleFactorX, m_scaleFactorY, Settings::GetTopColor());
    cube.RotateClockwise();
    cube.Mirror();
    m_borderCubes[2] = cube;

    // Bottom bar - right
    positions.clear();
    positions.insert(positions.end(), { 4.5, -11.5, 5.5, -11.5, 4.5, -10.5, 5.5, -10.5 });
    cube = Cube(true, positions, m_scaleFactorX, m_scaleFactorY, Settings::GetBottomColor());
    cube.RotateClockwise();
    cube.Mirror();
    m_borderCubes[3] = cube;

    // Bottom right cube
    positions.clear();
    positions.insert(positions.end(), { 5.5, -11.5, 6.5, -11.5, 5.5, -10.5, 6.5, -10.5 });
    m_borderCubes[4] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY);

    // Top left cube
    positions.clear();
    positions.insert(positions.end(), { -6.5, 10.5, -5.5, 10.5, -6.5, 11.5, -5.5, 11.5 });
    m_borderCubes[5] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY);

    // Top right cube
    positions.clear();
    positions.insert(positions.end(), { 5.5, 10.5, 6.5, 10.5, 5.5, 11.5, 6.5, 11.5 });
    m_borderCubes[6] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY);

    // Left bar
    positions.clear();
    positions.insert(positions.end(), { -6.5, -9.5, -5.5, -9.5, -6.5, 9.5, -5.5, 9.5 });
    m_borderCubes[7] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY, Settings::GetMiddleColor());
    // m_cubes.emplace_back(

    // Left bar - top part
    positions.clear();
    positions.insert(positions.end(), { -6.5, 9.5, -5.5, 9.5, -6.5, 10.5, -5.5, 10.5 });
    m_borderCubes[8] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY, Settings::GetTopColor());

    // Left bar - bottom part
    positions.clear();
    positions.insert(positions.end(), { -6.5, -9.5, -5.5, -9.5, -6.5, -10.5, -5.5, -10.5 });
    m_borderCubes[9] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY, Settings::GetBottomColor());

    // Right bar
    positions.clear();
    positions.insert(positions.end(), { 5.5, -9.5, 6.5, -9.5, 5.5, 9.5, 6.5, 9.5 });
    m_borderCubes[10] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY, Settings::GetMiddleColor());

    // Right bar - top part
    positions.clear();
    positions.insert(positions.end(), { 5.5, 10.5, 6.5, 10.5, 5.5, 9.5, 6.5, 9.5 });
    m_borderCubes[11] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY, Settings::GetTopColor());

    // Right bar - bottom part
    positions.clear();
    positions.insert(positions.end(), { 5.5, -10.5, 6.5, -10.5, 5.5, -9.5, 6.5, -9.5 });
    m_borderCubes[12] = Cube(true, positions, m_scaleFactorX, m_scaleFactorY, Settings::GetBottomColor());
}

//---------------------------------------------------------------

void Tetris::LimitFPS() const
{
    static std::chrono::time_point lastFrameTime(std::chrono::high_resolution_clock::now());
    const std::chrono::milliseconds frameDuration(1000 / m_targetFPS);
    const std::chrono::time_point currentTime(std::chrono::high_resolution_clock::now());
    const auto elapsedTime(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrameTime));
    const std::chrono::duration sleepDuration(frameDuration - elapsedTime);
    if (sleepDuration > std::chrono::milliseconds::zero())
        std::this_thread::sleep_for(sleepDuration);

    lastFrameTime = std::chrono::high_resolution_clock::now();
}

//---------------------------------------------------------------

std::function<void()> Tetris::MenuGui()
{
    return [this]
    {
        static constexpr char m_scoreboardText[11] = "Scoreboard";
        static constexpr char m_exitText[5] = "Exit";
        static constexpr char m_playText[5] = "Play";
        static constexpr char m_settingsText[9] = "Settings";

        m_guiManager.CreateWindow(static_cast<float>(m_width), static_cast<float>(m_height), s_name);

        m_guiManager.CreateButton(
            250.0f,
            100.0f,
            1.5f,
            m_playText,
            [this]
            {
                m_playGame = true;
                m_guiManager.PushFunctionId(2);
            },
            m_uiElementColor,
            m_uiElementColorOnHover,
            m_uiElementTextColor,
            m_uiElementBorderColor,
            true);

        m_guiManager.CreateButton(
            250.0f,
            200.0f,
            1.5f,
            m_scoreboardText,
            [this] { m_guiManager.PushFunctionId(1); },
            m_uiElementColor,
            m_uiElementColorOnHover,
            m_uiElementTextColor,
            m_uiElementBorderColor,
            true);

        m_guiManager.CreateButton(
            250.0f,
            300.0f,
            1.5f,
            m_settingsText,
            [this] { m_guiManager.PushFunctionId(3); },
            m_uiElementColor,
            m_uiElementColorOnHover,
            m_uiElementTextColor,
            m_uiElementBorderColor,
            true);

        m_guiManager.CreateButton(
            250.0f,
            400.0f,
            1.5f,
            m_exitText,
            [this] { m_exitClicked = true; },
            m_uiElementColor,
            m_uiElementColorOnHover,
            m_uiElementTextColor,
            m_uiElementBorderColor,
            true);
    };
}

//---------------------------------------------------------------

std::function<void()> Tetris::ScoreboardGui()
{
    return [this]
    {
        m_guiManager.CreateWindow(static_cast<float>(m_width), static_cast<float>(m_height), s_name);

        const std::vector<Score>* scores = m_jsonWrapper.GetScores();
        for (size_t i = 0; i < scores->size() && i < 10; ++i)
        {
            std::string text = scores->at(i).playerName + " " + std::to_string(scores->at(i).score);
            const Vector2 labelSize = GuiManager::CalculateTextSize(text.c_str());
            m_guiManager.CreateLabel(labelSize.X(), 100.0f + 50.0f * static_cast<float>(i), text.c_str(), 0.0f, true);
        }
    };
}

//---------------------------------------------------------------

std::function<void()> Tetris::SettingsGui()
{
    return [this]
    {
        m_guiManager.CreateWindow(static_cast<float>(m_width), static_cast<float>(m_height), s_name);

        constexpr char settingsText[9] = "Settings";
        const Vector2 labelSize = GuiManager::CalculateTextSize(settingsText);
        m_guiManager.CreateLabel(labelSize.X(), 100.0f, settingsText, 0.0f, true);

        std::vector<const char*> items;
        items.reserve(4);
        items.insert(items.end(), { "Turquoise", "Yellow", "Lime", "Red" });

        m_guiManager.CreateGap(0.0f, 20.0f);

        m_guiManager.CreateDropDown(
            items,
            [this](auto item)
            {
                for (const auto& cube : m_cubes)
                    cube->SetImageOffset(4 * item);

                for (auto& cube : m_borderCubes)
                    cube.SetImageOffset(4 * item);

                Settings::SetImageOffset(4 * item);
            },
            1.5f,
            300.0f,
            m_uiElementColor,
            m_uiElementColorOnHover,
            m_uiElementTextColor,
            m_uiElementBorderColor,
            "Cube Color");
    };
}

//---------------------------------------------------------------

std::function<void()> Tetris::GameScoreGui()
{
    return [this]
    {
        constexpr char m_scoreText[8] = "Score: ";
        constexpr char m_saveScore[11] = "Save Score";

        m_guiManager.CreateWindow(static_cast<float>(m_width) / 3, static_cast<float>(m_height), s_name);

        m_guiManager.CreateLabel(10.0f, 0.0f, m_scoreText, 10.0f);

        const Vector2 labelSize = GuiManager::CalculateTextSize(m_scoreText);
        GuiManager::CreateLabel(5.0f + labelSize.X(), m_score);

        m_guiManager.CreateButton(
            10.0f,
            50.0f,
            1.5f,
            m_saveScore,
            [this]
            {
                m_playGame = false;
                m_guiManager.PushFunctionId(4);
            },
            m_uiElementColor,
            m_uiElementColorOnHover,
            m_uiElementTextColor,
            m_uiElementBorderColor);
    };
}

//---------------------------------------------------------------

std::function<void()> Tetris::SaveScoreGui()
{
    return [this]
    {
        constexpr char m_saveScore[11] = "Save Score";
        static char nameBuffer[21] = "";

        m_guiManager.CreateWindow(static_cast<float>(m_width), static_cast<float>(m_height), s_name);

        m_guiManager.CreateTextInput(
            700.0f,
            100.0f,
            nameBuffer,
            1.5f,
            m_uiElementColor,
            m_uiElementTextColor,
            m_uiElementBorderColor,
            true);

        m_guiManager.CreateButton(
            250.0f,
            200.0f,
            1.5f,
            m_saveScore,
            [this]
            {
                if (m_score != 0)
                {
                    m_jsonWrapper.SaveToFile(nameBuffer, m_score);
                    ResetGame();
                }

                memset(nameBuffer, 0, sizeof(nameBuffer));
                m_playGame = true;
                m_guiManager.PopFunctionId();
            },
            m_uiElementColor,
            m_uiElementColorOnHover,
            m_uiElementTextColor,
            m_uiElementBorderColor,
            true);
    };
}

//---------------------------------------------------------------

void Tetris::AddScore()
{
    m_score += m_scoreCombo * 100;
    ++m_scoreCombo;
}

//---------------------------------------------------------------

void Tetris::ResetGame()
{
    m_score = 0;
    m_scoreCombo = 0;
    m_cubeGroup.ResetCubes();

    m_cubes.clear();

    TetriminoCreator::Create(m_cubeGroup, m_cubes, m_scaleFactorX, m_scaleFactorY);
}

//---------------------------------------------------------------

void Tetris::Play()
{
    Tetris tetris;
    tetris.CreateBorder();
    tetris.AddCube();
    tetris.Loop();
}

//---------------------------------------------------------------

bool Tetris::InternalLoop()
{
    if (m_exitClicked)
        return true;

    m_guiManager.Loop();

    if (CheckTime())
        CheckPressedKey(Key::ESC);

    if (m_playGame)
    {
        for (const auto& cube : m_cubes)
            DrawSquare(cube);

        for (const auto& cube : m_borderCubes)
            DrawSquare(cube);

        if (CheckTime())
        {
            CheckPressedKey(Key::DOWN, m_scaleFactorY);
            CheckPressedKey(Key::UP, m_scaleFactorY);
            CheckPressedKey(Key::LEFT, m_scaleFactorX);
            CheckPressedKey(Key::RIGHT, m_scaleFactorX);
            CheckPressedKey(Key::ROTATE);

#ifdef _DEBUG // Extra feature for debug - L key is creating new TetriminoCube
            CheckPressedKey(Key::DEBUG_KEY_1);
#endif
        }
    }

    LimitFPS();
    return false;
}

//---------------------------------------------------------------
