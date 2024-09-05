#include <memory>

#include <EngineEnums.h>

#include <Cube.h>
#include <TetriminoCube.h>
#include <TetriminoCubeGroup.h>

//---------------------------------------------------------------

TetriminoCubeGroup::TetriminoCubeGroup()
    : m_type()
    , m_xMovingFactor(0)
    , m_yMovingFactor(0)
    , m_rotation(0)
{
    m_tetriminoCubes.reserve(4);
    m_tetriminoCubes.insert(m_tetriminoCubes.end(), { nullptr, nullptr, nullptr, nullptr });
}

//---------------------------------------------------------------

void TetriminoCubeGroup::AddCube(const std::shared_ptr<TetriminoCube>& cube)
{
    for (size_t i = 0; i < m_tetriminoCubes.capacity(); i++)
    {
        if (m_tetriminoCubes[i] == nullptr)
        {
            m_tetriminoCubes[i] = cube;
            break;
        }
    }
}

//---------------------------------------------------------------

void TetriminoCubeGroup::ApplyRotationPositions(
    const std::vector<std::vector<double>>& positions,
    const std::vector<int>& xLocations,
    const std::vector<int>& yLocations,
    const int& rotation,
    const double& scaleFactorX,
    const double& scaleFactorY)
{
    m_tetriminoCubes[0]->ApplyRotationPositions(positions[0], xLocations[0], yLocations[0], scaleFactorX, scaleFactorY);
    m_tetriminoCubes[1]->ApplyRotationPositions(positions[1], xLocations[1], yLocations[1], scaleFactorX, scaleFactorY);
    m_tetriminoCubes[2]->ApplyRotationPositions(positions[2], xLocations[2], yLocations[2], scaleFactorX, scaleFactorY);
    m_tetriminoCubes[3]->ApplyRotationPositions(positions[3], xLocations[3], yLocations[3], scaleFactorX, scaleFactorY);
    m_rotation = rotation;
}

//---------------------------------------------------------------

bool TetriminoCubeGroup::CanBeMoved(const std::vector<std::shared_ptr<Cube>>& cubes, const Key keyPressed) const
{
    for (const auto& cube : cubes)
    {
        if (cube->IsStatic())
            continue;

        const auto cubeEntity = std::dynamic_pointer_cast<TetriminoCube>(cube);
        bool belongToCurrentGroup = false;
        for (const auto& tetriminoCube : m_tetriminoCubes)
        {
            if (tetriminoCube == cubeEntity)
            {
                belongToCurrentGroup = true;
                break;
            }
        }
        if (belongToCurrentGroup)
            continue;
        for (const auto& tetriminoCube : m_tetriminoCubes)
        {
            if (keyPressed == Key::LEFT)
            {
                if (cubeEntity->GetYLocation() == tetriminoCube->GetYLocation() &&
                    cubeEntity->GetXLocation() == tetriminoCube->GetXLocation() - 1)
                    return false;
            }
            if (keyPressed == Key::RIGHT)
            {
                if (cubeEntity->GetYLocation() == tetriminoCube->GetYLocation() &&
                    cubeEntity->GetXLocation() == tetriminoCube->GetXLocation() + 1)
                    return false;
            }
        }
    }
    return true;
}

//---------------------------------------------------------------

std::vector<std::shared_ptr<TetriminoCube>>& TetriminoCubeGroup::GetCubes()
{
    return m_tetriminoCubes;
}

//---------------------------------------------------------------

int TetriminoCubeGroup::GetRotation() const
{
    return m_rotation;
}

//---------------------------------------------------------------

TetriminoType TetriminoCubeGroup::GetType() const
{
    return m_type;
}

//---------------------------------------------------------------

int TetriminoCubeGroup::GetXMovingFactor() const
{
    return m_xMovingFactor;
}

//---------------------------------------------------------------

int TetriminoCubeGroup::GetYMovingFactor() const
{
    return m_yMovingFactor;
}

//---------------------------------------------------------------

void TetriminoCubeGroup::MoveCubes(
    const std::vector<std::shared_ptr<Cube>>& cubes,
    const double& scaleFactor,
    const Key keyPressed)
{
    for (const auto& cube : m_tetriminoCubes)
        if (!cube->CanBeMoved(keyPressed))
            return;

    if ((keyPressed == Key::LEFT || keyPressed == Key::RIGHT) && !CanBeMoved(cubes, keyPressed))
        return;

    switch (keyPressed)
    {
        case Key::UP:
            m_yMovingFactor += 1;
            break;
        case Key::DOWN:
            m_yMovingFactor -= 1;
            break;
        case Key::LEFT:
            m_xMovingFactor -= 1;
            break;
        case Key::RIGHT:
            m_xMovingFactor += 1;
            break;
        default:
#ifdef _DEBUG
            std::cerr << "How did we end up here? Key: " << KeyToString(keyPressed) << ' ' << __FILE__ << ' '
                      << __func__ << '\n';
#endif
            break;
    }

    for (const auto& cube : m_tetriminoCubes)
        cube->Move(scaleFactor, keyPressed);
}

//---------------------------------------------------------------

void TetriminoCubeGroup::ResetCubes()
{
    for (size_t i = 0; i < 4; i++)
        m_tetriminoCubes[i] = nullptr;
    m_xMovingFactor = 0;
    m_yMovingFactor = 0;
    m_rotation = 0;
}

//---------------------------------------------------------------

void TetriminoCubeGroup::SetMove(const bool shouldMove) const
{
    for (const auto& cube : m_tetriminoCubes)
        cube->SetMove(shouldMove);
}

//---------------------------------------------------------------

void TetriminoCubeGroup::SetType(const TetriminoType type)
{
    m_type = type;
}

//---------------------------------------------------------------

bool TetriminoCubeGroup::ShouldBeMovable(const std::vector<std::shared_ptr<Cube>>& cubes) const
{
    bool shouldBeMovable = true;

    // Check, if touching the board floor
    for (const auto& cube : m_tetriminoCubes)
        if (cube->GetYLocation() == -10)
            shouldBeMovable = false;

    if (!shouldBeMovable)
        return shouldBeMovable;

    for (const auto& cube : cubes)
    {
        if (cube->IsStatic())
            continue;

        const auto cubeEntity = std::dynamic_pointer_cast<TetriminoCube>(cube);
        bool belongToCurrentGroup = false;
        for (const auto& tetriminoCube : m_tetriminoCubes)
        {
            if (tetriminoCube == cubeEntity)
            {
                belongToCurrentGroup = true;
                break;
            }
        }
        if (belongToCurrentGroup)
            continue;
        for (const auto& tetriminoCube : m_tetriminoCubes)
            if (cubeEntity->GetXLocation() == tetriminoCube->GetXLocation() &&
                cubeEntity->GetYLocation() == tetriminoCube->GetYLocation() - 1)
                shouldBeMovable = false;
    }

    return shouldBeMovable;
}

//---------------------------------------------------------------
