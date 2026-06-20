#pragma once

#include <string>
#include <vector>

struct ScoreEntry {
    std::string name;
    int score;
};

class Highscores {
private:
    std::string filename;
    std::vector<ScoreEntry> scores;

    void loadScores();
    void saveScores();

public:
    Highscores();
    void addScore(const std::string& name, int score);
    void printScores() const;
};
