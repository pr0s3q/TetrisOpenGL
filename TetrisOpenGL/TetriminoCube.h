#pragma once

#include "Cube.h"

class TetriminoCube : public Cube
{
public:

    //---------------------------------------------------------------

    TetriminoCube(const std::vector<double>& positions, const std::vector<float>& colors, int xLocation, int yLocation);

    //---------------------------------------------------------------

    int GetXLocation() const;

    //---------------------------------------------------------------

    int GetYLocation() const;

    //---------------------------------------------------------------

    void Move(const double& scaleFactor, const Key keyPressed) override;

    //---------------------------------------------------------------

    void SetXLocation(int location);

    //---------------------------------------------------------------

    void SetYLocation(int location);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    int m_xLocation;

    //---------------------------------------------------------------

    int m_yLocation;

    //---------------------------------------------------------------
};
