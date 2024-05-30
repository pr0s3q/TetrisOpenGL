#pragma once

#include <vector>

class Entity
{
    friend class Game;

    //---------------------------------------------------------------

public:

    //---------------------------------------------------------------

    Entity(
        const std::vector<double>& positions,
        const int imageId,
        const double scaleFactorX,
        const double scaleFactorY);

    //---------------------------------------------------------------

    virtual ~Entity() = default;

    //---------------------------------------------------------------

    // Mirror image texture
    void Mirror();

    //---------------------------------------------------------------

    // Rotate counterclockwise image texture
    void RotateCounterClockwise();

    //---------------------------------------------------------------

    // Rotate clockwise image texture
    void RotateClockwise();

    //---------------------------------------------------------------

protected:

    //---------------------------------------------------------------

    double m_positions[16];

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    void AssignImageCoords();

    //---------------------------------------------------------------

    int m_imageID;
    double m_noOfXRepetition;
    double m_noOfYRepetition;
    std::vector<double> m_baseImageCoords;

    //---------------------------------------------------------------
};
