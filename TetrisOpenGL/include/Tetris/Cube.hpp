#pragma once

#include <Engine/Entity.hpp>

#include <vector>

#include <Tetris/Settings.hpp>

enum class Key;

class Cube : public Entity
{
public:

    //---------------------------------------------------------------

    Cube();

    //---------------------------------------------------------------

    Cube(
        bool staticImage,
        const std::vector<double>& positions,
        double scaleFactorX,
        double scaleFactorY,
        int imageId = Settings::GetCubeColor());

    //---------------------------------------------------------------

    Cube(
        const std::vector<double>& positions,
        double scaleFactorX,
        double scaleFactorY,
        int imageId = Settings::GetCubeColor());

    //---------------------------------------------------------------

    ~Cube() override = default;

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

    //---------------------------------------------------------------
};
