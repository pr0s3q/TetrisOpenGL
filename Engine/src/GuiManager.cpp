#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <Engine/Color.hpp>
#include <Engine/GuiManager.hpp>
#include <Engine/Vector2.hpp>

//---------------------------------------------------------------

GuiManager::GuiManager(const float scale)
    : m_font(nullptr)
    ,m_functionIdStack()
    ,m_scale(scale)
{
    m_functionIdStack.Push(0);
}

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

unsigned long long GuiManager::CurrentFunctionId() const
{
    return m_functionIdStack.Peek();
}

//---------------------------------------------------------------

void GuiManager::CreateButton(
    const float sizeX,
    const float posY,
    const float buttonBorderThickness,
    const char* text,
    const std::function<void()>& onClickFunction,
    const Color& buttonColor,
    const Color& buttonColorOnHover,
    const Color& buttonTextColor,
    const Color& buttonBorderColor,
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
    // Button border thickness
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, buttonBorderThickness * m_scale);
    // Button BG color
    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor.ToImVec4());
    // Button BG color on hover
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonColorOnHover.ToImVec4());
    // Button text color
    ImGui::PushStyleColor(ImGuiCol_Text, buttonTextColor.ToImVec4());
    // Button border color
    ImGui::PushStyleColor(ImGuiCol_Border, buttonBorderColor.ToImVec4());

    if (ImGui::Button(text, ImVec2(250.0f * m_scale, 60.0f * m_scale)))
        onClickFunction();

    // Popping styles
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(4);
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

void GuiManager::CreateDropDown(
    const std::vector<const char*>& dropDownValues,
    const std::function<void(unsigned char)>& onItemSelect,
    const float dropdownBorderThickness,
    const float dropdownWidth,
    const Color& dropdownColor,
    const Color& dropdownColorOnHover,
    const Color& dropdownTextColor,
    const Color& dropdownBorderColor,
    const char* dropdownLabelText) const
{
    static unsigned char selectedItemIdx = 0;

    const char* previewValue = dropDownValues[selectedItemIdx];
    const auto dropDownSize = static_cast<unsigned char>(dropDownValues.size());

    const float cornerRadius = 10.0f * m_scale;

    // Combo radius
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, cornerRadius);
    // Combo border thickness
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, dropdownBorderThickness * m_scale);
    // Combo padding
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f * m_scale, 5.0f * m_scale));
    // Combo BG color
    ImGui::PushStyleColor(ImGuiCol_FrameBg, dropdownColor.ToImVec4());
    ImGui::PushStyleColor(ImGuiCol_Button, dropdownColor.ToImVec4());
    ImGui::PushStyleColor(ImGuiCol_Header, dropdownColor.ToImVec4());
    // Combo BG color on hover
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, dropdownColorOnHover.ToImVec4());
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, dropdownColorOnHover.ToImVec4());
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, dropdownColorOnHover.ToImVec4());
    // Combo text color
    ImGui::PushStyleColor(ImGuiCol_Text, dropdownTextColor.ToImVec4());
    // Combo border color
    ImGui::PushStyleColor(ImGuiCol_Border, dropdownBorderColor.ToImVec4());

    // Center the dropdown
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const Vector2 textSize = CalculateTextSize(dropdownLabelText);
    const float xPos = (windowSize.x - textSize.X()) * 0.5f - dropdownWidth;
    ImGui::SetCursorPosX(xPos);

    // Set dropdown width
    ImGui::SetNextItemWidth(dropdownWidth * m_scale);

    constexpr ImGuiComboFlags flags = 0;
    if (ImGui::BeginCombo(dropdownLabelText, previewValue, flags))
    {
        for (unsigned char n = 0; n < dropDownSize; n++)
        {
            const bool isSelected = selectedItemIdx == n;
            if (ImGui::Selectable(dropDownValues[n], isSelected))
            {
                onItemSelect(n);
                selectedItemIdx = n;
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    // Popping styles
    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(8);
}

//---------------------------------------------------------------

void GuiManager::CreateGap(const float gapOnX, const float gapOnY) const
{
    ImGui::Dummy(ImVec2(gapOnX * m_scale, gapOnY * m_scale));
}

//---------------------------------------------------------------

void GuiManager::CreateTextInput(
    const float sizeX,
    const float posY,
    char (&textInput)[21],
    const float textInputBorderThickness,
    const Color& textInputColor,
    const Color& textInputTextColor,
    const Color& textInputBorderColor,
    const bool center) const
{
    const float cornerRadius = 10.0f * m_scale;
    float xPos;
    if (center)
        xPos = (1600.0f - sizeX) / 2.0f;
    else
        xPos = cornerRadius / 2.0f;

    ImGui::SetCursorPos({ xPos * m_scale, posY * m_scale });

    // TextInput radius
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, cornerRadius);
    // TextInput border thickness
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, textInputBorderThickness * m_scale);
    // TextInput padding
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f * m_scale, 5.0f * m_scale));
    // TextInput BG color
    ImGui::PushStyleColor(ImGuiCol_FrameBg, textInputColor.ToImVec4());
    ImGui::PushStyleColor(ImGuiCol_Button, textInputColor.ToImVec4());
    ImGui::PushStyleColor(ImGuiCol_Header, textInputColor.ToImVec4());
    // TextInput text color
    ImGui::PushStyleColor(ImGuiCol_Text, textInputTextColor.ToImVec4());
    // TextInput border color
    ImGui::PushStyleColor(ImGuiCol_Border, textInputBorderColor.ToImVec4());

    // Set TextInput width
    ImGui::SetNextItemWidth(sizeX * m_scale);
    constexpr int textSize = IM_ARRAYSIZE(textInput);
    ImGui::InputText("##", textInput, textSize);

    // Popping styles
    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(5);
}

//---------------------------------------------------------------

void GuiManager::Loop() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_functions[m_functionIdStack.Peek()]();

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

void GuiManager::PushFunctionId(const unsigned long long id)
{
    m_functionIdStack.Push(id);
}

//---------------------------------------------------------------

void GuiManager::PopFunctionId()
{
    if (m_functionIdStack.ElementCount() > 1)
        m_functionIdStack.Pop();
}

//---------------------------------------------------------------
