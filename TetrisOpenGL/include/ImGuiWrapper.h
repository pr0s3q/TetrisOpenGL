#pragma once

#include "ImGui/imgui.h"

class ImGuiWrapper
{
public:
    ImGuiWrapper(ImGuiIO& io);

    void Frame();

private:
    ImGuiIO& m_io;

    bool m_show_demo_window;
    bool m_show_another_window;
    ImVec4 m_clear_color;
};
