#include "TetriminoCubeGroup.h"

//---------------------------------------------------------------

TetriminoCubeGroup::TetriminoCubeGroup()
    : m_type(), m_xMovingFactor(0), m_yMovingFactor(0), m_rotation(0)
{
    m_tetriminoCubes.reserve(4);
    m_tetriminoCubes.insert(m_tetriminoCubes.end(),
        {
            nullptr,
            nullptr,
            nullptr,
            nullptr
        });
}

//---------------------------------------------------------------

void TetriminoCubeGroup::AddCube(TetriminoCube* cube)
{
    for(size_t i = 0; i < m_tetriminoCubes.capacity(); i++)
    {
        const TetriminoCube* tCube = m_tetriminoCubes[i];
        if(tCube == nullptr)
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
    const int& rotation)
{
    m_tetriminoCubes[0]->ApplyRotationPositions(positions[0], xLocations[0], yLocations[0]);
    m_tetriminoCubes[1]->ApplyRotationPositions(positions[1], xLocations[1], yLocations[1]);
    m_tetriminoCubes[2]->ApplyRotationPositions(positions[2], xLocations[2], yLocations[2]);
    m_tetriminoCubes[3]->ApplyRotationPositions(positions[3], xLocations[3], yLocations[3]);
    m_rotation = rotation;
}

//---------------------------------------------------------------

bool TetriminoCubeGroup::CanBeMoved(const std::vector<Entity*>& entities, const Key keyPressed) const
{
    for (const auto entity : entities)
    {
        if (entity->IsStatic())
            continue;

        const TetriminoCube* cubeEntity = dynamic_cast<TetriminoCube*>(entity);
        bool belongToCurrentGroup = false;
        for (const TetriminoCube* cube : m_tetriminoCubes)
        {
            if (cube == cubeEntity)
            {
                belongToCurrentGroup = true;
                break;
            }
        }
        if (belongToCurrentGroup)
            continue;
        for (const auto cube : m_tetriminoCubes)
        {
            if(keyPressed == Key::A)
            {
                if (cubeEntity->GetYLocation() == cube->GetYLocation() &&
                    cubeEntity->GetXLocation() == cube->GetXLocation() - 1)
                    return false;
            }
            if (keyPressed == Key::D)
            {
                if (cubeEntity->GetYLocation() == cube->GetYLocation() &&
                    cubeEntity->GetXLocation() == cube->GetXLocation() + 1)
                    return false;
            }
        }
    }
    return true;
}

//---------------------------------------------------------------

std::vector<TetriminoCube*>& TetriminoCubeGroup::GetCubes()
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

void TetriminoCubeGroup::MoveCubes(const std::vector<Entity*>& entities, const double& scaleFactor, const Key keyPressed)
{
    for(const auto cube : m_tetriminoCubes)
    {
        if (!cube->CanBeMoved(keyPressed))
            return;
    }

    if ((keyPressed == Key::A || keyPressed == Key::D) && !CanBeMoved(entities, keyPressed))
        return;

    switch (keyPressed)
    {
    case Key::W:
        m_yMovingFactor += 1;
        break;
    case Key::S:
        m_yMovingFactor -= 1;
        break;
    case Key::A:
        m_xMovingFactor -= 1;
        break;
    case Key::D:
        m_xMovingFactor += 1;
        break;
    }

    for (const auto cube : m_tetriminoCubes)
    {
        cube->Move(scaleFactor, keyPressed);
    }
}

//---------------------------------------------------------------

void TetriminoCubeGroup::ResetCubes()
{
    for (size_t i = 0; i < 4; i++)
    {
        m_tetriminoCubes[i] = nullptr;
    }
    m_xMovingFactor = 0;
    m_yMovingFactor = 0;
    m_rotation = 0;
}

//---------------------------------------------------------------

void TetriminoCubeGroup::SetMove(const bool shouldMove) const
{
    for (const auto cube : m_tetriminoCubes)
    {
        cube->SetMove(shouldMove);
    }
}

//---------------------------------------------------------------

void TetriminoCubeGroup::SetType(const TetriminoType type)
{
    m_type = type;
}

//---------------------------------------------------------------

bool TetriminoCubeGroup::ShouldBeMovable(const std::vector<Entity*>& entities) const
{
    bool shouldBeMovable = true;

    // Check, if touching the board floor
    for (const auto cube : m_tetriminoCubes)
    {
        if (cube->GetYLocation() == -10)
            shouldBeMovable = false;
    }

    if (!shouldBeMovable)
        return shouldBeMovable;

    for(const auto entity : entities)
    {
        if (entity->IsStatic())
            continue;

        const TetriminoCube* cubeEntity = dynamic_cast<TetriminoCube*>(entity);
        bool belongToCurrentGroup = false;
        for(const TetriminoCube* cube : m_tetriminoCubes)
        {
            if (cube == cubeEntity)
            {
                belongToCurrentGroup = true;
                break;
            }
        }
        if (belongToCurrentGroup)
            continue;
        for (const auto cube : m_tetriminoCubes)
        {
            if (cubeEntity->GetXLocation() == cube->GetXLocation() &&
                cubeEntity->GetYLocation() == cube->GetYLocation() - 1)
                shouldBeMovable = false;
        }
    }

    return shouldBeMovable;
}

//---------------------------------------------------------------
