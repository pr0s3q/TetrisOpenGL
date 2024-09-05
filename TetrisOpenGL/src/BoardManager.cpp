#include <BoardManager.hpp>

//---------------------------------------------------------------

BoardManager BoardManager::s_boardManager;

//---------------------------------------------------------------

BoardManager::BoardManager()
    : m_coordinateMap(21)
{
    m_coordinateMap.insert({ 10, { 10.5, 9.5 } });
    m_coordinateMap.insert({ 9, { 9.5, 8.5 } });
    m_coordinateMap.insert({ 8, { 8.5, 7.5 } });
    m_coordinateMap.insert({ 7, { 7.5, 6.5 } });
    m_coordinateMap.insert({ 6, { 6.5, 5.5 } });
    m_coordinateMap.insert({ 5, { 5.5, 4.5 } });
    m_coordinateMap.insert({ 4, { 4.5, 3.5 } });
    m_coordinateMap.insert({ 3, { 3.5, 2.5 } });
    m_coordinateMap.insert({ 2, { 2.5, 1.5 } });
    m_coordinateMap.insert({ 1, { 1.5, 0.5 } });
    m_coordinateMap.insert({ 0, { 0.5, -0.5 } });
    m_coordinateMap.insert({ -1, { -0.5, -1.5 } });
    m_coordinateMap.insert({ -2, { -1.5, -2.5 } });
    m_coordinateMap.insert({ -3, { -2.5, -3.5 } });
    m_coordinateMap.insert({ -4, { -3.5, -4.5 } });
    m_coordinateMap.insert({ -5, { -4.5, -5.5 } });
    m_coordinateMap.insert({ -6, { -5.5, -6.5 } });
    m_coordinateMap.insert({ -7, { -6.5, -7.5 } });
    m_coordinateMap.insert({ -8, { -7.5, -8.5 } });
    m_coordinateMap.insert({ -9, { -8.5, -9.5 } });
    m_coordinateMap.insert({ -10, { -9.5, -10.5 } });
}

//---------------------------------------------------------------

std::pair<double, double> BoardManager::GetCoordinate(const int position)
{
    return s_boardManager.m_coordinateMap[position];
}

//---------------------------------------------------------------
