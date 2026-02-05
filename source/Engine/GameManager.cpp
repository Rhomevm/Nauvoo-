#include "GameManager.h"
#include "../Systems/NPCScheduleManager.h"
#include "../Systems/ReputationManager.h"
#include "../Systems/DialogueManager.h"
#include "../Systems/CombatSystem.h"
#include "../Systems/SaveGameManager.h"
#include <iostream>
#include <algorithm>

namespace Nauvoo {

GameManager::GameManager() {
    schedule_manager = std::make_unique<NPCScheduleManager>();
    reputation_manager = std::make_unique<ReputationManager>();
    dialogue_manager = std::make_unique<DialogueManager>(reputation_manager.get());
    combat_system = std::make_unique<CombatSystem>(reputation_manager.get());
    save_manager = std::make_unique<SaveGameManager>();
}

GameManager::~GameManager() = default;

void GameManager::Initialize() {
    std::cout << "[GameManager] Initializing Nauvoo: Legion" << std::endl;
    
    // Initialize systems
    reputation_manager->Initialize();
    
    // Load schedules, dialogue, etc.
    schedule_manager->LoadSchedules("source/Data/npc_schedules.json");
    dialogue_manager->LoadDialogueTrees("source/Data/Dialogue/dialogue_trees.json");
    
    // Initialize world state
    world_state.current_time = { 1841, 5, 15, 360 };  // 9/15/1841 at 6:00 AM
    world_state.player.health = 100.0f;
    world_state.player.max_health = 100.0f;
    world_state.player.stamina = 100.0f;
    world_state.player.max_stamina = 100.0f;
    world_state.player.legion_rank = ELegionRank::RECRUIT;
    
    std::cout << "[GameManager] Initialization complete" << std::endl;
}

void GameManager::StartNewGame() {
    std::cout << "[GameManager] Starting new game" << std::endl;
    Initialize();
    
    // Spawn initial NPCs and set to starting positions
    // Load from NPC definition file
    world_state.current_time = { 1841, 5, 15, 360 };  // Game starts May 15, 1841 at 6 AM
}

void GameManager::Update(float delta_time) {
    if (is_paused) return;

    // Advance game time
    float game_minutes = delta_time * time_scale;
    int minutes_to_advance = static_cast<int>(game_minutes);
    
    if (minutes_to_advance > 0) {
        AdvanceGameTime(minutes_to_advance);
    }

    // Update all NPCs
    UpdateAllNPCs(delta_time);

    // Update player health (bleeding, injuries)
    if (combat_system->IsInCombat()) {
        combat_system->UpdateHealth(world_state.player, delta_time);
    }

    // Update NPC health
    for (auto& npc : world_state.all_npcs) {
        if (!npc.is_alive) continue;
        combat_system->UpdateNPCHealth(npc, delta_time);
    }
}

void GameManager::AdvanceGameTime(int minutes) {
    world_state.current_time.minute += minutes;
    
    // Roll over to next day
    while (world_state.current_time.minute >= 1440) {
        world_state.current_time.minute -= 1440;
        world_state.current_time.day++;
        
        // Handle season/month changes
        if (world_state.current_time.day > 30) {
            world_state.current_time.day = 1;
            world_state.current_time.month++;
            
            if (world_state.current_time.month > 12) {
                world_state.current_time.month = 1;
                world_state.current_time.year++;
            }
        }
        
        // Daily maintenance
        reputation_manager->ApplyDailyDecay();
    }
}

FNPC* GameManager::GetNPCById(const std::string& npc_id) {
    for (auto& npc : world_state.all_npcs) {
        if (npc.id == npc_id) {
            return &npc;
        }
    }
    return nullptr;
}

void GameManager::UpdateAllNPCs(float delta_time) {
    for (auto& npc : world_state.all_npcs) {
        if (!npc.is_alive) continue;

        // Update schedule based on current time
        schedule_manager->UpdateNPCSchedules(world_state.current_time, world_state.all_npcs);

        // Update NPC relationships (gossip, memory decay)
        // Update NPC AI behavior
        if (npc.is_in_combat) {
            combat_system->UpdateEnemyBehavior(npc, world_state.player, delta_time);
        }
    }
}

void GameManager::SpawnNPC(const FNPC& npc_definition) {
    world_state.all_npcs.push_back(npc_definition);
    std::cout << "[GameManager] Spawned NPC: " << npc_definition.name << std::endl;
}

void GameManager::RecordPlayerAction(const std::string& action_id) {
    reputation_manager->RecordAction(action_id, {});  // Will be populated with witnesses
    std::cout << "[GameManager] Player action recorded: " << action_id << std::endl;
}

void GameManager::StartDialogueWithNPC(const std::string& npc_id) {
    FNPC* npc = GetNPCById(npc_id);
    if (!npc) {
        std::cout << "[GameManager] Error: NPC not found: " << npc_id << std::endl;
        return;
    }
    
    std::cout << "[GameManager] Started dialogue with " << npc->name << std::endl;
    // Dialogue manager will handle tree selection
}

void GameManager::EndDialogue() {
    std::cout << "[GameManager] Dialogue ended" << std::endl;
}

void GameManager::InitiateCombat(const std::string& enemy_npc_id) {
    FNPC* enemy = GetNPCById(enemy_npc_id);
    if (!enemy) {
        std::cout << "[GameManager] Error: Enemy NPC not found: " << enemy_npc_id << std::endl;
        return;
    }
    
    std::cout << "[GameManager] Combat initiated with " << enemy->name << std::endl;
    combat_system->StartCombat(enemy_npc_id, *enemy, world_state.player);
}

void GameManager::EndCombat() {
    std::cout << "[GameManager] Combat ended" << std::endl;
}

void GameManager::TriggerEvent(const std::string& event_id) {
    world_state.active_events.push_back(event_id);
    std::cout << "[GameManager] Event triggered: " << event_id << std::endl;
}

void GameManager::CompleteEvent(const std::string& event_id) {
    // Move from active to completed
    auto it = std::find(world_state.active_events.begin(), 
                       world_state.active_events.end(), event_id);
    if (it != world_state.active_events.end()) {
        world_state.active_events.erase(it);
        world_state.completed_events.push_back(event_id);
        std::cout << "[GameManager] Event completed: " << event_id << std::endl;
    }
}

bool GameManager::IsEventActive(const std::string& event_id) const {
    return std::find(world_state.active_events.begin(), 
                    world_state.active_events.end(), event_id) != world_state.active_events.end();
}

void GameManager::SaveGame(const std::string& save_slot) {
    save_manager->SaveGame(world_state, save_slot);
    std::cout << "[GameManager] Game saved to slot: " << save_slot << std::endl;
}

bool GameManager::CanLoad(const std::string& save_slot) const {
    return save_manager->SaveExists(save_slot);
}

void GameManager::PrintWorldState() const {
    std::cout << "\n=== WORLD STATE ===" << std::endl;
    std::cout << "Date: " << world_state.current_time.year << "-" 
              << world_state.current_time.month << "-" 
              << world_state.current_time.day << " " 
              << (world_state.current_time.minute / 60) << ":"
              << (world_state.current_time.minute % 60) << std::endl;
    std::cout << "Season: ";
    switch (world_state.current_time.GetSeason()) {
        case EFormatSeason::SPRING: std::cout << "Spring"; break;
        case EFormatSeason::SUMMER: std::cout << "Summer"; break;
        case EFormatSeason::FALL: std::cout << "Fall"; break;
        case EFormatSeason::WINTER: std::cout << "Winter"; break;
    }
    std::cout << std::endl;
    std::cout << "Active events: " << world_state.active_events.size() << std::endl;
    std::cout << "Completed events: " << world_state.completed_events.size() << std::endl;
    std::cout << "Spawned NPCs: " << world_state.all_npcs.size() << std::endl;
}

void GameManager::PrintNPCStates() const {
    std::cout << "\n=== NPC STATES ===" << std::endl;
    for (const auto& npc : world_state.all_npcs) {
        std::cout << npc.name << " (" << npc.id << ")" << std::endl;
        std::cout << "  Faction: " << static_cast<int>(npc.faction) << std::endl;
        std::cout << "  Health: " << npc.health << "/" << npc.max_health << std::endl;
        std::cout << "  Status: " << (npc.is_alive ? "Alive" : "Dead") << std::endl;
    }
}

}  // namespace Nauvoo
