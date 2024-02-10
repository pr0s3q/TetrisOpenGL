#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <algorithm>
#include <ctime>
#include <stdexcept>
#include <string>

#include "Cube.h"
#include "TetriminoCreator.h"
#include "Tetris.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

//---------------------------------------------------------------

const int Tetris::s_height = 900;
const int Tetris::s_width = 1600;

//---------------------------------------------------------------

Tetris::Tetris()
    : m_scaleFactorX(70.0 / s_width), m_scaleFactorY(70.0 / s_height)
{
    const char* title = "Tetris OpenGL";
    if (!glfwInit())
    {
        SetOutcome("Cannot initialize GLFW");
        return;
    }

    m_window = glfwCreateWindow(s_width, s_height, title, nullptr, nullptr);
    if (!m_window)
    {
        SetOutcome("Cannot create window");
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        SetOutcome("Cannot initialize GLEW");
        return;
    }

    Cube::InitShader();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    m_ImGuiWrapper = new ImGuiWrapper(io, s_width, s_height);
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

//---------------------------------------------------------------

Tetris::~Tetris()
{
    Cube::TerminateShader();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    for (const auto cube : m_cubes)
        delete cube;
}

//---------------------------------------------------------------

void Tetris::AddCube()
{
    TetriminoCreator::Create(m_cubeGroup, m_cubes, m_scaleFactorX, m_scaleFactorY);
}

//---------------------------------------------------------------

void Tetris::CheckForRowToDelete()
{
    bool pointsAdded = false;
    while (true)
    {
        for (int yCoord = -10; yCoord <= 10; yCoord++)
        {
            bool rowEmpty = true;
            bool columnEmpty = false;
            for (int xCoord = -5; xCoord <= 5; xCoord++)
            {
                bool cubeFound = false;
                for (const auto cube : m_cubes)
                {
                    if (cube->IsStatic())
                        continue;

                    const TetriminoCube* tetriminoCube = dynamic_cast<TetriminoCube*>(cube);
                    if (tetriminoCube->GetYLocation() == yCoord && tetriminoCube->GetXLocation() == xCoord)
                    {
                        rowEmpty = false;
                        cubeFound = true;
                    }
                }
                if (!cubeFound)
                    columnEmpty = true;
            }

            if (rowEmpty)
            {
                if (pointsAdded)
                    m_ImGuiWrapper->ResetCombo();
                return;
            }

            if (columnEmpty)
                continue;

            std::vector<Cube*> toDelete;
            std::vector<long long> indexToErase;
            toDelete.reserve(11);
            indexToErase.reserve(11);
            for (const auto cube : m_cubes)
            {
                if (cube->IsStatic())
                    continue;

                const TetriminoCube* tetriminoCube = dynamic_cast<TetriminoCube*>(cube);
                if (tetriminoCube->GetYLocation() == yCoord)
                {
                    const long long index = std::ranges::find(m_cubes, cube) - m_cubes.begin();
                    indexToErase.emplace_back(index);
                    toDelete.emplace_back(cube);
                }
            }
            std::ranges::sort(indexToErase, std::ranges::greater());
            for (int i = 0; i < 11; i++)
            {
                m_cubes.erase(m_cubes.begin() + indexToErase[i]);
                delete toDelete[i];
            }
            m_ImGuiWrapper->AddScore();
            pointsAdded = true;
            ++yCoord;
            std::vector<TetriminoCube*> movableCubes;
            for (const auto entity : m_cubes)
            {
                if (entity->IsStatic())
                    continue;

                TetriminoCube* cube = dynamic_cast<TetriminoCube*>(entity);
                if (cube->GetYLocation() >= yCoord)
                {
                    cube->MoveForce(m_scaleFactorY);
                    movableCubes.emplace_back(cube);
                }
            }
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
                    for (const auto movableCube : movableCubes)
                    {
                        if (movableCube->GetYLocation() != i)
                            continue;

                        cubeInRow = true;
                        bool shouldBeMovable = true;
                        for (const auto entity : m_cubes)
                        {
                            if (entity->IsStatic())
                                continue;

                            const TetriminoCube* cube = dynamic_cast<TetriminoCube*>(entity);

                            if (cube->GetXLocation() == movableCube->GetXLocation() &&
                                cube->GetYLocation() == movableCube->GetYLocation() - 1)
                            {
                                shouldBeMovable = false;
                                break;
                            }
                        }
                        if (shouldBeMovable)
                        {
                            movableCube->MoveForce(m_scaleFactorY);
                            cubeMoved = true;
                        }
                    }
                }
            }
            break;
        }
    }
}

//---------------------------------------------------------------

void Tetris::CheckPressedKey(const double& scaleFactor, const int& key, const Key keyPressed)
{
    if (glfwGetKey(m_window, key) == GLFW_PRESS)
    {
        if (m_keyboardManager.IsPressed(key))
            return;

        m_keyboardManager.SetPressedToTrue(key);
        m_cubeGroup.MoveCubes(m_cubes, scaleFactor, keyPressed);

        if (m_cubeGroup.ShouldBeMovable(m_cubes))
            return;

        m_cubeGroup.SetMove(false);
        m_cubeGroup.ResetCubes();
        CheckForRowToDelete();
        TetriminoCreator::Create(m_cubeGroup, m_cubes, m_scaleFactorX, m_scaleFactorY);
    }
    else
    {
        m_keyboardManager.SetPressedToFalse(key);
    }
}

//---------------------------------------------------------------

void Tetris::CheckPressedKey(const int& key)
{
    if (glfwGetKey(m_window, key) == GLFW_PRESS)
    {
        if (m_keyboardManager.IsPressed(key))
            return;

        m_keyboardManager.SetPressedToTrue(key);
        TetriminoCreator::RotateIfPossible(m_cubes, m_cubeGroup, m_scaleFactorX, m_scaleFactorY);
    }
    else
    {
        m_keyboardManager.SetPressedToFalse(key);
    }
}

//---------------------------------------------------------------

void Tetris::CreateBorder()
{
    m_cubes = std::vector<Cube*>();
    // Reserve std::vector, so the array is not going to expand during runtime
    // Border - 7 cubes
    // Max possible cube entities from tetrimino - 11 X 21 -> 231 (11 X 21 is the board size)
    // Total 238 cubes (reserve 250 to have some extra space just in case)
    // If, std::vector will expand over 250, this could mean potential memory leak
    m_cubes.reserve(250);

    std::vector<double> positions;
    positions.reserve(8);
    positions.insert(positions.end(),
        {
            -6.45 * m_scaleFactorX, -11.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX, -11.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX, -10.55 * m_scaleFactorY,
            -6.45 * m_scaleFactorX, -10.55 * m_scaleFactorY
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 0.0f , 1.0f , 0.0f , 1.0f });

    m_cubes.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            -5.45 * m_scaleFactorX, -11.45 * m_scaleFactorY,
             5.45 * m_scaleFactorX, -11.45 * m_scaleFactorY,
             5.45 * m_scaleFactorX, -10.55 * m_scaleFactorY,
            -5.45 * m_scaleFactorX, -10.55 * m_scaleFactorY
        });

    m_cubes.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            6.45 * m_scaleFactorX, -11.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, -11.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, -10.55 * m_scaleFactorY,
            6.45 * m_scaleFactorX, -10.55 * m_scaleFactorY
        });

    m_cubes.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            -6.45 * m_scaleFactorX, 11.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX, 11.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX, 10.55 * m_scaleFactorY,
            -6.45 * m_scaleFactorX, 10.55 * m_scaleFactorY
        });

    m_cubes.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            6.45 * m_scaleFactorX, 11.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, 11.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, 10.55 * m_scaleFactorY,
            6.45 * m_scaleFactorX, 10.55 * m_scaleFactorY
        });

    m_cubes.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            -6.45 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX,  10.45 * m_scaleFactorY,
            -6.45 * m_scaleFactorX,  10.45 * m_scaleFactorY
        });

    m_cubes.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            6.45 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX,  10.45 * m_scaleFactorY,
            6.45 * m_scaleFactorX,  10.45 * m_scaleFactorY
        });

    m_cubes.emplace_back(new Cube(true, positions, colors));
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

void Tetris::Loop()
{
    while(!ShouldTerminate())
    {
        // Set the clear color
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Poll for and process events
        glfwPollEvents();

        if (m_ImGuiWrapper->Exit())
            break;

        m_ImGuiWrapper->Frame();

        if (m_ImGuiWrapper->PlayGame())
        {
            for (const auto cube : m_cubes)
            {
                cube->Loop();
            }

            CheckPressedKey(m_scaleFactorY, GLFW_KEY_S, Key::S);
            CheckPressedKey(m_scaleFactorY, GLFW_KEY_W, Key::W);
            CheckPressedKey(m_scaleFactorX, GLFW_KEY_A, Key::A);
            CheckPressedKey(m_scaleFactorX, GLFW_KEY_D, Key::D);
            CheckPressedKey(GLFW_KEY_Q);

            if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                m_ImGuiWrapper->ShowMenu();
            }

#ifdef _DEBUG // Extra feature for debug - L key is creating new TetriminoCube
            if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS)
            {
                if (!m_keyboardManager.IsPressed(GLFW_KEY_L))
                {
                    m_keyboardManager.SetPressedToTrue(GLFW_KEY_L);
                    m_cubeGroup.SetMove(false);
                    m_cubeGroup.ResetCubes();
                    TetriminoCreator::Create(m_cubeGroup, m_cubes, m_scaleFactorX, m_scaleFactorY);
                }
            }
            else
            {
                m_keyboardManager.SetPressedToFalse(GLFW_KEY_L);
            }
#endif
        }

        // Swap front and back buffers
        glfwSwapBuffers(m_window);
    }
}

//---------------------------------------------------------------

void Tetris::SetOutcome(const std::string& errorMessage)
{
    throw std::runtime_error(errorMessage.c_str());
}

//---------------------------------------------------------------

bool Tetris::ShouldTerminate() const
{
    return glfwWindowShouldClose(m_window);
}

//---------------------------------------------------------------
