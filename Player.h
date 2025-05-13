#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Tool;
class Crop;

class Player {
private:
    std::string name;
    int experience;
    int water;
    int attack;
    int defense;
    int money;
    int fertilizer;

public:
    Player(const std::string& name);
    void waterCrop();
    void applyTool(const Tool& t);
    void gainXP(int xp);
    bool canAfford(int cost) const;
    int getDefense() const;
    void addMoney(int amount);
    int getMoney() const;
    int getXP() const;
    int getFertilizer() const;
    void fertilizeCrop(Crop& crop);
    int getWater() const;

    void setXP(int xp) { experience = xp; }
    void setMoney(int m) { money = m; }
    void setWater(int w) { water = w; }
    void setFertilizer(int f) { fertilizer = f; }
    void setDefense(int d) { defense = d; }
};

#endif
