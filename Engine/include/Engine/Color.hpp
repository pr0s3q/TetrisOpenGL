#pragma once

#include <ImGui/imgui.h>

class Color
{
public:

    //---------------------------------------------------------------

    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

    //---------------------------------------------------------------

    ~Color() = default;

    //---------------------------------------------------------------

    Color() = delete;
    Color(const Color&) = delete;
    Color(Color&&) = delete;
    Color& operator=(const Color&) = delete;
    Color& operator=(Color&&) = delete;

    //---------------------------------------------------------------

    unsigned char R() const;
    unsigned char G() const;
    unsigned char B() const;
    unsigned char A() const;

    //---------------------------------------------------------------

    ImVec4 ToImVec4() const;

    //---------------------------------------------------------------

    static Color Red();
    static Color Turquoise();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    unsigned char m_r;
    unsigned char m_g;
    unsigned char m_b;
    unsigned char m_a;

    //---------------------------------------------------------------
};
