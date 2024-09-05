#include <JsonWrapper.hpp>

#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

//---------------------------------------------------------------

std::vector<Score>* JsonWrapper::GetScores()
{
    return &m_scores;
}

//---------------------------------------------------------------

void JsonWrapper::LoadFromFile()
{
    m_scores.clear();
    // TODO: Improve performance by reserving std::vector based on number of entities in the file
    std::ifstream stream;
    stream.open("score.json");

    std::string line;
    while (std::getline(stream, line))
    {
        nlohmann::json j = nlohmann::json::parse(line);
        Score sc{
            j["playerName"].get<std::string>(),
            j["score"].get<int>(),
        };
        m_scores.emplace_back(sc);
    }
    stream.close();
}

//---------------------------------------------------------------

void JsonWrapper::SaveToFile(const std::string& name, const int& score)
{
    Score sc{ name, score };
    nlohmann::json j;
    j["playerName"] = sc.playerName;
    j["score"] = sc.score;

    std::ofstream stream;
    stream.open("score.json", std::ios::app);
    stream << j << "\n";
    stream.close();

    m_scores.emplace_back(sc);
}

//---------------------------------------------------------------
