#include <ImGui/imgui.h>

#include <Engine/Vector2.hpp>

//---------------------------------------------------------------

Vector2::Vector2()
    : x(0)
    , y(0)
{}

//---------------------------------------------------------------

Vector2::Vector2(const float x, const float y)
    : x(x)
    , y(y)
{}

//---------------------------------------------------------------

Vector2::Vector2(const ImVec2& imVec2)
    : x(imVec2.x)
    , y(imVec2.y)
{}

//---------------------------------------------------------------

float Vector2::X() const
{
    return x;
}

//---------------------------------------------------------------

float Vector2::Y() const
{
    return y;
}

//---------------------------------------------------------------
