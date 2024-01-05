#include <vector>

#include "BoardManager.h"
#include "TetriminoCreator.h"

#include "TetriminoCube.h"
#include "Tetris.h"

//---------------------------------------------------------------

void TetriminoCreator::Create(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY)
{
    switch (static_cast<TetriminoType>(rand() % 7))
    {
    case TetriminoType::I:
        CreateITetrimino(cubeGroup, entities, scaleFactorX, scaleFactorY);
        break;
    case TetriminoType::T:
        CreateTTetrimino(cubeGroup, entities, scaleFactorX, scaleFactorY);
        break;
    case TetriminoType::O:
        CreateOTetrimino(cubeGroup, entities, scaleFactorX, scaleFactorY);
        break;
    case TetriminoType::L:
        CreateLTetrimino(cubeGroup, entities, scaleFactorX, scaleFactorY);
        break;
    case TetriminoType::J:
        CreateJTetrimino(cubeGroup, entities, scaleFactorX, scaleFactorY);
        break;
    case TetriminoType::S:
        CreateSTetrimino(cubeGroup, entities, scaleFactorX, scaleFactorY);
        break;
    case TetriminoType::Z:
        CreateZTetrimino(cubeGroup, entities, scaleFactorX, scaleFactorY);
        break;
    }
}

//---------------------------------------------------------------

void TetriminoCreator::CreateITetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY)
{
    std::vector<double> positions;
    positions.reserve(8);

    auto xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    auto yCoord = BoardManager::GetCoordinate(10, scaleFactorY);
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    auto cube = new TetriminoCube(positions, colors, 0, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    yCoord = BoardManager::GetCoordinate(9, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    yCoord = BoardManager::GetCoordinate(8, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 8);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    yCoord = BoardManager::GetCoordinate(7, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 7);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);
}

//---------------------------------------------------------------

void TetriminoCreator::CreateTTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY)
{
    std::vector<double> positions;
    positions.reserve(8);

    auto xCoord = BoardManager::GetCoordinate(-1, scaleFactorX);
    auto yCoord = BoardManager::GetCoordinate(10, scaleFactorY);
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    auto cube = new TetriminoCube(positions, colors, -1, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(1, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 1, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    yCoord = BoardManager::GetCoordinate(9, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);
}

//---------------------------------------------------------------

void TetriminoCreator::CreateOTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY)
{
    std::vector<double> positions;
    positions.reserve(8);

    auto xCoord = BoardManager::GetCoordinate(-1, scaleFactorX);
    auto yCoord = BoardManager::GetCoordinate(10, scaleFactorY);
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    auto cube = new TetriminoCube(positions, colors, -1, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(-1, scaleFactorX);
    yCoord = BoardManager::GetCoordinate(9, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, -1, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);
}

//---------------------------------------------------------------

void TetriminoCreator::CreateLTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY)
{
    std::vector<double> positions;
    positions.reserve(8);

    auto xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    auto yCoord = BoardManager::GetCoordinate(10, scaleFactorY);
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    auto cube = new TetriminoCube(positions, colors, 0, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    yCoord = BoardManager::GetCoordinate(9, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    yCoord = BoardManager::GetCoordinate(8, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 8);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(1, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 1, 8);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);
}

//---------------------------------------------------------------

void TetriminoCreator::CreateJTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY)
{
    std::vector<double> positions;
    positions.reserve(8);

    auto xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    auto yCoord = BoardManager::GetCoordinate(10, scaleFactorY);
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    auto cube = new TetriminoCube(positions, colors, 0, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    yCoord = BoardManager::GetCoordinate(9, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    yCoord = BoardManager::GetCoordinate(8, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 8);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(-1, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, -1, 8);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);
}

//---------------------------------------------------------------

void TetriminoCreator::CreateSTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY)
{
    std::vector<double> positions;
    positions.reserve(8);

    auto xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    auto yCoord = BoardManager::GetCoordinate(10, scaleFactorY);
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    auto cube = new TetriminoCube(positions, colors, 0, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(1, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 1, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    yCoord = BoardManager::GetCoordinate(9, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(-1, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, -1, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);
}

//---------------------------------------------------------------

void TetriminoCreator::CreateZTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY)
{
    std::vector<double> positions;
    positions.reserve(8);

    auto xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    auto yCoord = BoardManager::GetCoordinate(10, scaleFactorY);
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    auto cube = new TetriminoCube(positions, colors, 0, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(-1, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, -1, 10);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    yCoord = BoardManager::GetCoordinate(9, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 0, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);

    xCoord = BoardManager::GetCoordinate(1, scaleFactorX);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    cube = new TetriminoCube(positions, colors, 1, 9);
    entities.emplace_back(cube);
    cubeGroup.AddCube(cube);
}

//---------------------------------------------------------------
