#ifndef CROP_H
#define CROP_H

#include <string>
using namespace std;

class Crop {
protected:
    string name;
    int health;
    int daysToHarvest;
    int waterNeeded;
    float eventRisk;

public:
    Crop(const string& name, int health, int days, int waterNeeded, float eventRisk);
    
    virtual void grow();
    virtual void onEvent(const string& eventType);
    bool isReady() const;
    void changeHealth(int delta);

    string getName() const;
    int getHealth() const;
    int getDaysToHarvest() const;
    int getWaterNeeded() const;
    float getEventRisk() const;

    virtual ~Crop() = default;
};

#endif
