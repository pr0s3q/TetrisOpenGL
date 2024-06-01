#pragma once
#include <functional>
#include <vector>

struct ImFont;
struct ImGuiIO;

class GuiManager
{
public:

    //---------------------------------------------------------------

    GuiManager();

    void AddFont(const ImGuiIO& io);

    void AddFunction(const std::function<void()>& function);

    void CreateWindow(const float width, const float height, const char* name) const;

    void Loop() const;

    void PushFont() const;

    bool SetFunctionId(const unsigned long long functionId);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    ImFont* m_font;
    std::vector<std::function<void()>> m_functions;
    unsigned long long m_functionId;

    //---------------------------------------------------------------
};
