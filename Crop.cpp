#include "Crop.h"
#include <iostream>
using namespace std;

Crop::Crop(const string& name,
           int health,
           int daysToHarvest,
           int waterNeeded,
           float eventRisk)
  : name(name),
    health(health),
    daysToHarvest(daysToHarvest),
    waterNeeded(waterNeeded),
    eventRisk(eventRisk)
{}

void Crop::grow() {
    if (daysToHarvest > 0) {
        --daysToHarvest;
        cout << name << " grows. Days to harvest: "
             << daysToHarvest << "\n";
    }
}

void Crop::onEvent(const string& eventType) {
    if (eventType == "pestAttack" || eventType == "drought" ||
        eventType == "storm"     || eventType == "fungalInfection") {
        --health;
        cout << name << " hit by " << eventType 
             << ". Health: " << health << "\n";
    } else {
        ++health;
        cout << name << " benefits from " << eventType 
             << ". Health: " << health << "\n";
    }
}

bool Crop::isReady() const {
    return (daysToHarvest <= 0) && (health > 0);
}

void Crop::changeHealth(int delta) {
    health += delta;
}

string Crop::getName() const        { return name; }
int    Crop::getHealth() const      { return health; }
int    Crop::getDaysToHarvest() const { return daysToHarvest; }
int    Crop::getWaterNeeded() const   { return waterNeeded; }
float  Crop::getEventRisk() const     { return eventRisk; }
