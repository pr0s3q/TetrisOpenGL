#pragma once

#include <functional>
#include <vector>

#include "Vector2.h"

struct ImFont;
struct ImGuiIO;

class GuiManager
{
public:

    //---------------------------------------------------------------

    GuiManager();

    //---------------------------------------------------------------

    void AddFont(const ImGuiIO& io);

    //---------------------------------------------------------------

    void AddFunction(const std::function<void()>& function);

    //---------------------------------------------------------------

    static Vector2 CalculateTextSize(const char* text);

    //---------------------------------------------------------------

    static void CreateButton(
        float posX,
        float posY,
        const char* text,
        const std::function<void()>& onClickFunction);

    //---------------------------------------------------------------

    static void CreateLabel(float posX, float posY, const char* text);
    static void CreateLabel(float posX, float posY, int number);

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

    //---------------------------------------------------------------
};
