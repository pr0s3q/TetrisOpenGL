#include "GuiManager.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

//---------------------------------------------------------------

GuiManager::GuiManager()
    : m_font(nullptr)
    , m_functionId(0)
{}

//---------------------------------------------------------------

void GuiManager::AddFont(const ImGuiIO& io)
{
    if (m_font == nullptr)
    {
        m_font = io.Fonts->AddFontFromFileTTF("OpenSans-Light.ttf", 50.0f);
        io.Fonts->Build();
        IM_ASSERT(m_font != NULL);
    }
}

//---------------------------------------------------------------

void GuiManager::AddFunction(const std::function<void()>& function)
{
    m_functions.emplace_back(function);
}

//---------------------------------------------------------------

void GuiManager::CreateWindow(const float width, const float height, const char* name) const
{
    ImGui::SetNextWindowSize({ width, height });
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::Begin(
        name,
        nullptr,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);

    PushFont();
}

//---------------------------------------------------------------

void GuiManager::Loop() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_functions[m_functionId]();

    ImGui::PopFont();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//---------------------------------------------------------------

void GuiManager::PushFont() const
{
    if (m_font != nullptr)
        ImGui::PushFont(m_font);
}

//---------------------------------------------------------------

bool GuiManager::SetFunctionId(const unsigned long long functionId)
{
    if (m_functions.size() < functionId)
        return false;

    m_functionId = functionId;
    return true;
}

//---------------------------------------------------------------
