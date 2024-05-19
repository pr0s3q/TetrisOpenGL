#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <stdexcept>
#include <string>

#include "Game.h"

#include "Entity.h"
#include "stb/stb_image.h"

//---------------------------------------------------------------

Game::Game(const int screenWidth, const int screenHeight, const char* title)
    : m_height(screenHeight)
    , m_width(screenWidth)
    , m_scaleFactorX(70.0 / m_width)
    , m_scaleFactorY(70.0 / m_height)
{
    if (!glfwInit())
    {
        SetOutcome("Cannot initialize GLFW");
        return;
    }

    m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
    if (!m_window)
    {
        SetOutcome("Cannot create window");
        glfwTerminate();
        return;
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
    {
        SetOutcome("Cannot initialize GLEW");
        return;
    }

    // Compile Shader
    m_vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;
        out vec2 v_TexCoord;
        void main() {
            gl_Position = vec4(aPos, 1.0);
            v_TexCoord = aTexCoord;
        }
    )";

    m_fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 v_TexCoord;
        uniform sampler2D u_Texture;
        void main() {
            FragColor = texture(u_Texture, v_TexCoord);
        }
    )";

    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShader, 1, &m_vertexShaderSource, nullptr);
    glCompileShader(m_vertexShader);

    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShader, 1, &m_fragmentShaderSource, nullptr);
    glCompileShader(m_fragmentShader);

    // Check for shader compilation errors
    CheckShaderCompilation(m_vertexShader);
    CheckShaderCompilation(m_fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);

    // Check for program linking errors
    CheckProgramLinking(m_shaderProgram);

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(double), nullptr, GL_DYNAMIC_DRAW);

    // Cube positions in m_positions (id 0, 1, 4, 5, 8, 9...)
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), nullptr);
    glEnableVertexAttribArray(0);

    // Image positions in m_positions (id 2, 3, 6, 7, 10, 11...)
    glVertexAttribPointer(
        1,
        2,
        GL_DOUBLE,
        GL_FALSE,
        4 * sizeof(double),
        reinterpret_cast<const void*>(2 * sizeof(double)));
    glEnableVertexAttribArray(1);

    stbi_set_flip_vertically_on_load(1);
    int width, height, channels;
    unsigned char* image = stbi_load("res/textures/img.png", &width, &height, &channels, 4);
    if (!image)
        std::cerr << "Failed to load image" << '\n';

    // Generate texture
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    // Bind texture to sampler
    glUseProgram(m_shaderProgram);
    glUniform1i(glGetUniformLocation(m_shaderProgram, "u_Texture"), 0);
}

//---------------------------------------------------------------

Game::~Game()
{
    glfwTerminate();
}

//---------------------------------------------------------------

void Game::CheckShaderCompilation(const unsigned int shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation error:\n" << infoLog << '\n';
    }
}

//---------------------------------------------------------------

void Game::CheckProgramLinking(const unsigned int program)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Program linking error:\n" << infoLog << '\n';
    }
}

//---------------------------------------------------------------

void Game::CheckOpenGLError(const char* checkpoint)
{
    const unsigned int error = glGetError();
    if (error != GL_NO_ERROR)
        std::cerr << "OpenGL error (" << checkpoint << "): " << error << '\n';
}

//---------------------------------------------------------------

void Game::DrawSquare(const std::shared_ptr<Entity>& entity) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(entity->m_positions), entity->m_positions);

    glUseProgram(m_shaderProgram);
    CheckProgramLinking(m_shaderProgram);
    glBindVertexArray(m_VAO);
    CheckOpenGLError("Before draw");
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

//---------------------------------------------------------------

void Game::SetOutcome(const std::string& errorMessage)
{
    throw std::runtime_error(errorMessage.c_str());
}

//---------------------------------------------------------------

void Game::TerminateShader() const
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteProgram(m_shaderProgram);
}

//---------------------------------------------------------------

bool Game::ShouldTerminate() const
{
    return glfwWindowShouldClose(m_window);
}

//---------------------------------------------------------------
