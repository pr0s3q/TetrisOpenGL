#pragma once

#include <memory>
#include <vector>

class TetriminoCube;

class ConnectedTetriminoCubes
{
public:

    //---------------------------------------------------------------

    ConnectedTetriminoCubes() = default;

    //---------------------------------------------------------------

    void AddCubes(std::vector<std::shared_ptr<TetriminoCube>>& cubes);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    std::vector<std::shared_ptr<TetriminoCube>> m_cubes;
};
