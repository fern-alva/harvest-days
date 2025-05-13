#ifndef FRAGILE_CROP_H
#define FRAGILE_CROP_H

#include "Crop.h"
#include <iostream>
using namespace std;

class FragileCrop : public Crop {
public:
    FragileCrop(const string& name,
                int health,
                int days,
                int waterNeeded,
                float eventRisk)
      : Crop(name, health, days, waterNeeded, eventRisk) {}

    void onEvent(const string& eventType) override {
        if (eventType == "pestAttack") {
            cout << name << " is extra vulnerable to pests!\n";
            changeHealth(-2);
            cout << name << " health is now " << health << "\n";
        }
        else {
            Crop::onEvent(eventType);
        }
    }
};

#endif
