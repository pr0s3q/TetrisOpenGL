#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <algorithm>
#include <ctime>
#include <stdexcept>
#include <string>

#include "Cube.h"
#include "TetriminoCreator.h"
#include "Tetris.h"

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

    if (glewInit() != GLEW_OK)
    {
        SetOutcome("Cannot initialize GLEW");
        return;
    }

    Cube::InitShader();
}

//---------------------------------------------------------------

Tetris::~Tetris()
{
    Cube::TerminateShader();
    glfwTerminate();
    for (const auto entity : m_entities)
        delete entity;
}

//---------------------------------------------------------------

void Tetris::AddEntity()
{
    TetriminoCreator::Create(m_cubeGroup, m_entities, m_scaleFactorX, m_scaleFactorY);
}

//---------------------------------------------------------------

void Tetris::CheckForRowToDelete()
{
    while(true)
    {
        for(int yCoord = -10; yCoord <= 10; yCoord++)
        {
            bool rowEmpty = true;
            bool columnEmpty = false;
            for(int xCoord = -5; xCoord <= 5; xCoord++)
            {
                bool cubeFound = false;
                for (const auto entity : m_entities)
                {
                    if (entity->IsStatic())
                        continue;

                    const TetriminoCube* cube = dynamic_cast<TetriminoCube*>(entity);
                    if(cube->GetYLocation() == yCoord && cube->GetXLocation() == xCoord)
                    {
                        rowEmpty = false;
                        cubeFound = true;
                    }
                }
                if (!cubeFound)
                    columnEmpty = true;
            }
            if(!rowEmpty && !columnEmpty)
            {
                std::vector<Entity*> toDelete;
                std::vector<long long> indexToErase;
                toDelete.reserve(11);
                indexToErase.reserve(11);
                for (const auto entity : m_entities)
                {
                    if (entity->IsStatic())
                        continue;

                    const TetriminoCube* cube = dynamic_cast<TetriminoCube*>(entity);
                    if (cube->GetYLocation() == yCoord)
                    {
                        const long long index = std::ranges::find(m_entities, entity) - m_entities.begin();
                        indexToErase.emplace_back(index);
                        toDelete.emplace_back(entity);
                    }
                }
                std::ranges::sort(indexToErase, std::ranges::greater());
                for(int i = 0; i < 11; i++)
                {
                    m_entities.erase(m_entities.begin() + indexToErase[i]);
                    delete toDelete[i];
                }
                ++yCoord;
                std::vector<TetriminoCube*> movableCubes;
                for (const auto entity : m_entities)
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
                while(cubeMoved)
                {
                    cubeMoved = false;
                    bool cubeInRow = true;
                    if(yCoord > -9)
                        --yCoord;
                    for(int i = yCoord; i <= 10 && cubeInRow; i++)
                    {
                        cubeInRow = false;
                        for(const auto movableCube : movableCubes)
                        {
                            if(movableCube->GetYLocation() == i)
                            {
                                cubeInRow = true;
                                bool shouldBeMovable = true;
                                for (const auto entity : m_entities)
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
                }
                break;
            }
            if (rowEmpty)
                return;
        }
    }
}

//---------------------------------------------------------------

void Tetris::CheckPressedKey(const double& scaleFactor, const int& key, const Key keyPressed)
{
    if (glfwGetKey(m_window, key) == GLFW_PRESS)
    {
        if (!m_keyboardManager.IsPressed(key))
        {
            m_keyboardManager.SetPressedToTrue(key);
            m_cubeGroup.MoveCubes(m_entities, scaleFactor, keyPressed);
            if (!m_cubeGroup.ShouldBeMovable(m_entities))
            {
                m_cubeGroup.SetMove(false);
                m_cubeGroup.ResetCubes();
                CheckForRowToDelete();
                TetriminoCreator::Create(m_cubeGroup, m_entities, m_scaleFactorX, m_scaleFactorY);
            }
        }

    }
    else
    {
        m_keyboardManager.SetPressedToFalse(key);
    }
}

//---------------------------------------------------------------

void Tetris::CheckPressedKey(const int& key, Key keyPressed)
{
    if (glfwGetKey(m_window, key) == GLFW_PRESS)
    {
        if (!m_keyboardManager.IsPressed(key))
        {
            m_keyboardManager.SetPressedToTrue(key);
            TetriminoCreator::RotateIfPossible(m_entities, m_cubeGroup, m_scaleFactorX, m_scaleFactorY);
        }
    }
    else
    {
        m_keyboardManager.SetPressedToFalse(key);
    }
}

//---------------------------------------------------------------

void Tetris::CreateBorder()
{
    m_entities = std::vector<Entity*>();
    // Reserve std::vector, so the array is not going to expand during runtime
    // Border - 7 cubes
    // Max possible cube entities from tetrimino - 11 X 21 -> 231 (11 X 21 is the board size)
    // Total 238 cubes (reserve 250 to have some extra space just in case)
    // If, std::vector will expand over 250, this could mean potential memory leak
    m_entities.reserve(250);

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

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            -5.45 * m_scaleFactorX, -11.45 * m_scaleFactorY,
             5.45 * m_scaleFactorX, -11.45 * m_scaleFactorY,
             5.45 * m_scaleFactorX, -10.55 * m_scaleFactorY,
            -5.45 * m_scaleFactorX, -10.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            6.45 * m_scaleFactorX, -11.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, -11.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, -10.55 * m_scaleFactorY,
            6.45 * m_scaleFactorX, -10.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            -6.45 * m_scaleFactorX, 11.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX, 11.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX, 10.55 * m_scaleFactorY,
            -6.45 * m_scaleFactorX, 10.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            6.45 * m_scaleFactorX, 11.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, 11.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, 10.55 * m_scaleFactorY,
            6.45 * m_scaleFactorX, 10.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            -6.45 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            -5.55 * m_scaleFactorX,  10.45 * m_scaleFactorY,
            -6.45 * m_scaleFactorX,  10.45 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            6.45 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            5.55 * m_scaleFactorX,  10.45 * m_scaleFactorY,
            6.45 * m_scaleFactorX,  10.45 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));
}

//---------------------------------------------------------------

void Tetris::Init()
{
    srand(time(nullptr));
    Tetris tetris;
    tetris.CreateBorder();
    tetris.AddEntity();
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

        for (const auto entity : m_entities)
        {
            entity->Loop();
        }

        // Swap front and back buffers
        glfwSwapBuffers(m_window);

        // Poll for and process events
        glfwPollEvents();

        CheckPressedKey(m_scaleFactorY, GLFW_KEY_S, Key::S);
        CheckPressedKey(m_scaleFactorY, GLFW_KEY_W, Key::W);
        CheckPressedKey(m_scaleFactorX, GLFW_KEY_A, Key::A);
        CheckPressedKey(m_scaleFactorX, GLFW_KEY_D, Key::D);
        CheckPressedKey(GLFW_KEY_Q, Key::Q);

        if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS)
        {
            if (!m_keyboardManager.IsPressed(GLFW_KEY_L))
            {
                m_keyboardManager.SetPressedToTrue(GLFW_KEY_L);
                m_cubeGroup.SetMove(false);
                m_cubeGroup.ResetCubes();
                TetriminoCreator::Create(m_cubeGroup, m_entities, m_scaleFactorX, m_scaleFactorY);
            }
        }
        else
        {
            m_keyboardManager.SetPressedToFalse(GLFW_KEY_L);
        }
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
