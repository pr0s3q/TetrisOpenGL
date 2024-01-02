#pragma once
#include <vector>

#include "Enums.h"

class Entity
{
public:

    //---------------------------------------------------------------

    Entity(unsigned count, unsigned mode);

    //---------------------------------------------------------------

    virtual ~Entity();

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

    void Loop();

    //---------------------------------------------------------------

    virtual void Move(const double& scaleFactor, const Key keyPressed) = 0;

    //---------------------------------------------------------------

    virtual void SetMove(const bool shouldMove) = 0;

    //---------------------------------------------------------------

protected:

    //---------------------------------------------------------------

    bool m_shouldMove;
    unsigned int m_count;
    unsigned int m_mode;
    unsigned int m_VAO;
    unsigned int m_VBO;
    std::vector<float> m_colors;

    //---------------------------------------------------------------

    static const char* m_vertexShaderSource;
    static const char* m_fragmentShaderSource;
    static unsigned int m_fragmentShader;
    static unsigned int m_vertexShader;
    static unsigned int m_shaderProgram;

    //---------------------------------------------------------------
};
