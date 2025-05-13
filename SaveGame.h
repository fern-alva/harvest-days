#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include <string>
#include <fstream>
#include "Player.h"

class SaveGame {
public:
    static bool saveToFile(const Player& player, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        file << player.getXP() << std::endl
             << player.getMoney() << std::endl
             << player.getWater() << std::endl
             << player.getFertilizer() << std::endl
             << player.getDefense() << std::endl;

        return file.good();
    }

    static bool loadFromFile(Player& player, const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        int xp, money, water, fertilizer, defense;
        if (!(file >> xp >> money >> water >> fertilizer >> defense)) {
            return false;
        }

        player.setXP(xp);
        player.setMoney(money);
        player.setWater(water);
        player.setFertilizer(fertilizer);
        player.setDefense(defense);

        return true;
    }
};

#endif