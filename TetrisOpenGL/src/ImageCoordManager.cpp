#include "ImageCoordManager.h"

void ImageCoordManager::GetImageCoords(const int imageID, std::vector<double>& coords)
{
    switch (imageID)
    {
        case 1:
        {
            // Blue square
            coords.reserve(8);
            coords.insert(coords.end(), { 0.0, 0.12, 0.125, 0.12, 0.0, 0.16, 0.125, 0.16 });
            break;
        }
        case 2:
        {
            // Blue bar - len 21
            coords.reserve(8);
            coords.insert(coords.end(), { 0.0, 0.16, 0.125, 0.16, 0.0, 1.0, 0.125, 1.0 });
            break;
        }
        case 3:
        {
            // Blue bar - len 11, rot 90 deg anti clockwise
            coords.reserve(8);
            coords.insert(coords.end(), { 0.125, 1.0, 0.125, 0.56, 0.25, 1.0, 0.25, 0.56 });
            break;
        }
        case 4:
        {
            // Yellow square
            coords.reserve(8);
            coords.insert(coords.end(), { 0.25, 0.12, 0.375, 0.12, 0.25, 0.16, 0.375, 0.16 });
            break;
        }
        case 5:
        {
            // Yellow bar - len 21
            coords.reserve(8);
            coords.insert(coords.end(), { 0.25, 0.16, 0.375, 0.16, 0.25, 1.0, 0.375, 1.0 });
            break;
        }
        case 6:
        {
            // Yellow bar - len 11, rot 90 deg anti clockwise
            coords.reserve(8);
            coords.insert(coords.end(), { 0.375, 1.0, 0.375, 0.56, 0.5, 1.0, 0.5, 0.56 });
            break;
        }
        case 7:
        {
            // Green square
            coords.reserve(8);
            coords.insert(coords.end(), { 0.5, 0.12, 0.625, 0.12, 0.5, 0.16, 0.625, 0.16 });
            break;
        }
        case 8:
        {
            // Green bar - len 21
            coords.reserve(8);
            coords.insert(coords.end(), { 0.5, 0.16, 0.625, 0.16, 0.5, 1.0, 0.625, 1.0 });
            break;
        }
        case 9:
        {
            // Green bar - len 11, rot 90 deg anti clockwise
            coords.reserve(8);
            coords.insert(coords.end(), { 0.625, 1.0, 0.625, 0.56, 0.75, 1.0, 0.75, 0.56 });
            break;
        }
        case 10:
        {
            // Red square
            coords.reserve(8);
            coords.insert(coords.end(), { 0.75, 0.12, 0.875, 0.12, 0.75, 0.16, 0.875, 0.16 });
            break;
        }
        case 11:
        {
            // Red bar - len 21
            coords.reserve(8);
            coords.insert(coords.end(), { 0.75, 0.16, 0.875, 0.16, 0.75, 1.0, 0.875, 1.0 });
            break;
        }
        case 12:
        {
            // Red bar - len 11, rot 90 deg anti clockwise
            coords.reserve(8);
            coords.insert(coords.end(), { 0.875, 1.0, 0.875, 0.56, 1.0, 1.0, 1.0, 0.56 });
            break;
        }
        default:
        {
            coords.clear();
            break;
        }
    }
}
