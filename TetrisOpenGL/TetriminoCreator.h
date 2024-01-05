#pragma once

#include <vector>

#include "Entity.h"
#include "Enums.h"
#include "TetriminoCubeGroup.h"

class TetriminoCreator
{
public:

    //---------------------------------------------------------------

    static void Create(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    static void CreateITetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY);

    //---------------------------------------------------------------

    static void CreateTTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY);

    //---------------------------------------------------------------

    static void CreateOTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY);

    //---------------------------------------------------------------

    static void CreateLTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY);

    //---------------------------------------------------------------

    static void CreateJTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY);

    //---------------------------------------------------------------

    static void CreateSTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY);

    //---------------------------------------------------------------

    static void CreateZTetrimino(TetriminoCubeGroup& cubeGroup, std::vector<Entity*>& entities, double scaleFactorX, double scaleFactorY);

    //---------------------------------------------------------------
};
