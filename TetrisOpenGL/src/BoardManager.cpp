#include "BoardManager.h"

//---------------------------------------------------------------

BoardManager BoardManager::s_boardManager;

//---------------------------------------------------------------

BoardManager::BoardManager()
    : m_coordinateMap(21)
{
    m_coordinateMap.insert({ 10, { 10.45, 9.55 } });
    m_coordinateMap.insert({ 9, { 9.45, 8.55 } });
    m_coordinateMap.insert({ 8, { 8.45, 7.55 } });
    m_coordinateMap.insert({ 7, { 7.45, 6.55 } });
    m_coordinateMap.insert({ 6, { 6.45, 5.55 } });
    m_coordinateMap.insert({ 5, { 5.45, 4.55 } });
    m_coordinateMap.insert({ 4, { 4.45, 3.55 } });
    m_coordinateMap.insert({ 3, { 3.45, 2.55 } });
    m_coordinateMap.insert({ 2, { 2.45, 1.55 } });
    m_coordinateMap.insert({ 1, { 1.45, 0.55 } });
    m_coordinateMap.insert({ 0, { 0.45, -0.45 } });
    m_coordinateMap.insert({ -1, { -0.55, -1.45 } });
    m_coordinateMap.insert({ -2, { -1.55, -2.45 } });
    m_coordinateMap.insert({ -3, { -2.55, -3.45 } });
    m_coordinateMap.insert({ -4, { -3.55, -4.45 } });
    m_coordinateMap.insert({ -5, { -4.55, -5.45 } });
    m_coordinateMap.insert({ -6, { -5.55, -6.45 } });
    m_coordinateMap.insert({ -7, { -6.55, -7.45 } });
    m_coordinateMap.insert({ -8, { -7.55, -8.45 } });
    m_coordinateMap.insert({ -9, { -8.55, -9.45 } });
    m_coordinateMap.insert({ -10, { -9.55, -10.45 } });
}

//---------------------------------------------------------------

std::pair<double, double> BoardManager::GetCoordinate(const int position, const double scaleFactor)
{
    auto pair = s_boardManager.m_coordinateMap[position];
    pair.first *= scaleFactor;
    pair.second *= scaleFactor;
    return pair;
}

//---------------------------------------------------------------
