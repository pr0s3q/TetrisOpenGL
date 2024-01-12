#pragma once

#include <vector>

#include "Entity.h"
#include "Enums.h"
#include "TetriminoCubeGroup.h"

class TetriminoCreator
{
public:

    //---------------------------------------------------------------

    static void Create(
        TetriminoCubeGroup& cubeGroup,
        std::vector<Entity*>& entities,
        double scaleFactorX,
        double scaleFactorY);

    //---------------------------------------------------------------

    static void RotateIfPossible(
        const std::vector<Entity*>& entities,
        TetriminoCubeGroup& cubeGroup,
        const double& scaleFactorX,
        const double& scaleFactorY);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    static void CreateTetriminoPositions(
        std::vector<std::vector<double>>& positions,
        const std::vector<int>& xPositions,
        const std::vector<int>& yPositions,
        double scaleFactorX,
        double scaleFactorY);

    //---------------------------------------------------------------

    static void GetTypeLocations(
        std::vector<int>& xLocation,
        std::vector<int>& yLocation,
        int rotation,
        TetriminoType type);

    //---------------------------------------------------------------

    static bool IsCollidingWithOtherCubes(
        const std::vector<Entity*>& entities,
        const std::vector<int>& xLocations,
        const std::vector<int>& yLocations,
        TetriminoCubeGroup& cubeGroup);

    //---------------------------------------------------------------
};
