#pragma once

#include <vector>

enum class TetriminoType;

class Cube;
class TetriminoCubeGroup;

class TetriminoCreator
{
public:

    //---------------------------------------------------------------

    static void Create(
        TetriminoCubeGroup& cubeGroup,
        std::vector<std::shared_ptr<Cube>>& cubes,
        double scaleFactorX,
        double scaleFactorY);

    //---------------------------------------------------------------

    static void RotateIfPossible(
        const std::vector<std::shared_ptr<Cube>>& cubes,
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
        const std::vector<std::shared_ptr<Cube>>& cubes,
        const std::vector<int>& xLocations,
        const std::vector<int>& yLocations,
        TetriminoCubeGroup& cubeGroup);

    //---------------------------------------------------------------
};
