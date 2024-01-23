#pragma once

#include <vector>

#include "Enums.h"

class Entity
{
public:

    //---------------------------------------------------------------

    Entity(unsigned count, unsigned mode);

    //---------------------------------------------------------------

    virtual ~Entity() = default;

    //---------------------------------------------------------------

    // Check shader compilation status
    static void CheckShaderCompilation(unsigned shader);

    //---------------------------------------------------------------

    // Check program linking status
    static void CheckProgramLinking(unsigned program);

    //---------------------------------------------------------------

    // Check for OpenGL errors
    static void CheckOpenGLError(const char* checkpoint);

    //---------------------------------------------------------------

    virtual void Color() = 0;

    //---------------------------------------------------------------

    virtual bool IsStatic();

    //---------------------------------------------------------------

    virtual void Loop();

    //---------------------------------------------------------------

    virtual void Move(const double& scaleFactor, Key keyPressed) = 0;

    //---------------------------------------------------------------

    virtual void MoveForce(const double& scaleFactor) = 0;

    //---------------------------------------------------------------

    virtual void SetMove(bool shouldMove) = 0;

    //---------------------------------------------------------------

protected:

    //---------------------------------------------------------------

    bool m_shouldMove;
    bool m_staticImage = false;
    unsigned int m_count;
    unsigned int m_mode;
    std::vector<float> m_colors;

    static const char* s_vertexShaderSource;
    static const char* s_fragmentShaderSource;
    static unsigned int s_fragmentShader;
    static unsigned int s_vertexShader;
    static unsigned int s_shaderProgram;
    static unsigned int s_VAO;
    static unsigned int s_VBO;

    //---------------------------------------------------------------
};
