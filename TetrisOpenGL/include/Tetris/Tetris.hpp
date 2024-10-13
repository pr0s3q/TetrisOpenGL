#pragma once

#include <Engine/Array.hpp>
#include <Engine/Color.hpp>
#include <Engine/Game.hpp>

#include <Tetris/Cube.hpp>
#include <Tetris/JsonWrapper.hpp>
#include <Tetris/TetriminoCubeGroup.hpp>

#include <memory>
#include <vector>

enum class Key;

class Tetris final : Game
{
public:

    //---------------------------------------------------------------

    Tetris(const Tetris&) = delete;
    Tetris(Tetris&&) = delete;
    Tetris& operator=(const Tetris&) = delete;
    Tetris& operator=(Tetris&&) = delete;

    //---------------------------------------------------------------

    /// <summary>
    /// Launch Tetris
    /// </summary>
    static void Play();

    //---------------------------------------------------------------

    bool InternalLoop() override;

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    Tetris();

    //---------------------------------------------------------------

    /// <summary>
    /// Destructor - cleans up memory, terminate ImGui and glfw
    /// </summary>
    ~Tetris() override = default;

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

    void CheckPressedKey(Key keyPressed, const double& scaleFactor = 0.0);

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

    std::function<void()> MenuGui();
    std::function<void()> ScoreboardGui();
    std::function<void()> GameScoreGui();
    std::function<void()> SettingsGui();

    //---------------------------------------------------------------

    void AddScore();

    //---------------------------------------------------------------

    JsonWrapper m_jsonWrapper;
    Color m_uiElementColor;
    Color m_uiElementColorOnHover;
    Color m_uiElementTextColor;
    Color m_uiElementBorderColor;
    std::vector<std::shared_ptr<Cube>> m_cubes;
    Array<Cube, 13> m_borderCubes;
    TetriminoCubeGroup m_cubeGroup;
    int m_targetFPS;
    int m_score;
    int m_scoreCombo;
    bool m_playGame;
    bool m_exitClicked;

    static const char* s_name;

    //---------------------------------------------------------------
};
