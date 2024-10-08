#pragma once

struct ImVec2;

class Vector2
{
public:

    //---------------------------------------------------------------

    Vector2();

    //---------------------------------------------------------------

    Vector2(float x, float y);

    //---------------------------------------------------------------

    explicit Vector2(const ImVec2& imVec2);

    //---------------------------------------------------------------

    [[nodiscard]] float X() const;

    //---------------------------------------------------------------

    [[nodiscard]] float Y() const;

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    float x;
    float y;

    //---------------------------------------------------------------
};
