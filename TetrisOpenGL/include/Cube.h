#pragma once

#include <vector>

#include <Entity.h>

#include <HelperDefinitions.h>

enum class Key;

class Cube : public Entity
{
public:

    //---------------------------------------------------------------

    Cube(
        bool staticImage,
        const std::vector<double>& positions,
        double scaleFactorX,
        double scaleFactorY,
        int imageId = CUBE_COLOR);

    //---------------------------------------------------------------

    Cube(const std::vector<double>& positions, double scaleFactorX, double scaleFactorY, int imageId = CUBE_COLOR);

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
