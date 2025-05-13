#include "Event.h"
#include "Crop.h"
#include "Player.h"
#include "Tool.h"
#include <iostream>
#include <algorithm>
using namespace std;

Event::Event(const string& name, int strength, bool good, int sev, const string& action)
  : eventName(name),
    effectStrength(strength),
    isPositive(good),
    severity(sev),
    requiredAction(action),
    counterApplied(false),
    turnsRemaining(1)  
{
    if (name == "drought") turnsRemaining = 3;
    else if (name == "fungalInfection") turnsRemaining = 2;
    else if (name == "pestAttack") turnsRemaining = 2;
}

void Event::applyCounter(const Tool& tool) {
    if (tool.isEffectiveAgainst(eventName)) {
        cout << "The " << tool.getName() << " will help protect against the " 
             << eventName << " for " << turnsRemaining << " days!\n";
        counterApplied = true;
        turnsRemaining = max(1, turnsRemaining - 1);
    }
}

void Event::applyToCrop(Crop& crop) {
    if (!isActive()) return;
    
    int damage = counterApplied ? effectStrength/2 : effectStrength;
    damage = damage * severity;
    
    if (eventName == "rain") {
        cout << "A gentle rain waters the crop naturally!\n";
        crop.changeHealth(1);
    }
    else if (eventName == "drought") {
        cout << "Drought continues! (Severity: " << severity 
             << ", " << turnsRemaining << " days remaining) - Need to water extra!\n";
        crop.changeHealth(-damage);
    }
    else if (eventName == "storm") {
        cout << "Storm continues! (Severity: " << severity;
        if (counterApplied) {
            cout << ", Protected) - Reduced damage!\n";
        } else {
            cout << ") - Need protection!\n";
        }
        crop.changeHealth(-damage);
    }
    else if (eventName == "fungalInfection") {
        cout << "Fungal infection spreads! (Severity: " << severity 
             << ", " << turnsRemaining << " days remaining)";
        if (counterApplied) {
            cout << " - Treatment is helping!\n";
        } else {
            cout << " - Need treatment!\n";
        }
        crop.changeHealth(-damage);
    }
    else if (eventName == "sunshine") {
        cout << "Perfect sunny weather helps the crop thrive!\n";
        crop.changeHealth(1);
    }
    
    decrementTurns();
}

void Event::applyToCrop(Crop& crop, const Player& player) {
    if (!isActive()) return;

    if (eventName == "pestAttack") {
        int baseDamage = effectStrength * severity;
        int damage = baseDamage - player.getDefense();
        if (counterApplied) damage = damage / 2;
        if (damage < 0) damage = 0;
        
        cout << "Pest attack continues! (Severity: " << severity 
             << ", " << turnsRemaining << " days remaining) - ";
        if (counterApplied) {
            cout << "Your defenses are holding!\n";
        } else if (player.getDefense() >= baseDamage) {
            cout << "Your natural defenses help!\n";
        } else {
            cout << "Need better defenses!\n";
        }
        cout << "Deals " << damage << " damage after defense.\n";
        crop.changeHealth(-damage);
    } 
    else if (eventName == "storm") {
        int baseDamage = effectStrength * severity;
        int damage = baseDamage - (player.getDefense() / 2);
        if (counterApplied) damage = damage / 2;
        if (damage < 0) damage = 0;
        
        cout << "Storm rages on! (Severity: " << severity << ") - ";
        if (counterApplied) {
            cout << "Your shelter is holding!\n";
        } else if (damage == 0) {
            cout << "Natural protection is working!\n";
        } else {
            cout << "Need better shelter!\n";
        }
        cout << "Storm deals " << damage << " damage after protection.\n";
        crop.changeHealth(-damage);
    }
    else {
        applyToCrop(crop);
    }
    
    decrementTurns();
}

void Event::applyToPlayer(Player& player) {
    if (!isActive()) return;

    int amount = effectStrength * severity;
    if (counterApplied) amount = amount / 2;
    
    if (eventName == "treasureFound") {
        cout << "You found a buried treasure worth $" << amount << "!\n";
        player.addMoney(amount);
    }
    else if (eventName == "toolFound") {
        cout << "You found a useful farming tool!\n";
        player.gainXP(amount);
    }
    else if (eventName == "pestAttack") {
        cout << "Pests continue to steal resources! Loss: $" << amount << "\n";
        player.addMoney(-amount);
    }
    
    decrementTurns();
}
