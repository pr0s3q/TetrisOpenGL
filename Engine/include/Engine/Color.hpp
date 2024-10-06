#pragma once

#include <ImGui/imgui.h>

class Color
{
public:

    //---------------------------------------------------------------

    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

    //---------------------------------------------------------------

    Color(unsigned char red, unsigned char green, unsigned char blue);

    //---------------------------------------------------------------

    ~Color() = default;

    //---------------------------------------------------------------

    Color() = delete;
    Color(const Color&) = delete;
    Color(Color&&) = delete;
    Color& operator=(const Color&) = delete;
    Color& operator=(Color&&) = delete;

    //---------------------------------------------------------------

    [[nodiscard]] unsigned char R() const;
    [[nodiscard]] unsigned char G() const;
    [[nodiscard]] unsigned char B() const;
    [[nodiscard]] unsigned char A() const;

    //---------------------------------------------------------------

    [[nodiscard]] ImVec4 ToImVec4() const;

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
