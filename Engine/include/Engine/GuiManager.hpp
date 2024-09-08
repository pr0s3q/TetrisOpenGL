#pragma once

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

    Vector2 CalculateTextSize(const char* text);

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
    void CreateLabel(float posX, int number);

    //---------------------------------------------------------------

    void CreateWindow(float width, float height, const char* name) const;

    //---------------------------------------------------------------

    void Loop() const;

    //---------------------------------------------------------------

    void PushFont() const;

    //---------------------------------------------------------------

    bool SetFunctionId(unsigned long long functionId);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    ImFont* m_font;
    std::vector<std::function<void()>> m_functions;
    unsigned long long m_functionId;
    float m_scale;

    //---------------------------------------------------------------
};
