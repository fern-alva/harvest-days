#ifndef HARDY_CROP_H
#define HARDY_CROP_H

#include "Crop.h"
#include <iostream>
using namespace std;

class HardyCrop : public Crop {
public:
    HardyCrop(const string& name,
              int health,
              int days,
              int waterNeeded,
              float eventRisk)
        : Crop(name, health, days, waterNeeded, eventRisk) {}

    void onEvent(const string& eventType) override {
        if (eventType == "storm" || eventType == "drought") {
            cout << name << " resists the " << eventType << "!\n";
            changeHealth(0);
        } else {
            Crop::onEvent(eventType);
        }
    }

    void grow() override {
        if (daysToHarvest > 0) {
            --daysToHarvest;
            cout << name << " grows steadily. Days to harvest: "
                 << daysToHarvest << "\n";
        }
    }
};

#endif