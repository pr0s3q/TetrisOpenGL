#pragma once

#include <vector>

#include "Entity.h"
#include "HelperDefinitions.h"

enum class Key;

class Cube : public Entity
{
public:

    //---------------------------------------------------------------

    Cube(
        bool staticImage,
        const std::vector<double>& positions,
        const std::vector<float>& colors,
        const int imageId = CUBE_COLOR);

    //---------------------------------------------------------------

    Cube(const std::vector<double>& positions, const std::vector<float>& colors, const int imageId = CUBE_COLOR);

    //---------------------------------------------------------------

    virtual ~Cube() override = default;

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

    virtual void Loop() const override;

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

    bool m_shouldMove;
    bool m_staticImage = false;
    int m_count;
    unsigned int m_mode;
    std::vector<float> m_colors;

    static const char* s_vertexShaderSource;
    static const char* s_fragmentShaderSource;
    static unsigned int s_fragmentShader;
    static unsigned int s_vertexShader;
    static unsigned int s_shaderProgram;
    static unsigned int s_VAO;
    static unsigned int s_VBO;
    static unsigned int s_texture;

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    static void CompileShaders();

    //---------------------------------------------------------------
};
