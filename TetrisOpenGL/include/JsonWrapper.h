#pragma once

#include <string>
#include <vector>

//---------------------------------------------------------------

struct Score
{
    std::string playerName;
    int score;
};

//---------------------------------------------------------------

class JsonWrapper
{
public:

    //---------------------------------------------------------------

    JsonWrapper() = default;

    //---------------------------------------------------------------

    /// <summary>
    /// Get vector of all scores
    /// </summary>
    /// <returns></returns>
    std::vector<Score>* GetScores();

    //---------------------------------------------------------------

    /// <summary>
    /// Load scores saved in file
    /// </summary>
    void LoadFromFile();

    //---------------------------------------------------------------

    /// <summary>
    /// Save score to score file, and add score to scores vector
    /// </summary>
    /// <param name="name">Player name</param>
    /// <param name="score"></param>
    void SaveToFile(const std::string& name, const int& score);

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    std::vector<Score> m_scores;

    //---------------------------------------------------------------
};
