#include <functional>
#include <vector>
#include <random>
#include <thread>

#include "BoardManager.h"
#include "TetriminoCreator.h"
#include "TetriminoCube.h"
#include "Tetris.h"

//---------------------------------------------------------------

void TetriminoCreator::Create(TetriminoCubeGroup& cubeGroup, std::vector<Cube*>& cubes, const double scaleFactorX, const double scaleFactorY)
{
    std::uniform_int_distribution uid(0, 6);
    std::mersenne_twister_engine<unsigned long long, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15, 0xefc60000, 18, 1812433253> rng_engine(clock() + std::hash<std::thread::id>()(std::this_thread::get_id()));
    auto generator = std::bind(uid, rng_engine);
    const TetriminoType type = static_cast<TetriminoType>(generator());
    cubeGroup.SetType(type);

    std::vector<std::vector<double>> positions;
    std::vector<int> xLocations;
    std::vector<int> yLocations;
    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    GetTypeLocations(xLocations, yLocations, 0, type);
    CreateTetriminoPositions(positions, xLocations, yLocations, scaleFactorX, scaleFactorY);

    for (int i = 0; i < 4; i++)
    {
        auto cube = new TetriminoCube(positions[i], colors, xLocations[i], yLocations[i]);
        cubes.emplace_back(cube);
        cubeGroup.AddCube(cube);
    }
}

//---------------------------------------------------------------

void TetriminoCreator::RotateIfPossible(const std::vector<Cube*>& cubes, TetriminoCubeGroup& cubeGroup, const double& scaleFactorX, const double& scaleFactorY)
{
    const TetriminoType type = cubeGroup.GetType();

    if (type == TetriminoType::O)
        return;

    const int xMovingFactor = cubeGroup.GetXMovingFactor();
    const int yMovingFactor = cubeGroup.GetYMovingFactor();
    int rotation = cubeGroup.GetRotation() + 1;
    std::vector<int> xLocations;
    std::vector<int> yLocations;
    std::vector<std::vector<double>> positions;

    switch (type)
    {
        case TetriminoType::I:
        case TetriminoType::S:
        case TetriminoType::Z:
        {
            if (rotation == 2)
                rotation = 0;
            break;
        }
        case TetriminoType::T:
        case TetriminoType::L:
        case TetriminoType::J:
        {
            if (rotation == 4)
                rotation = 0;
            break;
        }
    }

    GetTypeLocations(xLocations, yLocations, rotation, type);

    xLocations[0] += xMovingFactor;
    xLocations[1] += xMovingFactor;
    xLocations[2] += xMovingFactor;
    xLocations[3] += xMovingFactor;
    yLocations[0] += yMovingFactor;
    yLocations[1] += yMovingFactor;
    yLocations[2] += yMovingFactor;
    yLocations[3] += yMovingFactor;
    if (IsCollidingWithOtherCubes(cubes, xLocations, yLocations, cubeGroup))
        return;

    CreateTetriminoPositions(positions, xLocations, yLocations, scaleFactorX, scaleFactorY);
    cubeGroup.ApplyRotationPositions(positions, xLocations, yLocations, rotation);
}

//---------------------------------------------------------------

void TetriminoCreator::CreateTetriminoPositions(
    std::vector<std::vector<double>>& positions,
    const std::vector<int>& xPositions,
    const std::vector<int>& yPositions,
    const double scaleFactorX,
    const double scaleFactorY)
{
    positions.reserve(4);
    positions.insert(positions.end(),
        {
            std::vector<double>(),
            std::vector<double>(),
            std::vector<double>(),
            std::vector<double>()
        });

    for(int i = 0; i < 4; i++)
    {
        auto xCoord = BoardManager::GetCoordinate(xPositions[i], scaleFactorX);
        auto yCoord = BoardManager::GetCoordinate(yPositions[i], scaleFactorY);
        positions[i].reserve(8);
        positions[i].insert(positions[i].end(),
            {
                xCoord.first,  yCoord.first,
                xCoord.second, yCoord.first,
                xCoord.second, yCoord.second,
                xCoord.first,  yCoord.second
            });
    }
}

//---------------------------------------------------------------

void TetriminoCreator::GetTypeLocations(std::vector<int>& xLocation, std::vector<int>& yLocation, const int rotation, TetriminoType type)
{
    xLocation.reserve(4);
    yLocation.reserve(4);
    switch (type)
    {
        case TetriminoType::I:
        {
            if (rotation == 0)
            {
                xLocation.insert(xLocation.end(), { 0, 0, 0, 0 });
                yLocation.insert(yLocation.end(), { 10, 9, 8, 7 });
            }
            else
            {
                xLocation.insert(xLocation.end(), { -2, -1, 0, 1 });
                yLocation.insert(yLocation.end(), { 9, 9, 9, 9 });
            }
            break;
        }
        case TetriminoType::T:
        {
            if (rotation == 0)
            {
                xLocation.insert(xLocation.end(), { -1, 0, 1, 0 });
                yLocation.insert(yLocation.end(), { 10, 10, 10, 9 });
            }
            else if (rotation == 1)
            {
                xLocation.insert(xLocation.end(), { -1, 0, 0, 0 });
                yLocation.insert(yLocation.end(), { 10, 11, 10, 9 });
            }
            else if (rotation == 2)
            {
                xLocation.insert(xLocation.end(), { -1, 0, 1, 0 });
                yLocation.insert(yLocation.end(), { 10, 10, 10, 11 });
            }
            else
            {
                xLocation.insert(xLocation.end(), { 1, 0, 0, 0 });
                yLocation.insert(yLocation.end(), { 10, 11, 10, 9 });
            }
            break;
        }
        case TetriminoType::O:
        {
            xLocation.insert(xLocation.end(), { 0, 0, 1, 1 });
            yLocation.insert(yLocation.end(), { 10, 9, 10, 9 });
            break;
        }
        case TetriminoType::L:
        {
            if (rotation == 0)
            {
                xLocation.insert(xLocation.end(), { 0, 0, 0, 1 });
                yLocation.insert(yLocation.end(), { 10, 9, 8, 8 });
            }
            else if (rotation == 1)
            {
                xLocation.insert(xLocation.end(), { -1, -1, 0, 1 });
                yLocation.insert(yLocation.end(), { 8, 9, 9, 9 });
            }
            else if (rotation == 2)
            {
                xLocation.insert(xLocation.end(), { -1, 0, 0, 0 });
                yLocation.insert(yLocation.end(), { 10, 10, 9, 8 });
            }
            else
            {
                xLocation.insert(xLocation.end(), { -1, 0, 1, 1 });
                yLocation.insert(yLocation.end(), { 9, 9, 9, 10 });
            }
            break;
        }
        case TetriminoType::J:
        {
            if (rotation == 0)
            {
                xLocation.insert(xLocation.end(), { -1, 0, 0, 0 });
                yLocation.insert(yLocation.end(), { 8, 8, 9, 10 });
            }
            else if (rotation == 1)
            {
                xLocation.insert(xLocation.end(), { -1, -1, 0, 1 });
                yLocation.insert(yLocation.end(), { 10, 9, 9, 9 });
            }
            else if (rotation == 2)
            {
                xLocation.insert(xLocation.end(), { 0, 0, 0, 1 });
                yLocation.insert(yLocation.end(), { 8, 9, 10, 10 });
            }
            else
            {
                xLocation.insert(xLocation.end(), { -1, 0, 1, 1 });
                yLocation.insert(yLocation.end(), { 9, 9, 9, 8 });
            }
            break;
        }
        case TetriminoType::S:
        {
            if (rotation == 0)
            {
                xLocation.insert(xLocation.end(), { -1, 0, 0, 1 });
                yLocation.insert(yLocation.end(), { 9, 9, 10, 10 });
            }
            else
            {
                xLocation.insert(xLocation.end(), { 0, 0, 1, 1 });
                yLocation.insert(yLocation.end(), { 10, 9, 9, 8 });
            }
            break;
        }
        case TetriminoType::Z:
        {
            if (rotation == 0)
            {
                xLocation.insert(xLocation.end(), { -1, 0, 0, 1 });
                yLocation.insert(yLocation.end(), { 10, 10, 9, 9 });
            }
            else
            {
                xLocation.insert(xLocation.end(), { 0, 0, 1, 1 });
                yLocation.insert(yLocation.end(), { 8, 9, 9, 10 });
            }
            break;
        }
    }
}

//---------------------------------------------------------------

bool TetriminoCreator::IsCollidingWithOtherCubes(
    const std::vector<Cube*>& cubes,
    const std::vector<int>& xLocations,
    const std::vector<int>& yLocations,
    TetriminoCubeGroup& cubeGroup)
{
    for(const int xLocation : xLocations)
    {
        if (xLocation < -5 || xLocation > 5)
            return true;
    }

    for (const int yLocation : yLocations)
    {
        if (yLocation < -10 || yLocation > 10)
            return true;
    }

    const std::vector<TetriminoCube*> tetriminoCubes = cubeGroup.GetCubes();
    for (const auto cube : cubes)
    {
        if (cube->IsStatic())
            continue;

        const TetriminoCube* cubeEntity = dynamic_cast<TetriminoCube*>(cube);
        bool belongToCurrentGroup = false;
        for (const TetriminoCube* tetriminoCube : tetriminoCubes)
        {
            if (tetriminoCube == cubeEntity)
            {
                belongToCurrentGroup = true;
                break;
            }
        }
        if (belongToCurrentGroup)
            continue;
        for (int i = 0; i < 4; i++)
        {
            if (cubeEntity->GetYLocation() == yLocations[i] &&
                cubeEntity->GetXLocation() == xLocations[i])
                return true;
        }
    }
    return false;
}

//---------------------------------------------------------------
