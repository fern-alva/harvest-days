#include "EventManager.h"
#include <cstdlib>

int EventManager::generateSeverity() {
    float r = (float)rand() / RAND_MAX;
    if (r < 0.6f) return 1;
    if (r < 0.9f) return 2;
    return 3;
}

std::unique_ptr<Event> EventManager::generateRandomEvent() {
    float r = (float)rand() / RAND_MAX;
    int severity = generateSeverity();
    
    if (r < 0.2f) {
        return make_unique<Event>("pestAttack", 1, false, severity, "defend");
    }
    if (r < 0.4f) {
        return make_unique<Event>("storm", 1, false, severity, "shelter");
    }
    if (r < 0.55f) {
        return make_unique<Event>("drought", 1, false, severity, "water");
    }
    if (r < 0.7f) {
        return make_unique<Event>("fungalInfection", 1, false, severity, "treat");
    }
    
    if (r < 0.85f) {
        return make_unique<Event>("rain", 1, true, 1, "none");
    }
    return make_unique<Event>("sunshine", 1, true, 1, "none");
}