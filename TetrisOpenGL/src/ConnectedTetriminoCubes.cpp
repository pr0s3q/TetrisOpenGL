#include "ConnectedTetriminoCubes.h"

ConnectedTetriminoCubes::ConnectedTetriminoCubes()
{
    
}

void ConnectedTetriminoCubes::AddCubes(std::vector<std::shared_ptr<TetriminoCube>>& cubes)
{
    m_cubes.reserve(4);
    m_cubes.insert(m_cubes.end(), { cubes[0], cubes[1], cubes[2], cubes[3] });
}
