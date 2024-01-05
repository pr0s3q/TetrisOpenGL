#include <vector>

#include "BoardManager.h"
#include "TetriminoCreator.h"
#include "TetriminoCube.h"
#include "Tetris.h"

//---------------------------------------------------------------

void TetriminoCreator::Create(std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY, const TetriminoType tetriminoType)
{
    switch (tetriminoType)
    {
    case TetriminoType::I:
        CreateITetrimino(entities, scaleFactorX, scaleFactorY);
        break;
    /*case T:
        CreateTTetrimino();
        break;
    case O:
        CreateOTetrimino();
        break;
    case L:
        CreateLTetrimino();
        break;
    case J:
        CreateJTetrimino();
        break;
    case S:
        CreateSTetrimino();
        break;
    case Z:
        CreateZTetrimino();
        break;*/
    }
}

//---------------------------------------------------------------

void TetriminoCreator::CreateITetrimino(std::vector<Entity*>& entities, const double scaleFactorX, const double scaleFactorY)
{
    std::vector<double> positions;
    positions.reserve(8);

    auto xCoord = BoardManager::GetCoordinate(0, scaleFactorX);
    auto yCoord = BoardManager::GetCoordinate(7, scaleFactorY);
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

    entities.emplace_back(new TetriminoCube(positions, colors, 0, 7));

    yCoord = BoardManager::GetCoordinate(8, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    entities.emplace_back(new TetriminoCube(positions, colors, 0, 8));

    yCoord = BoardManager::GetCoordinate(9, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    entities.emplace_back(new TetriminoCube(positions, colors, 0, 9));

    yCoord = BoardManager::GetCoordinate(10, scaleFactorY);
    positions.clear();
    positions.insert(positions.end(),
        {
            xCoord.first,  yCoord.first,
            xCoord.second, yCoord.first,
            xCoord.second, yCoord.second,
            xCoord.first,  yCoord.second
        });

    entities.emplace_back(new TetriminoCube(positions, colors, 0, 10));
}

//void TetriminoCreator::CreateTTetrimino(double scaleFactorX, double scaleFactorY)
//{
//}
//
//void TetriminoCreator::CreateOTetrimino(double scaleFactorX, double scaleFactorY)
//{
//}
//
//void TetriminoCreator::CreateLTetrimino(double scaleFactorX, double scaleFactorY)
//{
//}
//
//void TetriminoCreator::CreateJTetrimino(double scaleFactorX, double scaleFactorY)
//{
//}
//
//void TetriminoCreator::CreateSTetrimino(double scaleFactorX, double scaleFactorY)
//{
//}
//
//void TetriminoCreator::CreateZTetrimino(double scaleFactorX, double scaleFactorY)
//{
//}
