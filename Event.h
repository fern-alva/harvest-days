#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <algorithm>
using namespace std;

class Tool;
class Crop;
class Player;

class Event {
private:
    string eventName;
    int    effectStrength;
    bool   isPositive;
    int    severity;    
    string requiredAction;
    bool   counterApplied;
    int    turnsRemaining;

public:
    Event(const string& name, int strength, bool good, int sev = 1, const string& action = "none");
    
    void applyToCrop(Crop& crop);
    void applyToCrop(Crop& crop, const Player& player);
    void applyToPlayer(Player& player);
    void applyCounter(const Tool& tool);
    
    bool isActive() const { return turnsRemaining > 0; }
    void decrementTurns() { if (turnsRemaining > 0) --turnsRemaining; }
    
    string getName() const { return eventName; }
    bool   positive() const { return isPositive; }
    int    getSeverity() const { return severity; }
    string getRequiredAction() const { return requiredAction; }
    int    getTurnsRemaining() const { return turnsRemaining; }
};

#endif
