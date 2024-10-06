#pragma once

#include <Tetris/Cube.hpp>

#include <vector>

enum class Key;
class ConnectedTetriminoCubes;

class TetriminoCube final : public Cube
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

    [[nodiscard]] bool CanBeMoved(Key keyPressed) const;

    //---------------------------------------------------------------

    [[nodiscard]] int GetXLocation() const;

    //---------------------------------------------------------------

    [[nodiscard]] int GetYLocation() const;

    //---------------------------------------------------------------

    void Move(const double& scaleFactor, Key keyPressed) override;

    //---------------------------------------------------------------

    void MoveForce(const double& scaleFactor) override;

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    int m_xLocation;
    int m_yLocation;

    //---------------------------------------------------------------
};
