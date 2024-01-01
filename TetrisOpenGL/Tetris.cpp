#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Tetris.h"

#include <stdexcept>
#include <string>

//---------------------------------------------------------------

Tetris::Tetris()
{
    const int width = 1600;
    const int height = 900;
    const char* title = "Tetris OpenGL";
    if (!glfwInit())
    {
        SetOutcome("Cannot initialize GLFW");
        return;
    }

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
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


}

//---------------------------------------------------------------

void Tetris::Init()
{
    Tetris tetris;
    tetris.Loop();
}

//---------------------------------------------------------------

void Tetris::Loop() const
{
    while(true)
    {
        // Set the clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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

void Tetris::SetOutcome(const std::string& errorMessage)
{
    throw std::runtime_error(errorMessage.c_str());
}

//---------------------------------------------------------------
