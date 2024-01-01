#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Tetris.h"

#include <stdexcept>
#include <string>

#include "Cube.h"

//---------------------------------------------------------------

const int Tetris::s_height = 900;
const int Tetris::s_width = 1600;

//---------------------------------------------------------------

Tetris::Tetris()
    : m_scaleFactorX(100.0 / s_width), m_scaleFactorY(100.0 / s_height)
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
    m_entities = std::vector<Entity*>();

    m_entities.reserve(1);

    std::vector<double> positions;
    positions.reserve(8);
    positions.insert(positions.end(),
        {
             0.45 * m_scaleFactorX,  0.45 * m_scaleFactorY,
            -0.45 * m_scaleFactorX,  0.45 * m_scaleFactorY,
            -0.45 * m_scaleFactorX, -0.45 * m_scaleFactorY,
             0.45 * m_scaleFactorX, -0.45 * m_scaleFactorY
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    m_entities.emplace_back(new Cube(positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
             0.45 * m_scaleFactorX, 1.45 * m_scaleFactorY,
            -0.45 * m_scaleFactorX, 1.45 * m_scaleFactorY,
            -0.45 * m_scaleFactorX, 0.55 * m_scaleFactorY,
             0.45 * m_scaleFactorX, 0.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            1.45 * m_scaleFactorX, 1.45 * m_scaleFactorY,
            0.55 * m_scaleFactorX, 1.45 * m_scaleFactorY,
            0.55 * m_scaleFactorX, 0.55 * m_scaleFactorY,
            1.45 * m_scaleFactorX, 0.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
            1.45 * m_scaleFactorX, 2.45 * m_scaleFactorY,
            0.55 * m_scaleFactorX, 2.45 * m_scaleFactorY,
            0.55 * m_scaleFactorX, 1.55 * m_scaleFactorY,
            1.45 * m_scaleFactorX, 1.55 * m_scaleFactorY
        });

    m_entities.emplace_back(new Cube(positions, colors));
}

//---------------------------------------------------------------

void Tetris::Init()
{
    Tetris tetris;
    tetris.AddEntity();
    tetris.Loop();
}

//---------------------------------------------------------------

void Tetris::Loop() const
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
    }
}

//---------------------------------------------------------------

bool Tetris::ShouldTerminate() const
{
    return glfwWindowShouldClose(m_window);
}

//---------------------------------------------------------------

void Tetris::SetOutcome(const std::string& errorMessage)
{
    throw std::runtime_error(errorMessage.c_str());
}

//---------------------------------------------------------------
