#include <Tetris/Settings.hpp>

//---------------------------------------------------------------

void Settings::SetCubeColor(const unsigned char color)
{
    m_cubeColor = color;
}

//---------------------------------------------------------------

unsigned char Settings::GetCubeColor() const
{
    return m_cubeColor;
}

//---------------------------------------------------------------
