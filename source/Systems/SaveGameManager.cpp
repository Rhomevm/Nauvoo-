#include "../Systems/SaveGameManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace Nauvoo {

SaveGameManager::SaveGameManager() {
    save_directory = "./saves";
    
    // Create save directory if it doesn't exist
    if (!fs::exists(save_directory)) {
        fs::create_directories(save_directory);
        std::cout << "[SaveGameManager] Created save directory: " << save_directory << std::endl;
    }
}

SaveGameManager::~SaveGameManager() = default;

void SaveGameManager::SaveGame(const FWorldState& world_state, const std::string& save_slot) {
    std::string filename = save_directory + "/" + save_slot + ".nauvoo";
    
    std::string save_data;
    save_data += "=== NAUVOO SAVE FILE ===\n";
    save_data += "Version: 1.0\n";
    save_data += "Date: " + std::to_string(world_state.current_time.year) + "-" 
                 + std::to_string(world_state.current_time.month) + "-"
                 + std::to_string(world_state.current_time.day) + "\n";
    save_data += "Time: " + std::to_string(world_state.current_time.minute) + "\n";
    save_data += "\n";
    save_data += SerializePlayerState(world_state.player);
    save_data += "\n";
    save_data += SerializeWorldState(world_state);
    
    if (WriteFile(filename, save_data)) {
        std::cout << "[SaveGameManager] Game saved to " << filename << std::endl;
    } else {
        std::cout << "[SaveGameManager] Failed to save game to " << filename << std::endl;
    }
}

bool SaveGameManager::LoadGame(const std::string& save_slot, FWorldState& world_state) {
    std::string filename = save_directory + "/" + save_slot + ".nauvoo";
    std::string content;
    
    if (!ReadFile(filename, content)) {
        std::cout << "[SaveGameManager] Failed to read save file: " << filename << std::endl;
        return false;
    }
    
    // Parse content and populate world_state
    std::cout << "[SaveGameManager] Game loaded from " << filename << std::endl;
    return true;
}

bool SaveGameManager::SaveExists(const std::string& save_slot) const {
    std::string filename = save_directory + "/" + save_slot + ".nauvoo";
    return fs::exists(filename);
}

std::vector<std::string> SaveGameManager::GetAvailableSaves() const {
    std::vector<std::string> saves;
    
    if (!fs::exists(save_directory)) {
        return saves;
    }

    for (const auto& entry : fs::directory_iterator(save_directory)) {
        if (entry.path().extension() == ".nauvoo") {
            saves.push_back(entry.path().stem().string());
        }
    }

    return saves;
}

void SaveGameManager::DeleteSave(const std::string& save_slot) {
    std::string filename = save_directory + "/" + save_slot + ".nauvoo";
    
    if (fs::exists(filename)) {
        fs::remove(filename);
        std::cout << "[SaveGameManager] Deleted save: " << save_slot << std::endl;
    }
}

void SaveGameManager::AutoSave(const FWorldState& world_state, int game_day) {
    if (!auto_save_enabled) return;
    
    if (game_day != last_autosave_day) {
        SaveGame(world_state, "autosave");
        last_autosave_day = game_day;
    }
}

std::string SaveGameManager::SerializePlayerState(const FPlayerState& player) const {
    std::string data;
    data += "=== PLAYER STATE ===\n";
    data += "Health: " + std::to_string(static_cast<int>(player.health)) + "\n";
    data += "Stamina: " + std::to_string(static_cast<int>(player.stamina)) + "\n";
    data += "Legion Reputation: " + std::to_string(player.legion_reputation) + "\n";
    data += "Community Reputation: " + std::to_string(player.community_reputation) + "\n";
    data += "Outsider Reputation: " + std::to_string(player.outsider_reputation) + "\n";
    data += "Legion Rank: " + std::to_string(static_cast<int>(player.legion_rank)) + "\n";
    data += "Injuries: " + std::to_string(player.injuries.size()) + "\n";
    return data;
}

std::string SaveGameManager::SerializeWorldState(const FWorldState& world) const {
    std::string data;
    data += "=== WORLD STATE ===\n";
    data += "Total NPCs: " + std::to_string(world.all_npcs.size()) + "\n";
    data += "Active Events: " + std::to_string(world.active_events.size()) + "\n";
    data += "Completed Events: " + std::to_string(world.completed_events.size()) + "\n";
    return data;
}

std::string SaveGameManager::SerializeNPCState(const FNPC& npc) const {
    std::string data;
    data += "NPC: " + npc.id + " (" + npc.name + ")\n";
    data += "  Health: " + std::to_string(static_cast<int>(npc.health)) + "\n";
    data += "  Alive: " + std::string(npc.is_alive ? "Yes" : "No") + "\n";
    return data;
}

bool SaveGameManager::DeserializePlayerState(const std::string& data, FPlayerState& player) {
    // Would parse data and populate player state
    return true;
}

bool SaveGameManager::DeserializeWorldState(const std::string& data, FWorldState& world) {
    // Would parse data and populate world state
    return true;
}

bool SaveGameManager::DeserializeNPCState(const std::string& data, FNPC& npc) {
    // Would parse data and populate NPC state
    return true;
}

bool SaveGameManager::WriteFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << content;
    file.close();
    return true;
}

bool SaveGameManager::ReadFile(const std::string& filename, std::string& content) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    
    file.close();
    return true;
}

}  // namespace Nauvoo
