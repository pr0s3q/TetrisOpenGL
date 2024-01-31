#include "GL/glew.h"

#include <iostream>

#include "Entity.h"

//---------------------------------------------------------------

unsigned int Entity::s_shaderProgram = 0;
const char* Entity::s_vertexShaderSource = nullptr;
const char* Entity::s_fragmentShaderSource = nullptr;
unsigned int Entity::s_fragmentShader = 0;
unsigned int Entity::s_vertexShader = 0;
unsigned int Entity::s_VAO = 0;
unsigned int Entity::s_VBO = 0;


//---------------------------------------------------------------

Entity::Entity(const unsigned int count, const unsigned int mode)
    : m_shouldMove(true), m_count(count), m_mode(mode)
{
}

//---------------------------------------------------------------

bool Entity::IsStatic()
{
    return m_staticImage;
}

//---------------------------------------------------------------

void Entity::Loop()
{
    glUseProgram(s_shaderProgram);
    CheckProgramLinking(s_shaderProgram);
    Color();
    glBindVertexArray(s_VAO);
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