#include "Engine/Game.h"
#include "Engine/GameManager.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    try {
        std::cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
        std::cout << "║                                                           ║\n";
        std::cout << "║        NAUVOO: LEGION - Historical First-Person Game      ║\n";
        std::cout << "║                  Version 0.1 - MVP Build                  ║\n";
        std::cout << "║                                                           ║\n";
        std::cout << "╚═══════════════════════════════════════════════════════════╝\n\n";

        Nauvoo::NauvooGame game;
        game.Initialize();
        
        std::cout << "Press any key to start game simulation..." << std::endl;
        std::cin.get();
        
        game.Run();
        
        std::cout << "\n[Main] Game loop ended" << std::endl;
        std::cout << "\n═══════════════════════════════════════════════════════════\n";
        std::cout << "                    GAME ENDED SUCCESSFULLY                 \n";
        std::cout << "═══════════════════════════════════════════════════════════\n\n";
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "FATAL ERROR: " << e.what() << std::endl;
        return 1;
    }
}
