#include <GL/glew.h>

#include "Cube.h"

//---------------------------------------------------------------

Cube::Cube(const std::vector<double>& positions, const std::vector<float>& colors)
    : Entity(6, GL_TRIANGLES)
{
    m_colors = std::vector<float>();
    m_colors.reserve(colors.size());
    for (auto color : colors)
    {
        m_colors.emplace_back(color);
    }

    const double actualPositions[] =
    {
        positions[0],
        positions[1],
        positions[2],
        positions[3],
        positions[4],
        positions[5],
        positions[4],
        positions[5],
        positions[6],
        positions[7],
        positions[0],
        positions[1]
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(actualPositions), actualPositions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), nullptr);
    glEnableVertexAttribArray(0);
}

//---------------------------------------------------------------

void Cube::Color()
{
    glUniform4f(glGetUniformLocation(m_shaderProgram, "triangleColor"), 1.0f, 0.0f, 0.0f, 1.0f);
}

//---------------------------------------------------------------

void Cube::InitShader()
{
    CompileShaders();

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);

    // Check for program linking errors
    CheckProgramLinking(m_shaderProgram);

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
}

//---------------------------------------------------------------

void Cube::TerminateShader()
{
    glDeleteProgram(m_shaderProgram);
}

//---------------------------------------------------------------

void Cube::CompileShaders()
{
    m_vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    m_fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 triangleColor;
        void main() {
            FragColor = triangleColor;
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
}

//---------------------------------------------------------------
