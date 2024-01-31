#include "ImGuiWrapper.h"

#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

//---------------------------------------------------------------

ImGuiWrapper::ImGuiWrapper(ImGuiIO& io, int width, int height)
    : m_io(io), m_clear_color(0.45f, 0.55f, 0.60f, 1.00f), m_width(width), m_height(height), m_playGameClicked(false)
{
    m_io.Fonts->AddFontDefault();
    m_font = m_io.Fonts->AddFontFromFileTTF("OpenSans-Light.ttf", 50.0f);
    m_io.Fonts->Build();
    IM_ASSERT(m_font != NULL);
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

    const char* text = " Play ";
    const ImVec2 label_size = ImGui::CalcTextSize(text, nullptr, true);
    ImGui::SetCursorPos({ (static_cast<float>(m_width) - label_size.x) / 2, 100 });
    if (ImGui::Button(text))
        m_playGameClicked = true;

    ImGui::PopFont();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
