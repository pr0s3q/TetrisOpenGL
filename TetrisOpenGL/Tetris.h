#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "Entity.h"
#include "KeyboardManager.h"

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

    void Loop();

    //---------------------------------------------------------------

    bool ShouldTerminate() const;

    //---------------------------------------------------------------

    static void SetOutcome(const std::string& errorMessage);

    //---------------------------------------------------------------

    std::vector<Entity*> m_entities;
    GLFWwindow* m_window;
    KeyboardManager m_keyboardManager;
    double m_scaleFactorX;
    double m_scaleFactorY;

    static const int s_height;
    static const int s_width;

    //---------------------------------------------------------------
};
