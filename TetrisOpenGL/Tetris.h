#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "Entity.h"

class Tetris
{
public:

    //---------------------------------------------------------------

    ~Tetris();

    //---------------------------------------------------------------

    void AddEntity();

    //---------------------------------------------------------------

    static void Init();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    Tetris();

    //---------------------------------------------------------------

    void Loop() const;

    //---------------------------------------------------------------

    bool ShouldTerminate() const;

    //---------------------------------------------------------------

    static void SetOutcome(const std::string& errorMessage);

    //---------------------------------------------------------------

    std::vector<Entity*> m_entities;
    GLFWwindow* m_window;
    const double m_scaleFactorX;
    const double m_scaleFactorY;

    static const int s_height;
    static const int s_width;

    //---------------------------------------------------------------
};
