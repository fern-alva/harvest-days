#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <memory>
#include "Event.h"

class EventManager {
public:
    static std::unique_ptr<Event> generateRandomEvent();
    static float generateTreasureChance() { return 0.1f; }
    static Event generateTreasureEvent() { return Event("treasureFound", 10, true); }

private:
    static int generateSeverity();
    
    template<typename T, typename... Args>
    static std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
};

#endif