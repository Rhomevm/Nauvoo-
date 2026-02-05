#pragma once

#include "CoreTypes.h"
#include <memory>
#include <vector>
#include <map>

namespace Nauvoo {

class NPCScheduleManager;
class ReputationManager;
class DialogueManager;
class CombatSystem;
class SaveGameManager;

/**
 * Central game manager coordinating all systems
 * Handles time progression, updates, and inter-system communication
 */
class GameManager {
public:
    GameManager();
    ~GameManager();

    // Initialization
    void Initialize();
    void LoadGame(const std::string& save_slot);
    void StartNewGame();

    // Main update loop
    void Update(float delta_time);
    void FixedUpdate(float fixed_delta);

    // Time management
    void AdvanceGameTime(int minutes);
    FDateTime GetCurrentTime() const { return world_state.current_time; }
    EFormatSeason GetCurrentSeason() const { return world_state.current_time.GetSeason(); }
    float GetTimeScale() const { return time_scale; }

    // NPC management
    FNPC* GetNPCById(const std::string& npc_id);
    const std::vector<FNPC>& GetAllNPCs() const { return world_state.all_npcs; }
    std::vector<FNPC>& GetAllNPCs() { return world_state.all_npcs; }
    void UpdateAllNPCs(float delta_time);
    void SpawnNPC(const FNPC& npc_definition);

    // Player management
    FPlayerState& GetPlayerState() { return world_state.player; }
    const FPlayerState& GetPlayerState() const { return world_state.player; }
    void SetPlayerPosition(const FVector3& pos) { world_state.player.position = pos; }

    // Reputation system
    ReputationManager* GetReputationManager() { return reputation_manager.get(); }
    void RecordPlayerAction(const std::string& action_id);

    // Dialogue system
    DialogueManager* GetDialogueManager() { return dialogue_manager.get(); }
    void StartDialogueWithNPC(const std::string& npc_id);
    void EndDialogue();

    // Combat system
    CombatSystem* GetCombatSystem() { return combat_system.get(); }
    void InitiateCombat(const std::string& enemy_npc_id);
    void EndCombat();

    // World state
    FWorldState& GetWorldState() { return world_state; }
    const FWorldState& GetWorldState() const { return world_state; }

    // Event system
    void TriggerEvent(const std::string& event_id);
    void CompleteEvent(const std::string& event_id);
    bool IsEventActive(const std::string& event_id) const;

    // Save/Load
    void SaveGame(const std::string& save_slot);
    bool CanLoad(const std::string& save_slot) const;

    // Debug
    void PrintWorldState() const;
    void PrintNPCStates() const;

private:
    FWorldState world_state;
    
    std::unique_ptr<NPCScheduleManager> schedule_manager;
    std::unique_ptr<ReputationManager> reputation_manager;
    std::unique_ptr<DialogueManager> dialogue_manager;
    std::unique_ptr<CombatSystem> combat_system;
    std::unique_ptr<SaveGameManager> save_manager;

    float time_scale = 0.02f;  // 1 real second = 1.2 game minutes
    bool is_paused = false;

    // NPC daily routine tracking
    std::map<std::string, std::string> npc_current_activity;  // NPC_ID -> Activity_ID
};

}  // namespace Nauvoo
