#pragma once

#include <memory>
#include <vector>

class Cube;
class TetriminoCube;

enum class Key;
enum class TetriminoType;

class TetriminoCubeGroup
{
public:

    //---------------------------------------------------------------

    TetriminoCubeGroup();

    //---------------------------------------------------------------

    void AddCube(const std::shared_ptr<TetriminoCube>& cube);

    //---------------------------------------------------------------

    void ApplyRotationPositions(
        const std::vector<std::vector<double>>& positions,
        const std::vector<int>& xLocations,
        const std::vector<int>& yLocations,
        const int& rotation);

    //---------------------------------------------------------------

    bool CanBeMoved(const std::vector<std::shared_ptr<Cube>>& cubes, const Key keyPressed) const;

    //---------------------------------------------------------------

    std::vector<std::shared_ptr<TetriminoCube>>& GetCubes();

    //---------------------------------------------------------------

    int GetRotation() const;

    //---------------------------------------------------------------

    TetriminoType GetType() const;

    //---------------------------------------------------------------

    int GetXMovingFactor() const;

    //---------------------------------------------------------------

    int GetYMovingFactor() const;

    //---------------------------------------------------------------

    void MoveCubes(const std::vector<std::shared_ptr<Cube>>& cubes, const double& scaleFactor, const Key keyPressed);

    //---------------------------------------------------------------

    void ResetCubes();

    //---------------------------------------------------------------

    void SetMove(bool shouldMove) const;

    //---------------------------------------------------------------

    void SetType(TetriminoType type);

    //---------------------------------------------------------------

    bool ShouldBeMovable(const std::vector<std::shared_ptr<Cube>>& cubes) const;

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    std::vector<std::shared_ptr<TetriminoCube>> m_tetriminoCubes;
    TetriminoType m_type;
    int m_xMovingFactor;
    int m_yMovingFactor;
    int m_rotation;

    //---------------------------------------------------------------
};
