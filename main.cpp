#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Player.h"
#include "Tool.h"
#include "Event.h"
#include "EventManager.h"
#include "Crop.h"
#include "HardyCrop.h"
#include "FastGrowingCrop.h"
#include "RegenerativeCrop.h"
#include "FragileCrop.h"
#include "SaveGame.h"
#include "GameException.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BROWN   "\033[38;5;130m"

const char* BANNER = R"(
 __  __     ______     ______     __   __   ______     ______     ______      _____     ______     __  __     ______    
/\ \_\ \   /\  __ \   /\  == \   /\ \ / /  /\  ___\   /\  ___\   /\__  _\    /\  __-.  /\  __ \   /\ \_\ \   /\  ___\   
\ \  __ \  \ \  __ \  \ \  __<   \ \ \'/   \ \  __\   \ \___  \  \/_/\ \/    \ \ \/\ \ \ \  __ \  \ \____ \  \ \___  \  
 \ \_\ \_\  \ \_\ \_\  \ \_\ \_\  \ \__|    \ \_____\  \/\_____\    \ \_\     \ \____-  \ \_\ \_\  \/\_____\  \/\_____\ 
  \/_/\/_/   \/_/\/_/   \/_/ /_/   \/_/      \/_____/   \/_____/     \/_/      \/____/   \/_/\/_/   \/_____/   \/_____/ 
                                                                                                                        
)";

using namespace std;

vector<Tool> getAvailableTools(int playerXP) {
    vector<Tool> tools;
    int baseEffect = 1 + (playerXP / 20);
    tools.push_back(Tool("Scarecrow", 0, 0, baseEffect, 1, "pestControl"));
    tools.push_back(Tool("Greenhouse", 0, 0, 0, baseEffect + 1, "shelter"));
    tools.push_back(Tool("Sprinkler", 0, baseEffect, 0, 0, "irrigation"));
    tools.push_back(Tool("Fungicide Spray", 0, 0, baseEffect, 1, "fungicide"));
    return tools;
}

void handleEvent(Event& event, Player& player, Crop& crop) {
    if (!event.isActive()) return;
    
    cout << YELLOW << "\n--- EVENT UPDATE ---\n" << RESET;
    if (!event.positive()) {
        cout << event.getName() << " (Severity: " << event.getSeverity() 
             << ", Days remaining: " << event.getTurnsRemaining() << ")\n";
    }
    
    event.applyToCrop(crop, player);
}

int main() {
    srand((unsigned)time(nullptr));
    cout << BLUE << BANNER << RESET << "\n";
    cout << GREEN << "Welcome to Ferns Farm!" << RESET << "\n\n";
    cout << YELLOW
         << "Instructions:\n"
         << "Each day you can choose one of the following actions:\n"
         << "1) Water the crop (uses 1 water)\n"
         << "2) Fertilize the crop (uses 1 fertilizer, restores health)\n"
         << "3) Use a tool from your inventory\n"
         << "4) Check your stats (water, fertilizer, XP, defense, money)\n"
         << "5) Skip the day\n\n"
         << RESET;
    
    cout << "Would you like to load a saved game? (y/n): ";
    char loadChoice;
    cin >> loadChoice;
    cin.ignore();
    
    cout << "Enter your name: ";
    string name;
    getline(cin, name);
    Player player(name);
    
    if (loadChoice == 'y' || loadChoice == 'Y') {
        if (SaveGame::loadFromFile(player, "savegame.txt")) {
            cout << "Game loaded successfully!\n";
        } else {
            cout << "No saved game found or error loading game. Starting new game.\n";
        }
    }

    while (true) {
        const int seedCost = 20;
        if (!player.canAfford(seedCost)) {
            cout << "\nYou've run out of money to buy seeds. Game over.\n";
            break;
        }
        cout << "\nYou have $" << player.getMoney()
             << ". Seeds cost $" << seedCost << " each.\n";
        cout << "Buy a seed and choose your crop:\n";
        cout << " 1) Potato (Hardy, weather resistant)\n";
        cout << " 2) Strawberry (Fast growing but fragile)\n";
        cout << " 3) Lettuce (Can regenerate health)\n";
        cout << " 4) Corn (High yield but pest vulnerable)\n";
        cout << " 5) Save and Exit\n> ";
        int choice;
        cin >> choice;
        
        if (choice == 5) {
            if (SaveGame::saveToFile(player, "savegame.txt")) {
                cout << "Game saved successfully!\n";
            } else {
                cout << "Error saving game!\n";
            }
            cout << "Thanks for playing!\n";
            break;
        }

        player.addMoney(-seedCost);

        vector< unique_ptr<Crop> > options;
        options.emplace_back(new HardyCrop("Potato", 5, 5, 1, 0.10f));
        options.emplace_back(new FastGrowingCrop("Strawberry", 3, 4, 2, 0.25f));
        options.emplace_back(new RegenerativeCrop("Lettuce", 4, 6, 1, 0.05f));
        options.emplace_back(new FragileCrop("Corn", 4, 5, 2, 0.15f));

        if (choice < 1 || choice > (int)options.size()) {
            cout << "Invalid choice—defaulting to Potato.\n";
            choice = 1;
        }
        unique_ptr<Crop> crop = std::move(options[choice-1]);
        cout << "\nYou plant a " << crop->getName() << " seed.\n\n";
        
        if (crop->getName() == "Strawberry") {
            cout << RED
                 << "⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⡄⠀⠀⠀⠀⢀⠀⠀\n"
                 << "⠀⠀⠀⠀⠀⠀⣏⠓⠒⠤⣰⠋⠹⡄⠀⣠⠞⣿⠀⠀\n"
                 << "⠀⠀⠀⢀⠄⠂⠙⢦⡀⠐⠨⣆⠁⣷⣮⠖⠋⠉⠁⠀\n"
                 << "⠀⠀⡰⠁⠀⠮⠇⠀⣩⠶⠒⠾⣿⡯⡋⠩⡓⢦⣀⡀\n"
                 << "⠀⡰⢰⡹⠀⠀⠲⣾⣁⣀⣤⠞⢧⡈⢊⢲⠶⠶⠛⠁\n"
                 << "⢀⠃⠀⠀⠀⣌⡅⠀⢀⡀⠀⠀⣈⠻⠦⣤⣿⡀⠀⠀\n"
                 << "⠸⣎⠇⠀⠀⡠⡄⠀⠷⠎⠀⠐⡶⠁⠀⠀⣟⡇⠀⠀\n"
                 << "⡇⠀⡠⣄⠀⠷⠃⠀⠀⡤⠄⠀⠀⣔⡰⠀⢩⠇⠀⠀\n"
                 << "⡇⠀⠻⠋⠀⢀⠤⠀⠈⠛⠁⠀⢀⠉⠁⣠⠏⠀⠀⠀\n"
                 << "⣷⢰⢢⠀⠀⠘⠚⠀⢰⣂⠆⠰⢥⡡⠞⠁⠀⠀⠀⠀\n"
                 << "⠸⣎⠋⢠⢢⠀⢠⢀⠀⠀⣠⠴⠋⠀⠀⠀⠀⠀⠀⠀\n"
                 << "⠀⠘⠷⣬⣅⣀⣬⡷⠖⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                 << "⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                 << RESET << "\n";
        }

        int day = 1;
        unique_ptr<Event> currentEvent = nullptr;
        
        while (crop->getHealth() > 0 && !crop->isReady()) {
            cout << MAGENTA << "\n+------- Day " << day++ << " -------+\n" << RESET;
            cout << crop->getName()
                 << " (Health: "    << crop->getHealth()
                 << ", Days left: " << crop->getDaysToHarvest()
                 << ")\n";
                 
            if (currentEvent && currentEvent->isActive() && !currentEvent->positive()) {
                cout << "\nActive threat: " << currentEvent->getName() 
                     << " (Severity: " << currentEvent->getSeverity() 
                     << ", Days remaining: " << currentEvent->getTurnsRemaining()
                     << ") - Required action: " << currentEvent->getRequiredAction() 
                     << "\n\n";
            }
            
            cout << "1) Water   2) Fertilize   3) Use Tool   4) Check Stats   5) Skip   6) Save\n> ";
            int action;
            cin >> action;
            
            if (action == 6) {
                if (SaveGame::saveToFile(player, "savegame.txt")) {
                    cout << "Game saved successfully!\n";
                } else {
                    cout << "Error saving game!\n";
                }
                cout << "Exiting after save. Thanks for playing!\n";
                return 0;
            }
            
            if (action == 1) {
                try {
                    player.waterCrop();
                } catch (const OutOfWaterException& e) {
                    cout << RED << e.what() << RESET << "\n";
                }
            } else if (action == 2) {
                try {
                    player.fertilizeCrop(*crop);
                } catch (const OutOfFertilizerException& e) {
                    cout << RED << e.what() << RESET << "\n";
                }
            } else if (action == 3) {
                vector<Tool> tools = getAvailableTools(player.getXP());
                cout << "\nChoose a tool to use:\n";
                for (size_t i = 0; i < tools.size(); ++i) {
                    cout << i+1 << ") " << tools[i].getName();
                    string effect = tools[i].getSpecialEffect();
                    if (effect != "none") {
                        cout << " (effective against " << effect << ")";
                    }
                    cout << "\n";
                }
                int toolChoice;
                cin >> toolChoice;
                if (toolChoice > 0 && toolChoice <= (int)tools.size()) {
                    const Tool& selectedTool = tools[toolChoice-1];
                    player.applyTool(selectedTool);
                    
                    if (currentEvent) {
                        currentEvent->applyCounter(selectedTool);
                    }
                }
            } else if (action == 4) {
                cout << "\n--- " << name << "'s Stats ---\n"
                     << "Water: "      << player.getWater()      << "\n"
                     << "Fertilizer: " << player.getFertilizer() << "\n"
                     << "XP: "         << player.getXP()         << "\n"
                     << "Defense: "    << player.getDefense()    << "\n"
                     << "Money: $"     << player.getMoney()      << "\n\n";
            } else {
                cout << name << " skips.\n";
            }
            
            crop->grow();
            
            if (!currentEvent || !currentEvent->isActive()) {
                currentEvent = EventManager::generateRandomEvent();
                
                cout << "\n";
                if (currentEvent->positive()) {
                    cout << GREEN << "\n+++ EVENT ALERT +++\n" << RESET;
                } else {
                    cout << RED << "\n!!! EVENT ALERT !!!\n" << RESET;
                }
                cout << "WARNING: A " << currentEvent->getName() 
                     << " (Severity: " << currentEvent->getSeverity()
                     << ", Duration: " << currentEvent->getTurnsRemaining() << " days"
                     << ") is approaching!\n";
                cout << "Required action: " << currentEvent->getRequiredAction() << "\n\n";
            }
            
            if (currentEvent) {
                handleEvent(*currentEvent, player, *crop);
            }
            
            if ((float)rand() / RAND_MAX < EventManager::generateTreasureChance()) {
                Event treasureEvent = EventManager::generateTreasureEvent();
                treasureEvent.applyToPlayer(player);
            }
            
            cout << "\n";
        }

        if (crop->getHealth() <= 0) {
            cout << "Oh no—your crop died!\nGame over.\n";
            break;
        } else {
            cout << "You harvested your " << crop->getName() << "! \n";
            player.gainXP(10);
            player.addMoney(30);
            cout << "Now you have " << player.getXP()
                 << " XP and $" << player.getMoney() << ".\n";
        }

        cout << "\nPlant another crop? (y/n) ";
        char again;
        cin >> again;
        if (again != 'y' && again != 'Y') {
            cout << "Would you like to save before exiting? (y/n) ";
            char saveChoice;
            cin >> saveChoice;
            if (saveChoice == 'y' || saveChoice == 'Y') {
                if (SaveGame::saveToFile(player, "savegame.txt")) {
                    cout << "Game saved successfully!\n";
                } else {
                    cout << "Error saving game!\n";
                }
            }
            break;
        }
    }

    cout << "\nThanks for playing, " << name << "!\n";
    return 0;
}
