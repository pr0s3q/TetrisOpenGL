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

    void ApplyRotationPositions(
        const std::vector<std::vector<double>>& positions,
        const std::vector<int>& xLocations,
        const std::vector<int>& yLocations,
        const int& rotation);

    //---------------------------------------------------------------

    bool CanBeMoved(const std::vector<Entity*>& entities, Key keyPressed) const;

    //---------------------------------------------------------------

    std::vector<TetriminoCube*>& GetCubes();

    //---------------------------------------------------------------

    int GetRotation() const;

    //---------------------------------------------------------------

    TetriminoType GetType() const;

    //---------------------------------------------------------------

    int GetXMovingFactor() const;

    //---------------------------------------------------------------

    int GetYMovingFactor() const;

    //---------------------------------------------------------------

    void MoveCubes(
        const std::vector<Entity*>& entities,
        const double& scaleFactor,
        Key keyPressed);

    //---------------------------------------------------------------

    void ResetCubes();

    //---------------------------------------------------------------

    void SetMove(bool shouldMove) const;

    //---------------------------------------------------------------

    void SetType(TetriminoType type);

    //---------------------------------------------------------------

    bool ShouldBeMovable(const std::vector<Entity*>& entities) const;

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    std::vector<TetriminoCube*> m_tetriminoCubes;
    TetriminoType m_type;
    int m_xMovingFactor;
    int m_yMovingFactor;
    int m_rotation;

    //---------------------------------------------------------------
};
