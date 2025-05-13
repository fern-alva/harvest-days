#ifndef FAST_GROWING_CROP_H
#define FAST_GROWING_CROP_H

#include "Crop.h"
#include <iostream>
using namespace std;

class FastGrowingCrop : public Crop {
public:
    FastGrowingCrop(const string& name,
                    int health,
                    int days,
                    int waterNeeded,
                    float eventRisk)
        : Crop(name, health, days, waterNeeded, eventRisk) {}

    void grow() override {
        if (daysToHarvest > 0) {
            if ((float)rand() / RAND_MAX < 0.3) {
                daysToHarvest -= 2;
                cout << name << " grows rapidly! Days to harvest: "
                     << daysToHarvest << "\n";
            } else {
                --daysToHarvest;
                cout << name << " grows. Days to harvest: "
                     << daysToHarvest << "\n";
            }
        }
    }

    void onEvent(const string& eventType) override {
        if (eventType != "rain") {
            cout << name << " is fragile and takes extra damage from " << eventType << "!\n";
            changeHealth(-2);
        } else {
            Crop::onEvent(eventType);
        }
    }
};

#endif