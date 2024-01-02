#pragma once

#include <vector>

#include "Entity.h"
#include "Enums.h"

class TetriminoCreator
{
public:
    static void Create(std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY, const TetriminoType tetriminoType);
private:
    static void CreateITetrimino(std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY);
    /*static void CreateTTetrimino(double scaleFactorX, double scaleFactorY);
    static void CreateOTetrimino(double scaleFactorX, double scaleFactorY);
    static void CreateLTetrimino(double scaleFactorX, double scaleFactorY);
    static void CreateJTetrimino(double scaleFactorX, double scaleFactorY);
    static void CreateSTetrimino(double scaleFactorX, double scaleFactorY);
    static void CreateZTetrimino(double scaleFactorX, double scaleFactorY);*/
};
