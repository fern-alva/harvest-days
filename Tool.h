#ifndef TOOL_H
#define TOOL_H

#include <string>
using namespace std;

class Tool {
private:
    string name;
    int xpBonus;
    int waterBonus;
    int attackBonus;
    int defenseBonus;
    string specialEffect;

public:
    Tool(const string& name,
         int xpB,
         int waterB,
         int attackB,
         int defenseB,
         const string& effect = "none");

    string getName() const;
    int    getExperienceBonus() const;
    int    getWaterBonus() const;
    int    getAttackBonus() const;
    int    getDefenseBonus() const;
    string getSpecialEffect() const { return specialEffect; }
    bool   isEffectiveAgainst(const string& eventType) const;
};

#endif
