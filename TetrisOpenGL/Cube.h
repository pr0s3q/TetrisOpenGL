#pragma once

#include "Entity.h"

class Cube : public Entity
{
public:

    //---------------------------------------------------------------

    Cube(bool staticImage, const std::vector<double>& positions, const std::vector<float>& colors);

    //---------------------------------------------------------------

    Cube(const std::vector<double>& positions, const std::vector<float>& colors);

    //---------------------------------------------------------------

    void Color() override;

    //---------------------------------------------------------------

    void Move(const double& /*scaleFactor*/, Key /*keyPressed*/) override;

    //---------------------------------------------------------------

    void MoveForce(const double& /*scaleFactor*/) override;

    //---------------------------------------------------------------

    void SetMove(bool shouldMove) override;

    //---------------------------------------------------------------

    static void InitShader();

    //---------------------------------------------------------------

    static void TerminateShader();

    //---------------------------------------------------------------

protected:

    //---------------------------------------------------------------

    double m_positions[12];

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    static void CompileShaders();

    //---------------------------------------------------------------
};