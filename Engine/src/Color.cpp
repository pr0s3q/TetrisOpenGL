#include "Color.h"

//---------------------------------------------------------------

Color::Color(
    const unsigned char red,
    const unsigned char green,
    const unsigned char blue,
    const unsigned char alpha)
    : m_r(red),
      m_g(green),
      m_b(blue),
      m_a(alpha)
{}

//---------------------------------------------------------------

unsigned char Color::R() const
{
    return m_r;
}

//---------------------------------------------------------------

unsigned char Color::G() const
{
    return m_g;
}

//---------------------------------------------------------------

unsigned char Color::B() const
{
    return m_b;
}

//---------------------------------------------------------------

unsigned char Color::A() const
{
    return m_a;
}

//---------------------------------------------------------------

ImVec4 Color::ToImVec4() const
{
    return { static_cast<float>(m_r) / 255.0f,
             static_cast<float>(m_g) / 255.0f,
             static_cast<float>(m_b) / 255.0f,
             static_cast<float>(m_a) / 255.0f };
}

//---------------------------------------------------------------

Color Color::Red()
{
    return { 255, 0, 0, 255 };
}

//---------------------------------------------------------------

Color Color::Turquoise()
{
    return { 0, 255, 255, 255 };
}

//---------------------------------------------------------------
