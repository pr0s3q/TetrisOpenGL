#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdexcept>
#include <string>

#include "Cube.h"
#include "Tetris.h"
#include "TetriminoCreator.h"

//---------------------------------------------------------------

const int Tetris::s_height = 900;
const int Tetris::s_width = 1600;

//---------------------------------------------------------------

Tetris::Tetris()
    : m_scaleFactorX(50.0 / s_width), m_scaleFactorY(50.0 / s_height)
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
    TetriminoCreator::Create(m_entities, m_scaleFactorX, m_scaleFactorY, TetriminoType::I);
}

//---------------------------------------------------------------

void Tetris::CreateBorder()
{
    m_entities = std::vector<Entity*>();
    // Reserve std::vector, so the array is not going to expand during runtime
    // Border - 7 cubes
    // Max possible cube entities from tetrimino - 11 X 22 -> 242 (11 X 22 is the board size)
    // Total 249 cubes (reserve 260 to have some extra space just in case)
    // If, std::vector will expand over 260, this could mean potential memory leak
    m_entities.reserve(260);

    std::vector<double> positions;
    positions.reserve(8);
    positions.insert(positions.end(),
        {
            -5.45 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            -4.55 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            -4.55 * m_scaleFactorX,  -9.55 * m_scaleFactorY,
            -5.45 * m_scaleFactorX,  -9.55 * m_scaleFactorY
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 0.0f , 1.0f , 0.0f , 1.0f });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            -4.45 * m_scaleFactorX, -10.45 * m_scaleFactorY,
             4.45 * m_scaleFactorX, -10.45 * m_scaleFactorY,
             4.45 * m_scaleFactorX,  -9.55 * m_scaleFactorY,
            -4.45 * m_scaleFactorX,  -9.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            5.45 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            4.55 * m_scaleFactorX, -10.45 * m_scaleFactorY,
            4.55 * m_scaleFactorX,  -9.55 * m_scaleFactorY,
            5.45 * m_scaleFactorX,  -9.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            -5.45 * m_scaleFactorX, 10.45 * m_scaleFactorY,
            -4.55 * m_scaleFactorX, 10.45 * m_scaleFactorY,
            -4.55 * m_scaleFactorX,  9.55 * m_scaleFactorY,
            -5.45 * m_scaleFactorX,  9.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            5.45 * m_scaleFactorX, 10.45 * m_scaleFactorY,
            4.55 * m_scaleFactorX, 10.45 * m_scaleFactorY,
            4.55 * m_scaleFactorX,  9.55 * m_scaleFactorY,
            5.45 * m_scaleFactorX,  9.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            -5.45 * m_scaleFactorX, -9.45 * m_scaleFactorY,
            -4.55 * m_scaleFactorX, -9.45 * m_scaleFactorY,
            -4.55 * m_scaleFactorX,  9.45 * m_scaleFactorY,
            -5.45 * m_scaleFactorX,  9.45 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            5.45 * m_scaleFactorX, -9.45 * m_scaleFactorY,
            4.55 * m_scaleFactorX, -9.45 * m_scaleFactorY,
            4.55 * m_scaleFactorX,  9.45 * m_scaleFactorY,
            5.45 * m_scaleFactorX,  9.45 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(true, positions, colors));
}

//---------------------------------------------------------------

void Tetris::Init()
{
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

        // S
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        {
            if (!m_keyboardManager.IsPressed(GLFW_KEY_S))
            {
                m_keyboardManager.SetPressedToTrue(GLFW_KEY_S);
                for (const auto entity : m_entities)
                {
                    entity->Move(m_scaleFactorY, Key::S);
                }
            }

        }
        else
        {
            m_keyboardManager.SetPressedToFalse(GLFW_KEY_S);
        }

        // W
        if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        {
            if (!m_keyboardManager.IsPressed(GLFW_KEY_W))
            {
                m_keyboardManager.SetPressedToTrue(GLFW_KEY_W);
                for (const auto entity : m_entities)
                {
                    entity->Move(m_scaleFactorY, Key::W);
                }
            }

        }
        else
        {
            m_keyboardManager.SetPressedToFalse(GLFW_KEY_W);
        }

        // A
        if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        {
            if (!m_keyboardManager.IsPressed(GLFW_KEY_A))
            {
                m_keyboardManager.SetPressedToTrue(GLFW_KEY_A);
                for (const auto entity : m_entities)
                {
                    entity->Move(m_scaleFactorX, Key::A);
                }
            }
        }
        else
        {
            m_keyboardManager.SetPressedToFalse(GLFW_KEY_A);
        }

        // D
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        {
            if (!m_keyboardManager.IsPressed(GLFW_KEY_D))
            {
                m_keyboardManager.SetPressedToTrue(GLFW_KEY_D);
                for (const auto entity : m_entities)
                {
                    entity->Move(m_scaleFactorX, Key::D);
                }
            }
        }
        else
        {
            m_keyboardManager.SetPressedToFalse(GLFW_KEY_D);
        }

        if (glfwGetKey(m_window, GLFW_KEY_L) == GLFW_PRESS)
        {
            if (!m_keyboardManager.IsPressed(GLFW_KEY_L))
            {
                m_keyboardManager.SetPressedToTrue(GLFW_KEY_L);
                for (const auto entity : m_entities)
                {
                    entity->SetMove(false);
                }
                TetriminoCreator::Create(m_entities, m_scaleFactorX, m_scaleFactorY, TetriminoType::I);
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
