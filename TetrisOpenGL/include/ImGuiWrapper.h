#pragma once

#include <memory>

#include "JsonWrapper.h"
#include "ImGui/imgui.h"

class ImGuiWrapper
{
public:

    //---------------------------------------------------------------

    ImGuiWrapper(const ImGuiIO& io, int width, int height);

    //---------------------------------------------------------------

    void AddScore();

    //---------------------------------------------------------------

    bool Exit() const;

    //---------------------------------------------------------------

    void Frame();

    //---------------------------------------------------------------

    void GameScoreGuiView() const;

    //---------------------------------------------------------------

    void MenuGuiView();

    //---------------------------------------------------------------

    void ScoreboardView() const;

    //---------------------------------------------------------------

    bool PlayGame() const;

    //---------------------------------------------------------------

    void ResetCombo();

    //---------------------------------------------------------------

    void ShowMenu();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    enum class Mode
    {
        EMenuView = 0,
        EGameScoreView = 1,
        EScoreboardView = 2
    };

    std::shared_ptr<JsonWrapper> m_jsonWrapper;
    std::shared_ptr<ImFont> m_font;
    ImVec4 m_clear_color;
    Mode m_viewMode;
    int m_width;
    int m_height;
    int m_score;
    int m_scoreCombo;
    bool m_playGameClicked;
    bool m_exitClicked;
    std::shared_ptr<const char> m_exitText;
    std::shared_ptr<const char> m_playText;
    std::shared_ptr<const char> m_scoreboardText;
    std::shared_ptr<const char> m_scoreText;
    std::shared_ptr<const char> m_saveScore;

    //---------------------------------------------------------------
};
