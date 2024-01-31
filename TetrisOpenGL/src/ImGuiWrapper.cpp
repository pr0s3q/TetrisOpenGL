#include "ImGuiWrapper.h"

#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

//---------------------------------------------------------------

ImGuiWrapper::ImGuiWrapper(ImGuiIO& io, const int width, const int height)
    : m_io(io),
      m_clear_color(0.45f, 0.55f, 0.60f, 1.00f),
      m_viewMode(Mode::EMenuView),
      m_width(width),
      m_height(height),
      m_playGameClicked(false),
      m_exitClicked(false)
{
    m_font = m_io.Fonts->AddFontFromFileTTF("OpenSans-Light.ttf", 50.0f);
    m_io.Fonts->Build();
    IM_ASSERT(m_font != NULL);
}

//---------------------------------------------------------------

bool ImGuiWrapper::Exit() const
{
    return m_exitClicked;
}

//---------------------------------------------------------------

void ImGuiWrapper::Frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowSize({ static_cast<float>(m_width), static_cast<float>(m_height) });
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::Begin("TetrisOpenGL", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::PushFont(m_font);

    switch(m_viewMode)
    {
        case Mode::EMenuView:
        {
            MenuGuiView();
            break;
        }
    }

    ImGui::PopFont();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//---------------------------------------------------------------

void ImGuiWrapper::MenuGuiView()
{
    ImVec2 label_size = ImGui::CalcTextSize(m_playText, nullptr, true);
    ImGui::SetCursorPos({ (static_cast<float>(m_width) - label_size.x) / 2, 100 });
    if (ImGui::Button(m_playText))
        m_playGameClicked = true;

    label_size = ImGui::CalcTextSize(m_scoreboardText, nullptr, true);
    ImGui::SetCursorPos({ (static_cast<float>(m_width) - label_size.x) / 2, 200 });
    ImGui::Button(m_scoreboardText);
    // TODO : Add scoreboard

    label_size = ImGui::CalcTextSize(m_exitText, nullptr, true);
    ImGui::SetCursorPos({ (static_cast<float>(m_width) - label_size.x) / 2, 300 });
    if (ImGui::Button(m_exitText))
        m_exitClicked = true;
}

//---------------------------------------------------------------

bool ImGuiWrapper::PlayGame() const
{
    return m_playGameClicked;
}

//---------------------------------------------------------------

void ImGuiWrapper::ShowMenu()
{
    m_playGameClicked = false;
}

//---------------------------------------------------------------
