#pragma once

#include <vector>

#include "Enums.h"

class Cube
{
public:

    //---------------------------------------------------------------

    Cube(bool staticImage, const std::vector<double>& positions, const std::vector<float>& colors);

    //---------------------------------------------------------------

    Cube(const std::vector<double>& positions, const std::vector<float>& colors);

    //---------------------------------------------------------------

    virtual ~Cube() = default;

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

    void Color() const;

    //---------------------------------------------------------------

    static void InitShader();

    //---------------------------------------------------------------

    virtual bool IsStatic();

    //---------------------------------------------------------------

    void Loop() const;

    //---------------------------------------------------------------

    virtual void Move(const double& /*scaleFactor*/, Key /*keyPressed*/);

    //---------------------------------------------------------------

    virtual void MoveForce(const double& /*scaleFactor*/);

    //---------------------------------------------------------------

    void SetMove(bool shouldMove);

    //---------------------------------------------------------------

    static void TerminateShader();

    //---------------------------------------------------------------

protected:

    //---------------------------------------------------------------

    double m_positions[12];
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

private:

    //---------------------------------------------------------------

    static void CompileShaders();

    //---------------------------------------------------------------
};
