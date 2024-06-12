#pragma once

#include <memory>
#include <vector>

#include "Cube.h"

enum class Key;
class ConnectedTetriminoCubes;

class TetriminoCube : public Cube
{
public:

    //---------------------------------------------------------------

    TetriminoCube(
        const std::vector<double>& positions,
        int xLocation,
        int yLocation,
        double scaleFactorX,
        double scaleFactorY);

    //---------------------------------------------------------------

    void ApplyRotationPositions(
        const std::vector<double>& positions,
        int xLocation,
        int yLocation,
        const double& scaleFactorX,
        const double& scaleFactorY);

    //---------------------------------------------------------------

    bool CanBeMoved(Key keyPressed) const;

    //---------------------------------------------------------------

    int GetXLocation() const;

    //---------------------------------------------------------------

    int GetYLocation() const;

    //---------------------------------------------------------------

    void Move(const double& scaleFactor, Key keyPressed) override;

    //---------------------------------------------------------------

    void MoveForce(const double& scaleFactor) override;

    //---------------------------------------------------------------

    //---------------------------------------------------------------

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    int m_xLocation;
    int m_yLocation;

    //---------------------------------------------------------------
};
