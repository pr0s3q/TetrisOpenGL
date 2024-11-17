#pragma once

#include <Engine/Stack.hpp>
#include <Engine/Vector2.hpp>

#include <functional>
#include <vector>

class Color;
struct ImFont;
struct ImGuiIO;

class GuiManager
{
public:

    //---------------------------------------------------------------

    explicit GuiManager(float scale);

    //---------------------------------------------------------------

    void AddFont(const ImGuiIO& io);

    //---------------------------------------------------------------

    void AddFunction(const std::function<void()>& function);

    //---------------------------------------------------------------

    static Vector2 CalculateTextSize(const char* text);

    //---------------------------------------------------------------

    [[nodiscard]] unsigned long long CurrentFunctionId() const;

    //---------------------------------------------------------------

    void CreateButton(
        float sizeX,
        float posY,
        float buttonBorderThickness,
        const char* text,
        const std::function<void()>& onClickFunction,
        const Color& buttonColor,
        const Color& buttonColorOnHover,
        const Color& buttonTextColor,
        const Color& buttonBorderColor,
        bool center = false) const;

    //---------------------------------------------------------------

    void CreateLabel(float sizeX, float posY, const char* text, float offsetX = 0.0f, bool center = false) const;
    static void CreateLabel(float posX, int number);

    //---------------------------------------------------------------

    void CreateDropDown(
        const std::vector<const char*>& dropDownValues,
        const std::function<void(unsigned char)>& onItemSelect,
        float dropdownBorderThickness,
        float dropdownWidth,
        const Color& dropdownColor,
        const Color& dropdownColorOnHover,
        const Color& dropdownTextColor,
        const Color& dropdownBorderColor,
        const char* dropdownLabelText) const;

    //---------------------------------------------------------------

    void CreateGap(float gapOnX, float gapOnY) const;

    //---------------------------------------------------------------

    void CreateTextInput(
        float sizeX,
        float posY,
        char (&textInput)[21],
        float textInputBorderThickness,
        const Color& textInputColor,
        const Color& textInputTextColor,
        const Color& textInputBorderColor,
        bool center) const;

    //---------------------------------------------------------------

    void CreateWindow(float sizeX, float sizeY, const char* name, bool center) const;

    //---------------------------------------------------------------

    void Loop() const;

    //---------------------------------------------------------------

    void PushFont() const;

    //---------------------------------------------------------------

    void PushFunctionId(unsigned long long id);

    //---------------------------------------------------------------

    void PopFunctionId();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    ImFont* m_font;
    std::vector<std::function<void()>> m_functions;
    Stack<unsigned long long, 10> m_functionIdStack;
    float m_scale;

    //---------------------------------------------------------------
};
