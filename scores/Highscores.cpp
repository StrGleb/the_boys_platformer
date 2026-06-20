#include "Highscores.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Highscores::Highscores() : filename("config/highscores.txt") {
    loadScores();
}

void Highscores::loadScores() {
    scores.clear();
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string name;
    int score;
    while (file >> name >> score) {
        scores.push_back({name, score});
    }
    file.close();
}

void Highscores::saveScores() {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& entry : scores) {
        file << entry.name << " " << entry.score << "\n";
    }
    file.close();
}

void Highscores::addScore(const std::string& name, int score) {
    scores.push_back({name, score});
    
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });

    if (scores.size() > 5) {
        scores.resize(5);
    }

    saveScores();
}

void Highscores::printScores() const {
    std::cout << "\n=======================================================\n";
    std::cout << "                 ТАБЛИЦА REKOPДOB                      \n";
    std::cout << "=======================================================\n";
    if (scores.empty()) {
        std::cout << "Пока нет ни одного рекорда. Стань первым!\n";
    } else {
        for (size_t i = 0; i < scores.size(); ++i) {
            std::cout << i + 1 << ". " << scores[i].name << " — " << scores[i].score << " очков\n";
        }
    }
    std::cout << "=======================================================\n";
}
