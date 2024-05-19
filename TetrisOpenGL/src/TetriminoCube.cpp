#include "GL/glew.h"

#include "BoardManager.h"
#include "ConnectedTetriminoCubes.h"
#include "Cube.h"
#include "Enums.h"
#include "TetriminoCube.h"

//---------------------------------------------------------------

TetriminoCube::TetriminoCube(
    const std::shared_ptr<ConnectedTetriminoCubes>& connectedCubes,
    const std::vector<double>& positions,
    const std::vector<float>& colors,
    const int xLocation,
    const int yLocation)
    : Cube(positions, colors)
    , m_xLocation(xLocation)
    , m_yLocation(yLocation)
{
    m_connectedCubes = connectedCubes;
}

//---------------------------------------------------------------

void TetriminoCube::ApplyRotationPositions(
    const std::vector<double>& positions,
    const int xLocation,
    const int yLocation)
{
    m_positions[0] = positions[0];
    m_positions[1] = positions[1];
    m_positions[4] = positions[2];
    m_positions[5] = positions[3];
    m_positions[8] = positions[4];
    m_positions[9] = positions[5];
    m_positions[12] = positions[6];
    m_positions[13] = positions[7];

    m_xLocation = xLocation;
    m_yLocation = yLocation;
}

//---------------------------------------------------------------

bool TetriminoCube::CanBeMoved(const Key keyPressed) const
{
    switch (keyPressed)
    {
        case Key::UP:
        {
            if (m_yLocation == 10)
                return false;
            break;
        }
        case Key::DOWN:
        {
            if (m_yLocation == -10)
                return false;
            break;
        }
        case Key::LEFT:
        {
            if (m_xLocation == -5)
                return false;
            break;
        }
        case Key::RIGHT:
        {
            if (m_xLocation == 5)
                return false;
            break;
        }
    }
    return true;
}

//---------------------------------------------------------------

int TetriminoCube::GetXLocation() const
{
    return m_xLocation;
}

//---------------------------------------------------------------

int TetriminoCube::GetYLocation() const
{
    return m_yLocation;
}

//---------------------------------------------------------------

void TetriminoCube::Move(const double& scaleFactor, const Key keyPressed)
{
    if (!m_shouldMove || m_staticImage)
        return;

    switch (keyPressed)
    {
        case Key::UP:
        {
            if (m_yLocation == 10)
                return;

            m_yLocation += 1;

            const auto yCoord = BoardManager::GetCoordinate(m_yLocation, scaleFactor);
            m_positions[1] = yCoord.second;
            m_positions[5] = yCoord.second;
            m_positions[9] = yCoord.first;
            m_positions[13] = yCoord.first;
            break;
        }
        case Key::DOWN:
        {
            if (m_yLocation == -10)
                return;

            m_yLocation -= 1;

            const auto yCoord = BoardManager::GetCoordinate(m_yLocation, scaleFactor);
            m_positions[1] = yCoord.second;
            m_positions[5] = yCoord.second;
            m_positions[9] = yCoord.first;
            m_positions[13] = yCoord.first;
            break;
        }
        case Key::LEFT:
        {
            if (m_xLocation == -5)
                return;

            m_xLocation -= 1;

            const auto xCoord = BoardManager::GetCoordinate(m_xLocation, scaleFactor);
            m_positions[0] = xCoord.second;
            m_positions[4] = xCoord.first;
            m_positions[8] = xCoord.second;
            m_positions[12] = xCoord.first;
            break;
        }
        case Key::RIGHT:
        {
            if (m_xLocation == 5)
                return;

            m_xLocation += 1;

            const auto xCoord = BoardManager::GetCoordinate(m_xLocation, scaleFactor);
            m_positions[0] = xCoord.second;
            m_positions[4] = xCoord.first;
            m_positions[8] = xCoord.second;
            m_positions[12] = xCoord.first;
            break;
        }
    }
}

//---------------------------------------------------------------

void TetriminoCube::MoveForce(const double& scaleFactor)
{
    m_yLocation -= 1;

    const auto yCoord = BoardManager::GetCoordinate(m_yLocation, scaleFactor);
    m_positions[1] = yCoord.second;
    m_positions[5] = yCoord.second;
    m_positions[9] = yCoord.first;
    m_positions[13] = yCoord.first;
}

//---------------------------------------------------------------

void TetriminoCube::SetXLocation(const int location)
{
    m_xLocation = location;
}

//---------------------------------------------------------------

void TetriminoCube::SetYLocation(const int location)
{
    m_yLocation = location;
}

//---------------------------------------------------------------
