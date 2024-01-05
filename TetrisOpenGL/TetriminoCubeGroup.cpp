#include <typeinfo>

#include "TetriminoCubeGroup.h"

//---------------------------------------------------------------

TetriminoCubeGroup::TetriminoCubeGroup()
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

void TetriminoCubeGroup::MoveCubes(const std::vector<Entity*>& entities, const double& scaleFactor, const Key keyPressed) const
{
    for(const auto cube : m_tetriminoCubes)
    {
        if (!cube->CanBeMoved(keyPressed))
            return;
    }

    if ((keyPressed == Key::A || keyPressed == Key::D) && !CanBeMoved(entities, keyPressed))
        return;

    for (const auto cube : m_tetriminoCubes)
    {
        cube->Move(scaleFactor, keyPressed);
    }
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

void TetriminoCubeGroup::ResetCubes()
{
    for(size_t i = 0; i < 4; i++)
    {
        m_tetriminoCubes[i] = nullptr;
    }
}

//---------------------------------------------------------------
