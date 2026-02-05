#include "../Systems/ReputationManager.h"
#include <iostream>

using json = std::string;  // Dummy for now

namespace Nauvoo {

ReputationManager::ReputationManager() {
    LoadActionModifiers();
}

ReputationManager::~ReputationManager() = default;

void ReputationManager::Initialize() {
    legion_reputation = 0;
    community_reputation = 0;
    outsider_reputation = 0;
    personal_integrity = 0;
    action_history.clear();
    npc_reputation_map.clear();
}

void ReputationManager::LoadActionModifiers() {
    // This would load from action_modifiers.json
    // For now, using hard-coded values
    action_modifiers["help_with_task"] = {
        {"legion", 0},
        {"community", 30},
        {"outsider", 0}
    };
    
    action_modifiers["attend_drill"] = {
        {"legion", 20},
        {"community", 0},
        {"outsider", 0}
    };
    
    action_modifiers["skip_drill"] = {
        {"legion", -30},
        {"community", 0},
        {"outsider", 0}
    };
    
    action_modifiers["enforce_curfew_harshly"] = {
        {"legion", 25},
        {"community", -30},
        {"outsider", -20}
    };
    
    action_modifiers["show_mercy_to_enemy"] = {
        {"legion", -20},
        {"community", 40},
        {"outsider", 30}
    };
    
    action_modifiers["refuse_order"] = {
        {"legion", -40},
        {"community", 30},
        {"outsider", 10}
    };
}

void ReputationManager::RecordAction(const std::string& action_id, 
                                    const std::vector<std::string>& witnesses) {
    auto modifier_it = action_modifiers.find(action_id);
    if (modifier_it == action_modifiers.end()) {
        std::cout << "[ReputationManager] Unknown action: " << action_id << std::endl;
        return;
    }

    const auto& modifiers = modifier_it->second;
    
    // Apply reputation changes
    int legion_delta = modifiers.at("legion");
    int community_delta = modifiers.at("community");
    int outsider_delta = modifiers.at("outsider");
    
    legion_reputation += legion_delta;
    community_reputation += community_delta;
    outsider_reputation += outsider_delta;
    
    // Clamp to [-100, 100]
    legion_reputation = std::max(-100, std::min(100, legion_reputation));
    community_reputation = std::max(-100, std::min(100, community_reputation));
    outsider_reputation = std::max(-100, std::min(100, outsider_reputation));
    
    std::cout << "[ReputationManager] Action recorded: " << action_id << std::endl;
    std::cout << "  Legion: " << "++" << legion_delta << " -> " << legion_reputation << std::endl;
    std::cout << "  Community: " << "++" << community_delta << " -> " << community_reputation << std::endl;
    std::cout << "  Outsider: " << "++" << outsider_delta << " -> " << outsider_reputation << std::endl;
}

int ReputationManager::GetNPCTrust(const std::string& npc_id) const {
    auto it = npc_reputation_map.find(npc_id);
    if (it != npc_reputation_map.end()) {
        return it->second.trust;
    }
    return 0;
}

void ReputationManager::ModifyNPCTrust(const std::string& npc_id, int delta) {
    if (npc_reputation_map.find(npc_id) == npc_reputation_map.end()) {
        npc_reputation_map[npc_id].npc_id = npc_id;
    }
    
    npc_reputation_map[npc_id].trust += delta;
    npc_reputation_map[npc_id].trust = std::max(-100, std::min(100, npc_reputation_map[npc_id].trust));
    
    std::cout << "[ReputationManager] NPC " << npc_id << " trust: " << npc_reputation_map[npc_id].trust << std::endl;
}

void ReputationManager::AddNPCMemory(const std::string& npc_id, const FActionMemory& memory) {
    if (npc_reputation_map.find(npc_id) == npc_reputation_map.end()) {
        npc_reputation_map[npc_id].npc_id = npc_id;
    }
    
    npc_reputation_map[npc_id].memories.push_back(memory);
    std::cout << "[ReputationManager] Added memory for NPC " << npc_id << std::endl;
}

bool ReputationManager::CanAccessDialogue(const std::string& npc_id, 
                                         const std::string& dialogue_option_id) const {
    // Would check requirements here
    // For MVP, allow all dialogue
    return true;
}

std::string ReputationManager::DetermineEndingBranch() const {
    int combined_reputation = legion_reputation + community_reputation;
    
    if (legion_reputation >= 60 && community_reputation >= 60) {
        return "respected_on_both_sides";
    } else if (legion_reputation <= -30 && community_reputation <= -30) {
        return "outcast_and_blamed";
    } else if (legion_reputation >= 40 && community_reputation <= -40) {
        return "enforcer_path";
    } else if (legion_reputation <= -40 && community_reputation >= 40) {
        return "traitor_path";
    } else {
        return "caught_in_middle";
    }
}

void ReputationManager::ApplyDailyDecay() {
    const int LEGION_DECAY_RATE = 10;
    const int COMMUNITY_DECAY_RATE = 5;
    const int OUTSIDER_DECAY_RATE = 3;
    
    legion_reputation -= LEGION_DECAY_RATE;
    community_reputation -= COMMUNITY_DECAY_RATE;
    outsider_reputation -= OUTSIDER_DECAY_RATE;
    
    // Clamp
    legion_reputation = std::max(-100, legion_reputation);
    community_reputation = std::max(-100, community_reputation);
    outsider_reputation = std::max(-100, outsider_reputation);
}

std::string ReputationManager::GetReputationString(int reputation) const {
    if (reputation >= 80)  return "Exemplary";
    if (reputation >= 50)  return "Well-Regarded";
    if (reputation >= 20)  return "Favorable";
    if (reputation >= 0)   return "Neutral";
    if (reputation >= -20) return "Unfavorable";
    if (reputation >= -50) return "Distrusted";
    return "Despised";
}

void ReputationManager::PrintReputation() const {
    std::cout << "\n=== REPUTATION ===" << std::endl;
    std::cout << "Legion:     " << legion_reputation << " (" << GetReputationString(legion_reputation) << ")" << std::endl;
    std::cout << "Community:  " << community_reputation << " (" << GetReputationString(community_reputation) << ")" << std::endl;
    std::cout << "Outsider:   " << outsider_reputation << " (" << GetReputationString(outsider_reputation) << ")" << std::endl;
    std::cout << "Integrity:  " << personal_integrity << std::endl;
    std::cout << "Ending path: " << DetermineEndingBranch() << std::endl;
    std::cout << "Action history: " << action_history.size() << " actions recorded" << std::endl;
}

}  // namespace Nauvoo
