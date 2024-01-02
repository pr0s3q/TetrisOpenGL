#include "TetriminoCreator.h"

#include <vector>

#include "Cube.h"
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
    positions.insert(positions.end(),
        {
             0.45 * scaleFactorX,  0.45 * scaleFactorY,
            -0.45 * scaleFactorX,  0.45 * scaleFactorY,
            -0.45 * scaleFactorX, -0.45 * scaleFactorY,
             0.45 * scaleFactorX, -0.45 * scaleFactorY
        });

    std::vector<float> colors;
    colors.reserve(4);
    colors.insert(colors.end(), { 1.0f , 0.0f , 0.0f , 1.0f });

    entities.emplace_back(new Cube(positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
             0.45 * scaleFactorX, 1.45 * scaleFactorY,
            -0.45 * scaleFactorX, 1.45 * scaleFactorY,
            -0.45 * scaleFactorX, 0.55 * scaleFactorY,
             0.45 * scaleFactorX, 0.55 * scaleFactorY
        });

    entities.emplace_back(new Cube(positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
             0.45 * scaleFactorX, 2.45 * scaleFactorY,
            -0.45 * scaleFactorX, 2.45 * scaleFactorY,
            -0.45 * scaleFactorX, 1.55 * scaleFactorY,
             0.45 * scaleFactorX, 1.55 * scaleFactorY
        });

    entities.emplace_back(new Cube(positions, colors));

    positions.clear();
    positions.insert(positions.end(),
        {
             0.45 * scaleFactorX, 3.45 * scaleFactorY,
            -0.45 * scaleFactorX, 3.45 * scaleFactorY,
            -0.45 * scaleFactorX, 2.55 * scaleFactorY,
             0.45 * scaleFactorX, 2.55 * scaleFactorY
        });

    entities.emplace_back(new Cube(positions, colors));
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
