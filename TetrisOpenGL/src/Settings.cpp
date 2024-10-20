#include <Tetris/Settings.hpp>

//---------------------------------------------------------------

Settings Settings::s_Instance;

//---------------------------------------------------------------

Settings::Settings()
    : m_cubeColor(0)
    , m_topColor(3)
    , m_bottomColor(1)
    , m_middleColor(2)
    , m_imageOffset(0)
{}

//---------------------------------------------------------------

int Settings::GetCubeColor()
{
    return s_Instance.m_cubeColor;
}

//---------------------------------------------------------------

int Settings::GetTopColor()
{
    return s_Instance.m_topColor;
}

//---------------------------------------------------------------

int Settings::GetBottomColor()
{
    return s_Instance.m_bottomColor;
}

//---------------------------------------------------------------

int Settings::GetMiddleColor()
{
    return s_Instance.m_middleColor;
}

//---------------------------------------------------------------

int Settings::GetImageOffset()
{
    return s_Instance.m_imageOffset;
}

//---------------------------------------------------------------

void Settings::SetImageOffset(const int offset)
{
    s_Instance.m_imageOffset = offset;
}

//---------------------------------------------------------------
