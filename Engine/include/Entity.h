﻿#pragma once

#include <vector>

class Entity
{
    friend class Game;

    //---------------------------------------------------------------

public:

    //---------------------------------------------------------------

    Entity(const std::vector<double>& positions, const int imageId);

    //---------------------------------------------------------------

    virtual ~Entity() = default;

    //---------------------------------------------------------------

protected:

    //---------------------------------------------------------------

    double m_positions[16];

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    static void GetImageCoords(int imageID, std::vector<double>& coords);

    //---------------------------------------------------------------
};