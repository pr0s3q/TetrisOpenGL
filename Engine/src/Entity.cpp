#include "Entity.h"

//---------------------------------------------------------------

Entity::Entity(const std::vector<double>& positions, const int imageId)
{
    // Cube position
    m_positions[0] = positions[0];
    m_positions[1] = positions[1];
    m_positions[4] = positions[2];
    m_positions[5] = positions[3];
    m_positions[8] = positions[4];
    m_positions[9] = positions[5];
    m_positions[12] = positions[6];
    m_positions[13] = positions[7];

    // Position of image
    // (X,  Y)
    // (2,  3)  Left bottom
    // (6,  7)  Right bottom
    // (10, 11) Left top
    // (14, 15) Right top

    std::vector<double> imageCoords;
    GetImageCoords(imageId, imageCoords);

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

void Entity::GetImageCoords(const int imageID, std::vector<double>& coords)
{
    coords.reserve(8);
    coords.insert(coords.end(), { 0.0, 0.0, 1.0, 0.0, 0.0, 24.22222, 1.0, 24.22222 });
    // switch (imageID)
    // {
    //     case 1:
    //     {
    //         // Blue square
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.0, 0.12, 0.125, 0.12, 0.0, 0.16, 0.125, 0.16 });
    //         break;
    //     }
    //     case 2:
    //     {
    //         // Blue bar - len 21
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.0, 0.16, 0.125, 0.16, 0.0, 1.0, 0.125, 1.0 });
    //         break;
    //     }
    //     case 3:
    //     {
    //         // Blue bar - len 11, rot 90 deg anti clockwise
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.125, 1.0, 0.125, 0.56, 0.25, 1.0, 0.25, 0.56 });
    //         break;
    //     }
    //     case 4:
    //     {
    //         // Yellow square
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.25, 0.12, 0.375, 0.12, 0.25, 0.16, 0.375, 0.16 });
    //         break;
    //     }
    //     case 5:
    //     {
    //         // Yellow bar - len 21
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.25, 0.16, 0.375, 0.16, 0.25, 1.0, 0.375, 1.0 });
    //         break;
    //     }
    //     case 6:
    //     {
    //         // Yellow bar - len 11, rot 90 deg anti clockwise
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.375, 1.0, 0.375, 0.56, 0.5, 1.0, 0.5, 0.56 });
    //         break;
    //     }
    //     case 7:
    //     {
    //         // Green square
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.5, 0.12, 0.625, 0.12, 0.5, 0.16, 0.625, 0.16 });
    //         break;
    //     }
    //     case 8:
    //     {
    //         // Green bar - len 21
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.5, 0.12, 0.625, 0.12, 0.5, 0.12 + 0.04 * 24.222222, 0.625, 0.12 + 0.04
    //         * 24.222222 }); break;
    //     }
    //     case 9:
    //     {
    //         // Green bar - len 11, rot 90 deg anti clockwise
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.625, 1.0, 0.625, 0.56, 0.75, 1.0, 0.75, 0.56 });
    //         break;
    //     }
    //     case 10:
    //     {
    //         // Red square
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.75, 0.12, 0.875, 0.12, 0.75, 0.16, 0.875, 0.16 });
    //         break;
    //     }
    //     case 11:
    //     {
    //         // Red bar - len 21
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.75, 0.16, 0.875, 0.16, 0.75, 1.0, 0.875, 1.0 });
    //         break;
    //     }
    //     case 12:
    //     {
    //         // Red bar - len 11, rot 90 deg anti clockwise
    //         coords.reserve(8);
    //         coords.insert(coords.end(), { 0.875, 1.0, 0.875, 0.56, 1.0, 1.0, 1.0, 0.56 });
    //         break;
    //     }
    //     default:
    //     {
    //         coords.clear();
    //         break;
    //     }
    // }
}

//---------------------------------------------------------------
