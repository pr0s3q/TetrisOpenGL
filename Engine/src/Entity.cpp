#include "Entity.h"

//---------------------------------------------------------------

Entity::Entity(
    const std::vector<double>& positions,
    const int imageId,
    const double scaleFactorX,
    const double scaleFactorY)
    : m_imageID(imageId)
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

    const double noOfXRepetition = positions[0] - positions[2];
    const double noOfYRepetition = positions[1] - positions[5];

    std::vector<double> imageCoords;
    imageCoords.reserve(8);
    imageCoords.insert(
        imageCoords.end(),
        { 0.0,
          0.0,
          1.0 * noOfXRepetition,
          0.0,
          0.0,
          1.0 * noOfYRepetition,
          1.0 * noOfXRepetition,
          1.0 * noOfYRepetition });

    m_positions[2] = imageCoords[0];
    m_positions[3] = imageCoords[1];
    m_positions[6] = imageCoords[2];
    m_positions[7] = imageCoords[3];
    m_positions[10] = imageCoords[4];
    m_positions[11] = imageCoords[5];
    m_positions[14] = imageCoords[6];
    m_positions[15] = imageCoords[7];
}

//---------------------------------------------------------------
