#include <Engine/GuiManager.hpp>

#include <Engine/Color.hpp>
#include <Engine/Vector2.hpp>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

//---------------------------------------------------------------

GuiManager::GuiManager(const float scale)
    : m_font(nullptr)
    , m_functionId(0)
    , m_scale(scale)
{}

//---------------------------------------------------------------

void GuiManager::AddFont(const ImGuiIO& io)
{
    if (m_font == nullptr)
    {
        m_font = io.Fonts->AddFontFromFileTTF("OpenSans-Light.ttf", 50.0f * m_scale);
        io.Fonts->Build();
        IM_ASSERT(m_font);
    }
}

//---------------------------------------------------------------

void GuiManager::AddFunction(const std::function<void()>& function)
{
    m_functions.emplace_back(function);
}

//---------------------------------------------------------------

Vector2 GuiManager::CalculateTextSize(const char* text)
{
    return Vector2(ImGui::CalcTextSize(text, nullptr, true));
}

//---------------------------------------------------------------

void GuiManager::CreateButton(
    const float sizeX,
    const float posY,
    const char* text,
    const std::function<void()>& onClickFunction,
    const Color& buttonColor,
    const Color& buttonTextColor,
    const bool center) const
{
    const float cornerRadius = 10.0f * m_scale;
    float xPos;
    if (center)
        xPos = (1600.0f - sizeX) / 2.0f;
    else
        xPos = cornerRadius / 2.0f;

    ImGui::SetCursorPos({ xPos * m_scale, posY * m_scale });

    // Button radius
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, cornerRadius);
    // Button BG color
    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor.ToImVec4());
    // Button text color
    ImGui::PushStyleColor(ImGuiCol_Text, buttonTextColor.ToImVec4());

    if (ImGui::Button(text, ImVec2(250.0f * m_scale, 60.0f * m_scale)))
        onClickFunction();

    // Popping styles
    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(2);
}

//---------------------------------------------------------------

void GuiManager::CreateLabel(
    const float sizeX,
    const float posY,
    const char* text,
    const float offsetX,
    const bool center) const
{
    float xPos;
    if (center)
        xPos = (1600.0f * m_scale - sizeX) / 2.0f;
    else
        xPos = offsetX * m_scale;

    ImGui::SetCursorPos({ xPos, posY * m_scale });
    ImGui::Text("%s", text); // %s - string data type (format specifier in C )
}

//---------------------------------------------------------------

void GuiManager::CreateLabel(const float posX, const int number)
{
    ImGui::SetCursorPos({ posX, 0.0f });
    ImGui::Text("%i", number); // %i - integer data type (format specifier in C )
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
