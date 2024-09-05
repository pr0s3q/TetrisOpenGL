#include <Engine/Entity.hpp>

//---------------------------------------------------------------

Entity::Entity(
    const std::vector<double>& positions,
    const int imageId,
    const double scaleFactorX,
    const double scaleFactorY)
    : m_imageID(imageId)
    , m_positions()
{
    // Cube position
    m_positions[0] = positions[0] * scaleFactorX;
    m_positions[1] = positions[1] * scaleFactorY;
    m_positions[4] = positions[2] * scaleFactorX;
    m_positions[5] = positions[3] * scaleFactorY;
    m_positions[8] = positions[4] * scaleFactorX;
    m_positions[9] = positions[5] * scaleFactorY;
    m_positions[12] = positions[6] * scaleFactorX;
    m_positions[13] = positions[7] * scaleFactorY;

    // Position of image
    // (X,  Y)
    // (2,  3)  Left bottom
    // (6,  7)  Right bottom
    // (10, 11) Left top
    // (14, 15) Right top

    m_noOfXRepetition = positions[0] - positions[2];
    m_noOfYRepetition = positions[1] - positions[5];

    m_baseImageCoords.reserve(8);
    m_baseImageCoords.insert(m_baseImageCoords.end(), { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0 });

    AssignImageCoords();
}

//---------------------------------------------------------------

void Entity::Mirror()
{
    double temp1 = m_positions[2];
    double temp2 = m_positions[3];
    m_positions[2] = m_positions[6];
    m_positions[3] = m_positions[7];
    m_positions[6] = temp1;
    m_positions[7] = temp2;
    temp1 = m_positions[10];
    temp2 = m_positions[11];
    m_positions[10] = m_positions[14];
    m_positions[11] = m_positions[15];
    m_positions[14] = temp1;
    m_positions[15] = temp2;
}

//---------------------------------------------------------------

void Entity::RotateCounterClockwise()
{
    AssignImageCoords();

    const double temp1 = m_positions[2];
    const double temp2 = m_positions[3];
    m_positions[2] = m_positions[10];
    m_positions[3] = m_positions[11];
    m_positions[10] = m_positions[14];
    m_positions[11] = m_positions[15];
    m_positions[14] = m_positions[6];
    m_positions[15] = m_positions[7];
    m_positions[6] = temp1;
    m_positions[7] = temp2;
}

//---------------------------------------------------------------

void Entity::RotateClockwise()
{
    const double rotationTemp = m_noOfXRepetition;
    m_noOfXRepetition = m_noOfYRepetition;
    m_noOfYRepetition = rotationTemp;

    AssignImageCoords();

    const double temp1 = m_positions[2];
    const double temp2 = m_positions[3];
    m_positions[2] = m_positions[6];
    m_positions[3] = m_positions[7];
    m_positions[6] = m_positions[14];
    m_positions[7] = m_positions[15];
    m_positions[14] = m_positions[10];
    m_positions[15] = m_positions[11];
    m_positions[10] = temp1;
    m_positions[11] = temp2;
}

//---------------------------------------------------------------

void Entity::AssignImageCoords()
{
    m_positions[2] = m_baseImageCoords[0];
    m_positions[3] = m_baseImageCoords[1];
    m_positions[6] = m_baseImageCoords[2];
    m_positions[7] = m_baseImageCoords[3];
    m_positions[10] = m_baseImageCoords[4];
    m_positions[11] = m_baseImageCoords[5];
    m_positions[14] = m_baseImageCoords[6];
    m_positions[15] = m_baseImageCoords[7];

    m_positions[6] *= m_noOfXRepetition;
    m_positions[11] *= m_noOfYRepetition;
    m_positions[14] *= m_noOfXRepetition;
    m_positions[15] *= m_noOfYRepetition;
}

//---------------------------------------------------------------
