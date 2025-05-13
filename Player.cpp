#include "Player.h"
#include "Tool.h"
#include "Crop.h"
#include "GameException.h"
#include <iostream>
using namespace std;

Player::Player(const string& name) 
    : name(name), experience(0), water(5), attack(1), defense(1), money(100), fertilizer(3)
{}

void Player::waterCrop() {
    if (water > 0) {
        --water;
        cout << name << " waters the crop. " << water << " water remaining.\n";
    } else {
        throw OutOfWaterException();
    }
}

void Player::applyTool(const Tool& t) {
    water += t.getWaterBonus();
    attack += t.getAttackBonus();
    defense += t.getDefenseBonus();
    experience += t.getExperienceBonus();
    cout << name << " uses " << t.getName() << ".\n";
}

void Player::gainXP(int xp) {
    experience += xp;
    cout << name << " gained " << xp << " XP!\n";
}

bool Player::canAfford(int cost) const {
    return money >= cost;
}

int Player::getDefense() const {
    return defense;
}

void Player::addMoney(int amount) {
    money += amount;
}

int Player::getMoney() const {
    return money;
}

int Player::getXP() const {
    return experience;
}

int Player::getFertilizer() const {
    return fertilizer;
}

void Player::fertilizeCrop(Crop& crop) {
    if (fertilizer > 0) {
        --fertilizer;
        crop.changeHealth(2);
        cout << name << " fertilizes the crop. " << fertilizer << " fertilizer remaining.\n";
    } else {
        throw OutOfFertilizerException();
    }
}

int Player::getWater() const {
    return water;
}
