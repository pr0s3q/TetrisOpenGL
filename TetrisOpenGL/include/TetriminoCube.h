#pragma once

#include <memory>

class ConnectedTetriminoCubes;
class Cube;

class TetriminoCube : public Cube
{
public:

    //---------------------------------------------------------------

    TetriminoCube(
        const std::shared_ptr<ConnectedTetriminoCubes>& connectedCubes,
        const std::vector<double>& positions,
        const std::vector<float>& colors,
        int xLocation,
        int yLocation);

    //---------------------------------------------------------------

    void ApplyRotationPositions(const std::vector<double>& positions, int xLocation, int yLocation);

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

    void SetXLocation(int location);

    //---------------------------------------------------------------

    void SetYLocation(int location);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    std::shared_ptr<ConnectedTetriminoCubes> m_connectedCubes;
    int m_xLocation;
    int m_yLocation;

    //---------------------------------------------------------------
};
