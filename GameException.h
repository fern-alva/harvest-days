#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <exception>

class OutOfWaterException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Out of water!";
    }
};

class OutOfFertilizerException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Out of fertilizer!";
    }
};

#endif
