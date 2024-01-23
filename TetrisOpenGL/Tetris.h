#pragma once

#include "GLFW/glfw3.h"

#include <string>
#include <vector>

#include "Entity.h"
#include "KeyboardManager.h"
#include "TetriminoCubeGroup.h"

class Tetris
{
public:

    //---------------------------------------------------------------

    ~Tetris();

    //---------------------------------------------------------------

    static void Init();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    Tetris();

    //---------------------------------------------------------------

    void AddEntity();

    //---------------------------------------------------------------

    void CheckForRowToDelete();

    //---------------------------------------------------------------

    void CheckPressedKey(const double& scaleFactor, const int& key, Key keyPressed);

    //---------------------------------------------------------------

    void CheckPressedKey(const int& key);

    //---------------------------------------------------------------

    void CreateBorder();

    //---------------------------------------------------------------

    void Loop();

    //---------------------------------------------------------------

    bool ShouldTerminate() const;

    //---------------------------------------------------------------

    static void SetOutcome(const std::string& errorMessage);

    //---------------------------------------------------------------

    std::vector<Entity*> m_entities;
    TetriminoCubeGroup m_cubeGroup;
    GLFWwindow* m_window;
    KeyboardManager m_keyboardManager;
    double m_scaleFactorX;
    double m_scaleFactorY;

    static const int s_height;
    static const int s_width;

    //---------------------------------------------------------------
};
