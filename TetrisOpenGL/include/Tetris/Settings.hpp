#pragma once

class Settings
{
public:

    Settings() = default;

    void SetCubeColor(unsigned char color);
    unsigned char GetCubeColor() const;

private:

    unsigned char m_cubeColor;
};
