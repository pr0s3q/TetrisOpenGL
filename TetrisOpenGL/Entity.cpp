#include "GL/glew.h"

#include <iostream>

#include "Entity.h"

//---------------------------------------------------------------

unsigned int Entity::m_shaderProgram = 0;
const char* Entity::m_vertexShaderSource = nullptr;
const char* Entity::m_fragmentShaderSource = nullptr;
unsigned int Entity::m_fragmentShader = 0;
unsigned int Entity::m_vertexShader = 0;

//---------------------------------------------------------------

Entity::Entity(const unsigned int count, const unsigned int mode)
    : m_shouldMove(true), m_count(count), m_mode(mode), m_VAO(0), m_VBO(0)
{
}

//---------------------------------------------------------------

Entity::~Entity()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteProgram(m_shaderProgram);
}

//---------------------------------------------------------------

bool Entity::IsStatic()
{
    return m_staticImage;
}

//---------------------------------------------------------------

void Entity::Loop()
{
    glUseProgram(m_shaderProgram);
    CheckProgramLinking(m_shaderProgram);
    Color();
    glBindVertexArray(m_VAO);
    CheckOpenGLError("Before draw");
    glDrawArrays(m_mode, 0, m_count);
}

//---------------------------------------------------------------

void Entity::CheckShaderCompilation(const unsigned int shader) {
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

void Entity::CheckProgramLinking(const unsigned int program) {
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

void Entity::CheckOpenGLError(const char* checkpoint) {
    const unsigned int error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error (" << checkpoint << "): " << error << '\n';
    }
}

//---------------------------------------------------------------
