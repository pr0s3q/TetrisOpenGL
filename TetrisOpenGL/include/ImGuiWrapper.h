#pragma once

#include <memory>

struct ImFont;
struct ImGuiIO;
class JsonWrapper;

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
    ImFont* m_font;
    Mode m_viewMode;
    int m_width;
    int m_height;
    int m_score;
    int m_scoreCombo;
    bool m_playGameClicked;
    bool m_exitClicked;
    const char* m_exitText = "       Exit       ";
    const char* m_playText = "       Play       ";
    const char* m_scoreboardText = " Scoreboard ";
    const char* m_scoreText = "Score: ";
    const char* m_saveScore = "Save Score";

    //---------------------------------------------------------------
};
