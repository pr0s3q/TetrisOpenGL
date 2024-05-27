#include <algorithm>
#include <chrono>
#include <thread>

#include "Cube.h"
#include "EngineEnums.h"
#include "HelperDefinitions.h"
#include "ImGuiWrapper.h"
#include "TetriminoCreator.h"
#include "TetriminoCube.h"
#include "TetriminoCubeGroup.h"
#include "Tetris.h"

//---------------------------------------------------------------

const double Tetris::s_dtFactor = 0.1;

//---------------------------------------------------------------

Tetris::Tetris()
    : Game(3200, 1800, "Tetris OpenGL")
    , m_targetFPS(150)
{
    m_ImGuiWrapper = std::make_shared<ImGuiWrapper>(InitImGui(), m_width, m_height);

    m_cubeGroup = std::make_shared<TetriminoCubeGroup>();
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
                    m_ImGuiWrapper->ResetCombo(); // Reset combo if points were added
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
            m_ImGuiWrapper->AddScore(); // Increment score
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
            m_cubeGroup->MoveCubes(m_cubes, scaleFactor, keyPressed);

            if (m_cubeGroup->ShouldBeMovable(m_cubes))
                return;

            m_cubeGroup->SetMove(false);
            m_cubeGroup->ResetCubes();
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
            m_cubeGroup->SetMove(false);
            m_cubeGroup->ResetCubes();
            TetriminoCreator::Create(m_cubeGroup, m_cubes, m_scaleFactorX, m_scaleFactorY);
            break;
        }
        case Key::ESC:
        {
            m_ImGuiWrapper->ShowMenu();
            break;
        }
    }
}

//---------------------------------------------------------------

void Tetris::CreateBorder()
{
    m_cubes = std::vector<std::shared_ptr<Cube>>();
    // Reserve std::vector, so the array is not going to expand during runtime
    // Border - 7 cubes
    // Max possible cube entities from tetrimino - 11 X 21 -> 231 (11 X 21 is the board size)
    // Total 238 cubes (reserve 250 to have some extra space just in case)
    // If, std::vector will expand over 250, this could mean potential memory leak
    m_cubes.reserve(250);

    std::vector<double> positions;
    positions.reserve(8);
    positions.insert(positions.end(), { -6.5, -11.5, -5.5, -11.5, -6.5, -10.5, -5.5, -10.5 });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 0.0f, 1.0f, 0.0f, 1.0f });

    m_cubes.emplace_back(std::make_shared<Cube>(true, positions, colors, m_scaleFactorX, m_scaleFactorY));

    positions.clear();
    positions.insert(positions.end(), { -5.5, -11.5, 5.5, -11.5, -5.5, -10.5, 5.5, -10.5 });

    m_cubes.emplace_back(std::make_shared<Cube>(true, positions, colors, m_scaleFactorX, m_scaleFactorY, BAR_11_COLOR));

    positions.clear();
    positions.insert(positions.end(), { 5.5, -11.5, 6.5, -11.5, 5.5, -10.5, 6.5, -10.5 });

    m_cubes.emplace_back(std::make_shared<Cube>(true, positions, colors, m_scaleFactorX, m_scaleFactorY));

    positions.clear();
    positions.insert(positions.end(), { -6.5, 10.5, -5.5, 10.5, -6.5, 11.5, -5.5, 11.5 });

    m_cubes.emplace_back(std::make_shared<Cube>(true, positions, colors, m_scaleFactorX, m_scaleFactorY));

    positions.clear();
    positions.insert(positions.end(), { 5.5, 10.5, 6.5, 10.5, 5.5, 11.5, 6.5, 11.5 });

    m_cubes.emplace_back(std::make_shared<Cube>(true, positions, colors, m_scaleFactorX, m_scaleFactorY));

    positions.clear();
    positions.insert(positions.end(), { -6.5, -10.5, -5.5, -10.5, -6.5, 10.5, -5.5, 10.5 });

    m_cubes.emplace_back(std::make_shared<Cube>(true, positions, colors, m_scaleFactorX, m_scaleFactorY, BAR_21_COLOR));

    positions.clear();
    positions.insert(positions.end(), { 5.5, -10.5, 6.5, -10.5, 5.5, 10.5, 6.5, 10.5 });

    m_cubes.emplace_back(std::make_shared<Cube>(true, positions, colors, m_scaleFactorX, m_scaleFactorY, BAR_21_COLOR));
}

//---------------------------------------------------------------

void Tetris::LimitFPS() const
{
    static std::chrono::time_point lastFrameTime(std::chrono::high_resolution_clock::now());
    const std::chrono::milliseconds frameDuration(1000 / m_targetFPS);
    const std::chrono::time_point currentTime(std::chrono::high_resolution_clock::now());
    const std::chrono::duration elapsedTime(
        std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrameTime));
    const std::chrono::duration sleepDuration(frameDuration - elapsedTime);
    if (sleepDuration > std::chrono::milliseconds::zero())
        std::this_thread::sleep_for(sleepDuration);

    lastFrameTime = std::chrono::high_resolution_clock::now();
}

//---------------------------------------------------------------

void Tetris::Init()
{
    Tetris tetris;
    tetris.CreateBorder();
    tetris.AddCube();
    tetris.Loop();
}

//---------------------------------------------------------------

bool Tetris::InternalLoop()
{
    if (m_ImGuiWrapper->Exit())
        return true;

    m_ImGuiWrapper->Frame();

    CheckPressedKey(Key::ESC);

    if (m_ImGuiWrapper->PlayGame())
    {
        for (const auto& cube : m_cubes)
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
