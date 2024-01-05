#pragma once

#include <vector>

#include "TetriminoCube.h"

class TetriminoCubeGroup
{
public:

    //---------------------------------------------------------------

    TetriminoCubeGroup();

    //---------------------------------------------------------------

    void AddCube(TetriminoCube* cube);

    //---------------------------------------------------------------

    bool CanBeMoved(const std::vector<Entity*>& entities, Key keyPressed) const;

    //---------------------------------------------------------------

    void MoveCubes(const std::vector<Entity*>& entities, const double& scaleFactor, Key keyPressed) const;

    //---------------------------------------------------------------

    void SetMove(bool shouldMove) const;

    //---------------------------------------------------------------

    bool ShouldBeMovable(const std::vector<Entity*>& entities) const;

    //---------------------------------------------------------------

    void ResetCubes();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    std::vector<TetriminoCube*> m_tetriminoCubes;

    //---------------------------------------------------------------
};
