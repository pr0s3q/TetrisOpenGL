﻿#pragma once

#include <Engine/GuiManager.hpp>

#include <memory>
#include <string>
#include <vector>

class Entity;

enum class Key;

struct GLFWwindow;
struct ImGuiIO;

class Game
{
public:

    //---------------------------------------------------------------

    /// <summary>
    /// Constructor - Initialize glfw, crate window, initialize glew, shader and ImGui
    /// </summary>
    Game(int screenWidth, int screenHeight, const char* title);

    //---------------------------------------------------------------

    virtual ~Game();

    //---------------------------------------------------------------

    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    //---------------------------------------------------------------

    [[nodiscard]] bool CheckPressedKey(Key key) const;

    //---------------------------------------------------------------

    bool CheckTime();

    //---------------------------------------------------------------

    void DrawSquare(const std::shared_ptr<Entity>& entity);
    void DrawSquare(const Entity& entity);

    //---------------------------------------------------------------

    virtual bool InternalLoop() = 0;

    //---------------------------------------------------------------

    /// <summary>
    /// Loop function. Responsible for events, generating graphic etc.
    /// </summary>
    void Loop();

    //---------------------------------------------------------------

    /// <summary>
    /// Check, whether program should terminate
    /// </summary>
    /// <returns>True, if game should terminate, false otherwise</returns>
    [[nodiscard]] bool ShouldTerminate() const;

    //---------------------------------------------------------------

protected:

    //---------------------------------------------------------------

    const int m_height;
    const int m_width;
    double m_scaleFactorX;
    double m_scaleFactorY;
    GuiManager m_guiManager;

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    static void CheckOpenGLError(const char* checkpoint);

    //---------------------------------------------------------------

    static void CheckProgramLinking(unsigned int program);

    //---------------------------------------------------------------

    static void CheckShaderCompilation(unsigned int shader);

    //---------------------------------------------------------------

    static std::vector<int> GetGLFWKeys(Key key);

    //---------------------------------------------------------------

    [[nodiscard]] ImGuiIO& InitImGui() const;

    //---------------------------------------------------------------

    /// <summary>
    /// Throws std::runtime_error with specific error message
    /// </summary>
    /// <param name="errorMessage"></param>
    static void SetOutcome(const std::string& errorMessage);

    //---------------------------------------------------------------

    void TerminateShader() const;

    //---------------------------------------------------------------

    GLFWwindow* m_window;
    double m_dtFactor;
    double m_lastTime;
    const char* m_vertexShaderSource;
    const char* m_fragmentShaderSource;
    unsigned int m_fragmentShader;
    unsigned int m_vertexShader;
    unsigned int m_shaderProgram;
    unsigned int m_VAO;
    unsigned int m_VBO;
    std::unique_ptr<unsigned int[]> m_textureIDs;
    int m_boundTexture;

    //---------------------------------------------------------------
};
