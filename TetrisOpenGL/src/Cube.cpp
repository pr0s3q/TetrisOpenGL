#include "Cube.h"

#include <iostream>

//---------------------------------------------------------------

Cube::Cube(
    const bool staticImage,
    const std::vector<double>& positions,
    const std::vector<float>& colors,
    const int imageId)
    : Cube(positions, colors, imageId)
{
    m_staticImage = staticImage;
}

//---------------------------------------------------------------

Cube::Cube(const std::vector<double>& positions, const std::vector<float>& colors, const int imageId)
    : Entity(positions, imageId)
    , m_shouldMove(true)
{
    m_colors = std::vector<float>();
    m_colors.reserve(colors.size());
    for (auto color : colors)
        m_colors.emplace_back(color);
}

//---------------------------------------------------------------

bool Cube::IsStatic()
{
    return m_staticImage;
}

//---------------------------------------------------------------

void Cube::Move(const double& /*scaleFactor*/, const Key /*keyPressed*/)
{}

//---------------------------------------------------------------

void Cube::MoveForce(const double& /*scaleFactor*/)
{}

//---------------------------------------------------------------

void Cube::SetMove(const bool shouldMove)
{
    if (m_staticImage)
        return;

    m_shouldMove = shouldMove;
}

//---------------------------------------------------------------