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

    virtual bool InternalLoop() override;

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
    virtual ~Tetris() override = default;

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

    void CheckPressedKey(const Key keyPressed, const double& scaleFactor = 0.0);

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

    std::vector<std::shared_ptr<Cube>> m_cubes;
    std::shared_ptr<TetriminoCubeGroup> m_cubeGroup;
    std::shared_ptr<ImGuiWrapper> m_ImGuiWrapper;
    int m_targetFPS;

    static const double s_dtFactor;

    //---------------------------------------------------------------
};
