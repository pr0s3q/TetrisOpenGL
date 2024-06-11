#pragma once

#include <memory>
#include <vector>

class Cube;
class TetriminoCubeGroup;

enum class TetriminoType;

class TetriminoCreator
{
public:

    //---------------------------------------------------------------

    static void Create(
        const std::shared_ptr<TetriminoCubeGroup>& cubeGroup,
        std::vector<std::shared_ptr<Cube>>& cubes,
        const double scaleFactorX,
        const double scaleFactorY);

    //---------------------------------------------------------------

    static void RotateIfPossible(
        const std::vector<std::shared_ptr<Cube>>& cubes,
        const std::shared_ptr<TetriminoCubeGroup>& cubeGroup,
        const double& scaleFactorX,
        const double& scaleFactorY);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    static void CreateTetriminoPositions(
        std::vector<std::vector<double>>& positions,
        const std::vector<int>& xPositions,
        const std::vector<int>& yPositions);

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
        const std::shared_ptr<TetriminoCubeGroup>& cubeGroup);

    //---------------------------------------------------------------
};
