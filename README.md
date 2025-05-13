# Harvest Days

A text-based farming simulation game written in C++ where players manage crops, deal with random events, and try to build a successful farm.

## Features

- **Diverse Crop System**: Multiple crop types with unique characteristics
  - Hardy Crops: Weather resistant and durable
  - Fast Growing Crops: Quick harvest cycles but require careful attention
  - Fragile Crops: High value but susceptible to damage
  - Regenerative Crops: Special healing properties

- **Event System**: Dynamic gameplay with random events
  - Weather events affecting crop growth
  - Pest invasions
  - Disease outbreaks
  - Farm management challenges

- **Resource Management**
  - Water management
  - Tools and equipment usage
  - Player stats and experience tracking
  - In-game currency system

- **Save System**: Save and load game progress

## Building the Game

### Prerequisites
- C++ compiler (supporting C++11 or later)
- Make build system

### Compilation
```bash
make
```

The executable will be created in the `build/` directory as `harvest_days`.

### Running the Game
```bash
./build/harvest_days
```

## Project Structure

- `main.cpp` - Game entry point and main loop
- `Player.h/cpp` - Player state and actions
- `Crop.h/cpp` - Base crop management
- `Event.h/cpp` - Event system implementation
- `EventManager.h/cpp` - Event handling and scheduling
- `Tool.h/cpp` - Tools and equipment system
- `SaveGame.h` - Save/load game functionality
- Specialized crop types:
  - `FastGrowingCrop.h`
  - `FragileCrop.h`
  - `HardyCrop.h`
  - `RegenerativeCrop.h`

## Save Files

Game progress is automatically saved to `savegame.txt`, storing:
- Player progress and stats
- Current crops and their status
- Resource levels
- Game state

## Development

### Clean Build
To clean build files:
```bash
make clean
```

## Game Controls

Interact with the game through text commands. Follow the in-game prompts to:
- Plant and manage different crop types
- Use tools and resources
- Respond to random events
- Save your progress
