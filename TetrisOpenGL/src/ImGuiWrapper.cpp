#include "ImGuiWrapper.h"

#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

//---------------------------------------------------------------

ImGuiWrapper::ImGuiWrapper(ImGuiIO& io, int width, int height)
    : m_io(io), m_clear_color(0.45f, 0.55f, 0.60f, 1.00f), m_width(width), m_height(height), m_showGameClicked(false)
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
    if (ImGui::Button("Button"))
        m_showGameClicked = true;

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", static_cast<double>(1000.0f / m_io.Framerate), static_cast<double>(m_io.Framerate));
    ImGui::PopFont();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//---------------------------------------------------------------

bool ImGuiWrapper::ShowGame() const
{
    return m_showGameClicked;
}

//---------------------------------------------------------------

void ImGuiWrapper::ShowMenu()
{
    m_showGameClicked = false;
}

//---------------------------------------------------------------
