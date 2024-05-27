#include "Cube.h"

#include <iostream>

//---------------------------------------------------------------

Cube::Cube(
    const bool staticImage,
    const std::vector<double>& positions,
    const double scaleFactorX,
    const double scaleFactorY,
    const int imageId)
    : Cube(positions, scaleFactorX, scaleFactorY, imageId)
{
    m_staticImage = staticImage;
}

//---------------------------------------------------------------

Cube::Cube(
    const std::vector<double>& positions,
    const double scaleFactorX,
    const double scaleFactorY,
    const int imageId)
    : Entity(positions, imageId, scaleFactorX, scaleFactorY)
    , m_shouldMove(true)
{}

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
