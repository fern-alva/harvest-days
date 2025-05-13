#include "Tool.h"

Tool::Tool(const string& name, int xpB, int waterB, int attackB, int defenseB, const string& effect)
    : name(name), xpBonus(xpB), waterBonus(waterB), attackBonus(attackB), defenseBonus(defenseB), specialEffect(effect)
{}

string Tool::getName() const { 
    return name; 
}

int Tool::getExperienceBonus() const { 
    return xpBonus; 
}

int Tool::getWaterBonus() const { 
    return waterBonus; 
}

int Tool::getAttackBonus() const { 
    return attackBonus; 
}

int Tool::getDefenseBonus() const { 
    return defenseBonus; 
}

bool Tool::isEffectiveAgainst(const string& eventType) const {
    if (specialEffect == "pestControl" && eventType == "pestAttack") return true;
    if (specialEffect == "shelter" && eventType == "storm") return true;
    if (specialEffect == "irrigation" && eventType == "drought") return true;
    if (specialEffect == "fungicide" && eventType == "fungalInfection") return true;
    return false;
}
