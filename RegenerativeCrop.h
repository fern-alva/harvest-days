#ifndef REGENERATIVE_CROP_H
#define REGENERATIVE_CROP_H

#include "Crop.h"
#include <iostream>
using namespace std;

class RegenerativeCrop : public Crop {
public:
    RegenerativeCrop(const string& name,
                     int health,
                     int days,
                     int waterNeeded,
                     float eventRisk)
        : Crop(name, health, days, waterNeeded, eventRisk) {}

    void grow() override {
        if (daysToHarvest > 0) {
            --daysToHarvest;
            if ((float)rand() / RAND_MAX < 0.4) {
                changeHealth(1);
                cout << name << " regenerates some health! Current health: " 
                     << health << "\n";
            }
            cout << name << " grows. Days to harvest: "
                 << daysToHarvest << "\n";
        }
    }

    void onEvent(const string& eventType) override {
        Crop::onEvent(eventType);
        if ((float)rand() / RAND_MAX < 0.3) {
            changeHealth(1);
            cout << name << " recovers some health after the " 
                 << eventType << "! Health: " << health << "\n";
        }
    }
};

#endif