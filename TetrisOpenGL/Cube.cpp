#include <GL/glew.h>

#include "Cube.h"

//---------------------------------------------------------------

Cube::Cube(const bool staticImage, const std::vector<double>& positions, const std::vector<float>& colors)
    : Cube(positions, colors)
{
    m_staticImage = staticImage;
}

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

    m_positions[0] = positions[0];
    m_positions[1] = positions[1];
    m_positions[2] = positions[2];
    m_positions[3] = positions[3];
    m_positions[4] = positions[4];
    m_positions[5] = positions[5];
    m_positions[6] = positions[4];
    m_positions[7] = positions[5];
    m_positions[8] = positions[6];
    m_positions[9] = positions[7];
    m_positions[10] = positions[0];
    m_positions[11] = positions[1];

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_positions), m_positions, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), nullptr);
    glEnableVertexAttribArray(0);
}

//---------------------------------------------------------------

void Cube::Color()
{
    glUniform4f(glGetUniformLocation(m_shaderProgram, "triangleColor"), m_colors[0], m_colors[1], m_colors[2], m_colors[3]);
}

//---------------------------------------------------------------

void Cube::Move(const double& scaleFactor, const Key keyPressed)
{
    if (!m_shouldMove || m_staticImage)
        return;

    constexpr double moveFactor = 1.0;
    switch (keyPressed)
    {
        case Key::W:
        {
            for (int i = 0; i < 6; i++)
            {
                m_positions[i * 2 + 1] += moveFactor * scaleFactor;
            }
            break;
        }
        case Key::S:
        {
            for (int i = 0; i < 6; i++)
            {
                m_positions[i * 2 + 1] -= moveFactor * scaleFactor;
            }
            break;
        }
        case Key::A:
        {
            for (int i = 0; i < 6; i++)
            {
                m_positions[i * 2] -= moveFactor * scaleFactor;
            }
            break;
        }
        case Key::D:
        {
            for (int i = 0; i < 6; i++)
            {
                m_positions[i * 2] += moveFactor * scaleFactor;
            }
            break;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_positions), m_positions);
}

//---------------------------------------------------------------

void Cube::SetMove(const bool shouldMove)
{
    if (m_staticImage)
        return;

    m_shouldMove = shouldMove;
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
