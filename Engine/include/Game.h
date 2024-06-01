#pragma once

#include <vector>
#include <xstring>

#include "GuiManager.h"

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
    Game(const int screenWidth, const int screenHeight, const char* title);

    //---------------------------------------------------------------

    virtual ~Game();

    //---------------------------------------------------------------

    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

    //---------------------------------------------------------------

    bool CheckPressedKey(Key key) const;

    //---------------------------------------------------------------

    bool CheckTime();

    //---------------------------------------------------------------

    void DrawSquare(const std::shared_ptr<Entity>& entity);

    //---------------------------------------------------------------

    ImGuiIO& InitImGui() const;

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
    bool ShouldTerminate() const;

    //---------------------------------------------------------------

protected:

    //---------------------------------------------------------------

    GLFWwindow* m_window;
    const int m_height;
    const int m_width;
    double m_scaleFactorX;
    double m_scaleFactorY;
    const char* m_vertexShaderSource;
    const char* m_fragmentShaderSource;
    unsigned int m_fragmentShader;
    unsigned int m_vertexShader;
    unsigned int m_shaderProgram;
    unsigned int m_VAO;
    unsigned int m_VBO;
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

    /// <summary>
    /// Throws std::runtime_error with specific error message
    /// </summary>
    /// <param name="errorMessage"></param>
    static void SetOutcome(const std::string& errorMessage);

    //---------------------------------------------------------------

    void TerminateShader() const;

    //---------------------------------------------------------------

    double m_dtFactor;
    double m_lastTime;
    std::unique_ptr<unsigned int[]> m_textureIDs;
    int m_bindedTexture;
};
