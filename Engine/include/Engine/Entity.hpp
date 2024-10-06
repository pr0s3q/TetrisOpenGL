#pragma once

#include <vector>

class Entity
{
    //---------------------------------------------------------------

    friend class Game;

    //---------------------------------------------------------------

public:

    //---------------------------------------------------------------

    Entity(
        const std::vector<double>& positions,
        int imageId,
        int imageOffset,
        double scaleFactorX,
        double scaleFactorY);

    //---------------------------------------------------------------

    virtual ~Entity() = default;

    //---------------------------------------------------------------

    void SetImageOffset(unsigned char offset);

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

    Entity();

    //---------------------------------------------------------------

    double m_positions[16];

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    void AssignImageCoords();

    //---------------------------------------------------------------

    int m_imageID;
    unsigned char m_imageOffset;
    double m_noOfXRepetition;
    double m_noOfYRepetition;
    std::vector<double> m_baseImageCoords;

    //---------------------------------------------------------------
};
