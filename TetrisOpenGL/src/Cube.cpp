#include "GL/glew.h"

#include "Cube.h"

#include <iostream>

//---------------------------------------------------------------

unsigned int Cube::s_shaderProgram = 0;
const char* Cube::s_vertexShaderSource = nullptr;
const char* Cube::s_fragmentShaderSource = nullptr;
unsigned int Cube::s_fragmentShader = 0;
unsigned int Cube::s_vertexShader = 0;
unsigned int Cube::s_VAO = 0;
unsigned int Cube::s_VBO = 0;

//---------------------------------------------------------------

Cube::Cube(const bool staticImage, const std::vector<double>& positions, const std::vector<float>& colors)
    : Cube(positions, colors)
{
    m_staticImage = staticImage;
}

//---------------------------------------------------------------

Cube::Cube(const std::vector<double>& positions, const std::vector<float>& colors)
    : m_shouldMove(true), m_count(6), m_mode(GL_TRIANGLES)
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
}

//---------------------------------------------------------------

void Cube::CheckShaderCompilation(const unsigned int shader) {
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

void Cube::CheckProgramLinking(const unsigned int program) {
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

void Cube::CheckOpenGLError(const char* checkpoint) {
    const unsigned int error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error (" << checkpoint << "): " << error << '\n';
    }
}

//---------------------------------------------------------------

void Cube::Color() const
{
    glUniform4f(glGetUniformLocation(s_shaderProgram, "triangleColor"), m_colors[0], m_colors[1], m_colors[2], m_colors[3]);
}

//---------------------------------------------------------------

void Cube::InitShader()
{
    CompileShaders();

    s_shaderProgram = glCreateProgram();
    glAttachShader(s_shaderProgram, s_vertexShader);
    glAttachShader(s_shaderProgram, s_fragmentShader);
    glLinkProgram(s_shaderProgram);

    // Check for program linking errors
    CheckProgramLinking(s_shaderProgram);

    glDeleteShader(s_vertexShader);
    glDeleteShader(s_fragmentShader);

    glGenVertexArrays(1, &s_VAO);
    glGenBuffers(1, &s_VBO);

    glBindVertexArray(s_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(double) * 12, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), nullptr);
    glEnableVertexAttribArray(0);
}

//---------------------------------------------------------------

bool Cube::IsStatic()
{
    return m_staticImage;
}

//---------------------------------------------------------------

void Cube::Loop() const
{
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_positions), m_positions);

    glUseProgram(s_shaderProgram);
    CheckProgramLinking(s_shaderProgram);
    Color();
    glBindVertexArray(s_VAO);
    CheckOpenGLError("Before draw");
    glDrawArrays(m_mode, 0, m_count);
}

//---------------------------------------------------------------

void Cube::Move(const double& /*scaleFactor*/, const Key /*keyPressed*/)
{
}

//---------------------------------------------------------------

void Cube::MoveForce(const double& /*scaleFactor*/)
{
}

//---------------------------------------------------------------

void Cube::SetMove(const bool shouldMove)
{
    if (m_staticImage)
        return;

    m_shouldMove = shouldMove;
}

//---------------------------------------------------------------

void Cube::TerminateShader()
{
    glDeleteVertexArrays(1, &s_VAO);
    glDeleteBuffers(1, &s_VBO);
    glDeleteProgram(s_shaderProgram);
}

//---------------------------------------------------------------

void Cube::CompileShaders()
{
    s_vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    s_fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 triangleColor;
        void main() {
            FragColor = triangleColor;
        }
    )";

    s_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vertexShader, 1, &s_vertexShaderSource, nullptr);
    glCompileShader(s_vertexShader);

    s_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_fragmentShader, 1, &s_fragmentShaderSource, nullptr);
    glCompileShader(s_fragmentShader);

    // Check for shader compilation errors
    CheckShaderCompilation(s_vertexShader);
    CheckShaderCompilation(s_fragmentShader);
}

//---------------------------------------------------------------
