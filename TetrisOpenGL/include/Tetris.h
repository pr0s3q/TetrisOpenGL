#pragma once

#include <memory>
#include <vector>

#include "Game.h"

class Cube;
class ImGuiWrapper;
class TetriminoCubeGroup;

enum class Key;

class Tetris : Game
{
public:

    //---------------------------------------------------------------

    Tetris(const Tetris&) = delete;
    Tetris(Tetris&&) = delete;
    Tetris& operator=(const Tetris&) = delete;
    Tetris& operator=(Tetris&&) = delete;

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
    /// Destructor - cleans up memory, terminate ImGui and glfw
    /// </summary>
    ~Tetris();

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

    std::vector<std::shared_ptr<Cube>> m_cubes;
    std::shared_ptr<TetriminoCubeGroup> m_cubeGroup;
    std::shared_ptr<ImGuiWrapper> m_ImGuiWrapper;
    int m_targetFPS;

    static const double s_dtFactor;

    //---------------------------------------------------------------
};
