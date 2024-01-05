#pragma once

#include <unordered_map>

class BoardManager
{
public:

    //---------------------------------------------------------------

    BoardManager();

    //---------------------------------------------------------------

    static std::pair<double, double> GetCoordinate(const int position, const double scaleFactor);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    std::unordered_map<int, std::pair<double, double>> m_coordinateMap;

    static BoardManager s_boardManager;

    //---------------------------------------------------------------
};
