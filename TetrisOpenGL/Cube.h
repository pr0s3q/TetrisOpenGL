#pragma once

#include "Entity.h"

class Cube : public Entity
{
public:

    //---------------------------------------------------------------

    Cube(const std::vector<double>& positions, const std::vector<float>& colors);

    //---------------------------------------------------------------

    void Color() override;

    //---------------------------------------------------------------

    void Move(const double& scaleFactor, Key keyPressed) override;

    //---------------------------------------------------------------

    void SetMove(const bool shouldMove) override;

    //---------------------------------------------------------------

    static void InitShader();

    //---------------------------------------------------------------

    static void TerminateShader();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    static void CompileShaders();

    //---------------------------------------------------------------

    double m_positions[12];

    //---------------------------------------------------------------
};