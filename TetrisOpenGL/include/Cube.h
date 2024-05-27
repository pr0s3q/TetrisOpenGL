﻿#pragma once

#include <vector>

#include "Entity.h"
#include "HelperDefinitions.h"

enum class Key;

class Cube : public Entity
{
public:

    //---------------------------------------------------------------

    Cube(
        bool staticImage,
        const std::vector<double>& positions,
        const double scaleFactorX,
        const double scaleFactorY,
        const int imageId = CUBE_COLOR);

    //---------------------------------------------------------------

    Cube(
        const std::vector<double>& positions,
        const double scaleFactorX,
        const double scaleFactorY,
        const int imageId = CUBE_COLOR);

    //---------------------------------------------------------------

    virtual ~Cube() override = default;

    //---------------------------------------------------------------

    virtual bool IsStatic();

    //---------------------------------------------------------------

    virtual void Move(const double& /*scaleFactor*/, Key /*keyPressed*/);

    //---------------------------------------------------------------

    virtual void MoveForce(const double& /*scaleFactor*/);

    //---------------------------------------------------------------

    void SetMove(bool shouldMove);

    //---------------------------------------------------------------

protected:

    //---------------------------------------------------------------

    bool m_shouldMove;
    bool m_staticImage = false;
};
