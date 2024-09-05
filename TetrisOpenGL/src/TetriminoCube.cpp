#include <EngineEnums.hpp>

#include <BoardManager.hpp>
#include <Cube.hpp>
#include <TetriminoCube.hpp>

//---------------------------------------------------------------

TetriminoCube::TetriminoCube(
    const std::vector<double>& positions,
    const int xLocation,
    const int yLocation,
    const double scaleFactorX,
    const double scaleFactorY)
    : Cube(positions, scaleFactorX, scaleFactorY)
    , m_xLocation(xLocation)
    , m_yLocation(yLocation)
{}

//---------------------------------------------------------------

void TetriminoCube::ApplyRotationPositions(
    const std::vector<double>& positions,
    const int xLocation,
    const int yLocation,
    const double& scaleFactorX,
    const double& scaleFactorY)
{
    m_positions[0] = positions[0] * scaleFactorX;
    m_positions[1] = positions[1] * scaleFactorY;
    m_positions[4] = positions[2] * scaleFactorX;
    m_positions[5] = positions[3] * scaleFactorY;
    m_positions[8] = positions[4] * scaleFactorX;
    m_positions[9] = positions[5] * scaleFactorY;
    m_positions[12] = positions[6] * scaleFactorX;
    m_positions[13] = positions[7] * scaleFactorY;

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
        default:
#ifdef _DEBUG
            std::cerr << "How did we end up here? Key: " << KeyToString(keyPressed) << ' ' << __FILE__ << ' '
                      << __func__ << '\n';
#endif
            break;
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

            const auto yCoord = BoardManager::GetCoordinate(m_yLocation);
            m_positions[1] = yCoord.second * scaleFactor;
            m_positions[5] = yCoord.second * scaleFactor;
            m_positions[9] = yCoord.first * scaleFactor;
            m_positions[13] = yCoord.first * scaleFactor;
            break;
        }
        case Key::DOWN:
        {
            if (m_yLocation == -10)
                return;

            m_yLocation -= 1;

            const auto yCoord = BoardManager::GetCoordinate(m_yLocation);
            m_positions[1] = yCoord.second * scaleFactor;
            m_positions[5] = yCoord.second * scaleFactor;
            m_positions[9] = yCoord.first * scaleFactor;
            m_positions[13] = yCoord.first * scaleFactor;
            break;
        }
        case Key::LEFT:
        {
            if (m_xLocation == -5)
                return;

            m_xLocation -= 1;

            const auto xCoord = BoardManager::GetCoordinate(m_xLocation);
            m_positions[0] = xCoord.second * scaleFactor;
            m_positions[4] = xCoord.first * scaleFactor;
            m_positions[8] = xCoord.second * scaleFactor;
            m_positions[12] = xCoord.first * scaleFactor;
            break;
        }
        case Key::RIGHT:
        {
            if (m_xLocation == 5)
                return;

            m_xLocation += 1;

            const auto xCoord = BoardManager::GetCoordinate(m_xLocation);
            m_positions[0] = xCoord.second * scaleFactor;
            m_positions[4] = xCoord.first * scaleFactor;
            m_positions[8] = xCoord.second * scaleFactor;
            m_positions[12] = xCoord.first * scaleFactor;
            break;
        }
        default:
#ifdef _DEBUG
            std::cerr << "How did we end up here? Key: " << KeyToString(keyPressed) << ' ' << __FILE__ << ' '
                      << __func__ << '\n';
#endif
            break;
    }
}

//---------------------------------------------------------------

void TetriminoCube::MoveForce(const double& scaleFactor)
{
    m_yLocation -= 1;

    const auto yCoord = BoardManager::GetCoordinate(m_yLocation);
    m_positions[1] = yCoord.second * scaleFactor;
    m_positions[5] = yCoord.second * scaleFactor;
    m_positions[9] = yCoord.first * scaleFactor;
    m_positions[13] = yCoord.first * scaleFactor;
}

//---------------------------------------------------------------
