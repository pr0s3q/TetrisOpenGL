#pragma once

#include "ImGui/imgui.h"

class ImGuiWrapper
{
public:

    //---------------------------------------------------------------

    ImGuiWrapper(const ImGuiIO& io, int width, int height);

    //---------------------------------------------------------------

    bool Exit() const;

    //---------------------------------------------------------------

    void Frame();

    //---------------------------------------------------------------

    void MenuGuiView();

    //---------------------------------------------------------------

    bool PlayGame() const;

    //---------------------------------------------------------------

    void ShowMenu();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    enum class Mode
    {
        EMenuView = 0
    };

    ImFont* m_font;
    ImVec4 m_clear_color;
    Mode m_viewMode;
    int m_width;
    int m_height;
    bool m_playGameClicked;
    bool m_exitClicked;
    const char* m_playText = "       Play       ";
    const char* m_scoreboardText = " Scoreboard ";
    const char* m_exitText = "       Exit       ";

    //---------------------------------------------------------------
};
