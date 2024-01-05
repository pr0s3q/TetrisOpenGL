#include <GL/glew.h>

#include "BoardManager.h"
#include "TetriminoCube.h"

//---------------------------------------------------------------

TetriminoCube::TetriminoCube(const std::vector<double>& positions, const std::vector<float>& colors, const int xLocation, const int yLocation)
    : Cube(positions, colors), m_xLocation(xLocation), m_yLocation(yLocation)
{
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

void TetriminoCube::Move(const double& scaleFactor, const Key keyPressed)
{
    if (!m_shouldMove || m_staticImage)
        return;

    switch (keyPressed)
    {
        case Key::W:
        {
            if(m_yLocation == 10)
                return;

            m_yLocation += 1;

            const auto yCoord = BoardManager::GetCoordinate(m_yLocation, scaleFactor);
            m_positions[1] = yCoord.first;
            m_positions[3] = yCoord.first;
            m_positions[5] = yCoord.second;
            m_positions[7] = yCoord.second;
            m_positions[9] = yCoord.second;
            m_positions[11] = yCoord.first;
            break;
        }
        case Key::S:
        {
            if (m_yLocation == -10)
                return;

            m_yLocation -= 1;

            const auto yCoord = BoardManager::GetCoordinate(m_yLocation, scaleFactor);
            m_positions[1] = yCoord.first;
            m_positions[3] = yCoord.first;
            m_positions[5] = yCoord.second;
            m_positions[7] = yCoord.second;
            m_positions[9] = yCoord.second;
            m_positions[11] = yCoord.first;
            break;
        }
        case Key::A:
        {
            if (m_xLocation == -5)
                return;

            m_xLocation -= 1;

            const auto xCoord = BoardManager::GetCoordinate(m_xLocation, scaleFactor);
            m_positions[0] = xCoord.first;
            m_positions[2] = xCoord.second;
            m_positions[4] = xCoord.second;
            m_positions[6] = xCoord.second;
            m_positions[8] = xCoord.first;
            m_positions[10] = xCoord.first;
            break;
        }
        case Key::D:
        {
            if (m_xLocation == 5)
                return;

            m_xLocation += 1;

            const auto xCoord = BoardManager::GetCoordinate(m_xLocation, scaleFactor);
            m_positions[0] = xCoord.first;
            m_positions[2] = xCoord.second;
            m_positions[4] = xCoord.second;
            m_positions[6] = xCoord.second;
            m_positions[8] = xCoord.first;
            m_positions[10] = xCoord.first;
            break;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_positions), m_positions);
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
