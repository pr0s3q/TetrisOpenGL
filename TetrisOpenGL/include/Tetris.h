#pragma once

#include "GLFW/glfw3.h"

#include <memory>
#include <string>
#include <vector>

class Cube;
class ImGuiWrapper;
class TetriminoCubeGroup;

enum class Key;

class Tetris
{
public:

    //---------------------------------------------------------------

    /// <summary>
    /// Destructor - cleans up memory, terminate ImGui and glfw
    /// </summary>
    ~Tetris();

    //---------------------------------------------------------------

    /// <summary>
    /// Initialize Tetris
    /// </summary>
    static void Init();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    /// <summary>
    /// Constructor - Initialize glfw, crate window, initialize glew, shader and ImGui
    /// </summary>
    Tetris();

    //---------------------------------------------------------------

    /// <summary>
    /// Add random cube at the top of the game border
    /// </summary>
    void AddCube();

    //---------------------------------------------------------------

    /// <summary>
    /// Loops through all cubes, and check if there is completed row to delete
    /// </summary>
    void CheckForRowToDelete();

    //---------------------------------------------------------------

    /// <summary>
    /// Check if key is pressed, and moves cube in direction specific for pressed key.
    /// Checks only keys responsible for moving tetriminos
    /// </summary>
    /// <param name="scaleFactor"></param>
    /// <param name="key">GLFW key</param>
    /// <param name="keyPressed">Enum key</param>
    bool CheckPressedKey(const double& scaleFactor, const int& key, Key keyPressed);

    //---------------------------------------------------------------

    /// <summary>
    /// Check if key is pressed, and rotates cube in direction specific for pressed key.
    /// Checks only keys responsible for rotating tetriminos
    /// </summary>
    /// <param name="key">GLFW key</param>
    void CheckPressedKey(const int& key) const;

    //---------------------------------------------------------------

    /// <summary>
    /// Create game border, in which player will play the game
    /// </summary>
    void CreateBorder();

    //---------------------------------------------------------------

    /// <summary>
    /// Limit FPS to the specific number (number specified in m_targetFPS)
    /// </summary>
    void LimitFPS() const;

    //---------------------------------------------------------------

    /// <summary>
    /// Loop function. Responsible for events, generating graphic etc.
    /// </summary>
    void Loop();

    //---------------------------------------------------------------

    /// <summary>
    /// Check, whether program should terminate
    /// </summary>
    /// <returns>True if should terminate, false otherwise</returns>
    bool ShouldTerminate() const;

    //---------------------------------------------------------------

    /// <summary>
    /// Throws std::runtime_error with specific error message
    /// </summary>
    /// <param name="errorMessage"></param>
    static void SetOutcome(const std::string& errorMessage);

    //---------------------------------------------------------------

    std::vector<std::shared_ptr<Cube>> m_cubes;
    std::shared_ptr<TetriminoCubeGroup> m_cubeGroup;
    GLFWwindow* m_window;
    double m_scaleFactorX;
    double m_scaleFactorY;
    std::shared_ptr<ImGuiWrapper> m_ImGuiWrapper;
    int m_targetFPS;

    static const int s_height;
    static const int s_width;
    static const double s_dtFactor;

    //---------------------------------------------------------------
};
