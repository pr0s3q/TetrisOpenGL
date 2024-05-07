#pragma once

#include <memory>
#include <vector>

class ImageCoordManager
{
public:

    static void GetImageCoords(const int imageID, std::vector<double>& coords);
};
