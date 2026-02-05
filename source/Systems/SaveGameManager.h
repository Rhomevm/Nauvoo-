#pragma once

#include "../Engine/CoreTypes.h"
#include <string>
#include <vector>

namespace Nauvoo {

/**
 * Handles saving and loading game state
 */
class SaveGameManager {
public:
    SaveGameManager();
    ~SaveGameManager();

    // Save/Load operations
    void SaveGame(const FWorldState& world_state, const std::string& save_slot);
    bool LoadGame(const std::string& save_slot, FWorldState& world_state);

    // Save management
    bool SaveExists(const std::string& save_slot) const;
    std::vector<std::string> GetAvailableSaves() const;
    void DeleteSave(const std::string& save_slot);

    // Auto-save
    void EnableAutoSave(bool enable) { auto_save_enabled = enable; }
    void AutoSave(const FWorldState& world_state, int game_day);

private:
    std::string save_directory;
    bool auto_save_enabled = true;
    int last_autosave_day = -1;

    // Serialization helpers
    std::string SerializePlayerState(const FPlayerState& player) const;
    std::string SerializeWorldState(const FWorldState& world) const;
    std::string SerializeNPCState(const FNPC& npc) const;

    bool DeserializePlayerState(const std::string& data, FPlayerState& player);
    bool DeserializeWorldState(const std::string& data, FWorldState& world);
    bool DeserializeNPCState(const std::string& data, FNPC& npc);

    // File I/O
    bool WriteFile(const std::string& filename, const std::string& content);
    bool ReadFile(const std::string& filename, std::string& content);
};

}  // namespace Nauvoo
