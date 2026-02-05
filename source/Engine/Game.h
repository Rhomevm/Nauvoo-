#pragma once

#include "../Engine/GameManager.h"
#include <memory>

namespace Nauvoo {

/**
 * Main game application class
 * Handles initialization, main loop, and shutdown
 */
class NauvooGame {
public:
    NauvooGame();
    ~NauvooGame();

    // Initialization
    void Initialize();
    void LoadContent();

    // Main loop
    void Run();
    bool Update(float delta_time);
    void Render();

    // Game state
    bool IsRunning() const { return is_running; }
    void Quit() { is_running = false; }

    // Access
    GameManager* GetGameManager() { return game_manager.get(); }

private:
    std::unique_ptr<GameManager> game_manager;
    bool is_running = true;

    // Game content
    void CreateInitialNPCs();
    void CreateDialogueTrees();
    void CreateStartingLocation();
};

}  // namespace Nauvoo
