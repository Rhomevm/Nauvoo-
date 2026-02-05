// CORE TYPES & DATA STRUCTURES
// Pseudo-C++ definitions for reference implementation

#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>

namespace Nauvoo {

// ==================== ENUMERATIONS ====================

enum class EFaction {
    LDS_CIVILIAN,
    LEGION_SOLDIER,
    OUTSIDER,
    NEUTRAL
};

enum class ELegionRank {
    RECRUIT,
    LEGIONNAIRE,
    SENIOR_LEGIONNAIRE,
    SERGEANT,
    CAPTAIN,
    COMMANDER
};

enum class EActivityType {
    WORK,
    REST,
    SOCIALIZE,
    PRAY,
    EAT,
    TRAVEL,
    GUARD_DUTY,
    TRAINING,
    IDLE
};

enum class EBodyPart {
    HEAD,
    TORSO,
    LEFT_ARM,
    RIGHT_ARM,
    LEFT_LEG,
    RIGHT_LEG
};

enum class EInjuryType {
    LACERATION,
    BRUISE,
    FRACTURE,
    GUNSHOT,
    INTERNAL_BLEEDING
};

enum class EWeaponType {
    MUSKET,
    PISTOL,
    CLUB,
    SABER,
    KNIFE,
    BAYONET,
    FIST
};

enum class EFormatSeason {
    SPRING,
    SUMMER,
    FALL,
    WINTER
};

enum class EStance {
    STANDING,
    CROUCHING,
    PRONE,
    MOVING,
    BEHIND_COVER
};

// ==================== BASIC DATA STRUCTURES ====================

struct FVector3 {
    float x, y, z;
    
    FVector3 operator+(const FVector3& other) const {
        return { x + other.x, y + other.y, z + other.z };
    }
    
    FVector3 operator-(const FVector3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }
    
    float Distance(const FVector3& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }
};

struct FDateTime {
    int year;
    int month;      // 1-12
    int day;        // 1-31
    int minute;     // 0-1440 (game minutes per day)
    
    int GetTotalGameMinutes() const {
        return (year * 525600) + (month * 43800) + (day * 1440) + minute;
    }
    
    EFormatSeason GetSeason() const {
        int m = month;
        if (m >= 3 && m <= 5) return EFormatSeason::SPRING;
        if (m >= 6 && m <= 8) return EFormatSeason::SUMMER;
        if (m >= 9 && m <= 11) return EFormatSeason::FALL;
        return EFormatSeason::WINTER;
    }
};

// ==================== NPC RELATED ====================

struct FRelationship {
    std::string target_npc_id;
    int trust = 0;              // -100 to 100
    int fear = 0;               // 0 to 100
    int respect = 0;            // -100 to 100
    int intimacy = 0;           // 0 to 100
    FDateTime last_interaction;
};

struct FPlayerAction {
    std::string action_id;
    FDateTime timestamp;
    FVector3 location;
    std::string description;
    std::vector<std::string> witnesses;  // NPC IDs who saw this
};

struct FActionMemory {
    FPlayerAction action;
    std::string emotional_response;     // "angry", "grateful", "fearful"
    bool will_gossip_about = false;
    int relevance = 5;  // 1-10, how much they care
};

struct FReputationData {
    std::string npc_id;
    int trust = 0;                      // -100 to 100
    int fear = 0;                       // 0 to 100
    int respect = 0;                    // -100 to 100
    std::vector<FActionMemory> memories;
    std::vector<std::string> dialogue_locked;  // dialogue options not available
};

struct FInjury {
    EInjuryType type;
    EBodyPart location;
    int severity = 1;              // 1-10
    float bleed_rate = 0.0f;        // HP per second
    bool is_treated = false;
    bool infection_risk = false;
    FDateTime timestamp;
};

struct FScheduleActivity {
    int time_start_minute;          // 0-1440
    int time_end_minute;
    std::string location_id;
    EActivityType action;
    bool interruptible = true;
    std::vector<std::string> social_group_npc_ids;  // who is with them
};

struct FNPCSchedule {
    std::string npc_id;
    std::vector<FScheduleActivity> daily_routine;
    std::map<EFormatSeason, std::vector<FScheduleActivity>> seasonal_overrides;
    std::vector<std::pair<std::string, std::vector<FScheduleActivity>>> event_overrides;
};

struct FNPC {
    std::string id;
    std::string name;
    int age = 25;
    std::string occupation;
    EFaction faction = EFaction::LDS_CIVILIAN;
    ELegionRank rank = ELegionRank::RECRUIT;
    
    // State
    FVector3 position;
    float health = 100.0f;
    float max_health = 100.0f;
    std::vector<FInjury> injuries;
    
    // Relationships
    std::map<std::string, FRelationship> relationships;  // NPC_ID -> Relationship
    FReputationData reputation_with_player;
    std::vector<FActionMemory> memory_of_player;
    
    // Schedule
    FNPCSchedule schedule;
    FScheduleActivity* current_activity = nullptr;
    
    // Behavior
    bool is_alive = true;
    bool is_in_combat = false;
    FVector3 combat_target_position;
};

// ==================== PLAYER RELATED ====================

struct FPlayerState {
    // Physical
    FVector3 position;
    FVector3 forward_vector;
    float health = 100.0f;
    float max_health = 100.0f;
    float stamina = 100.0f;
    float max_stamina = 100.0f;
    std::vector<FInjury> injuries;
    EStance stance = EStance::STANDING;
    
    // Equipment
    std::string equipped_weapon_id;
    std::vector<std::string> inventory_item_ids;
    float carrying_weight = 0.0f;
    float max_carrying_capacity = 30.0f;
    
    // Reputation
    int legion_reputation = 0;       // -100 to 100
    int community_reputation = 0;    // -100 to 100
    int outsider_reputation = 0;     // -100 to 100
    int personal_integrity = 0;      // -50 to 50
    
    // Rank
    ELegionRank legion_rank = ELegionRank::RECRUIT;
    
    // History
    std::vector<FPlayerAction> action_history;
};

// ==================== DIALOGUE RELATED ====================

struct FDialogueOption {
    std::string id;
    std::string display_text;
    
    // Requirements
    int legion_rep_requirement = -999;          // -999 = no requirement
    int community_rep_requirement = -999;
    int outsider_rep_requirement = -999;
    int npc_trust_requirement = -999;
    bool requires_consistency = false;
    
    // Consequence
    std::string next_node_id;
    std::string consequence_action;             // what happens when selected
    int legion_rep_delta = 0;
    int community_rep_delta = 0;
    int outsider_rep_delta = 0;
};

struct FDialogueNode {
    std::string id;
    std::string type;  // "speech", "choice", "condition", "action"
    
    // Speech node
    std::string speaker_npc_id;
    std::string text;
    std::string audio_cue_id;
    
    // Choice node
    std::vector<FDialogueOption> choices;
    
    // Condition node
    std::string condition_type;
    std::map<std::string, std::string> condition_parameters;
    std::string true_branch_node_id;
    std::string false_branch_node_id;
    
    // Next
    std::string next_node_id;
};

struct FDialogueTree {
    std::string id;
    std::string npc_id;
    std::string root_node_id;
    std::vector<FDialogueNode> nodes;
    
    FDialogueNode* GetNode(const std::string& node_id) {
        // Implementation: search nodes vector
        for (auto& node : nodes) {
            if (node.id == node_id) return &node;
        }
        return nullptr;
    }
};

// ==================== WEAPON SYSTEM ====================

struct FWeapon {
    std::string id;
    std::string name;
    EWeaponType type;
    
    // Stats
    float fire_rate = 1.0f;              // seconds between shots
    float reload_time = 45.0f;           // seconds to reload
    float accuracy = 0.7f;               // base accuracy (0-1)
    float damage = 40.0f;
    float range = 100.0f;                // effective range in meters
    float stamina_cost = 10.0f;
    
    // Ammo
    int current_ammo = 6;
    int max_ammo = 6;
    float misfire_chance = 0.05f;        // 5% base misfire rate
    
    // State
    bool is_reloading = false;
    float reload_progress = 0.0f;        // 0-1
};

// ==================== WORLD STATE ====================

struct FWorldState {
    FPlayerState player;
    std::vector<FNPC> all_npcs;
    FDateTime current_time;
    
    // Flags for world events
    std::vector<std::string> active_events;
    std::vector<std::string> completed_events;
    std::map<std::string, int> event_counters;
    
    // Locations
    std::map<std::string, FVector3> location_positions;
    
    // Save metadata
    int save_slot = 0;
    std::string save_name;
    FDateTime save_time;
};

// ==================== UTILITY FUNCTIONS ====================

inline float GetAccuracyMod(EStance stance) {
    switch (stance) {
        case EStance::STANDING:       return 0.7f;
        case EStance::CROUCHING:      return 0.85f;
        case EStance::PRONE:          return 0.95f;
        case EStance::MOVING:         return 0.4f;
        case EStance::BEHIND_COVER:   return 0.8f;
    }
    return 1.0f;
}

inline float GetFatigueAccuracyPenalty(float stamina, float max_stamina) {
    float stamina_percent = stamina / max_stamina;
    if (stamina_percent < 0.2f) return 0.5f;  // Very low stamina
    if (stamina_percent < 0.5f) return 0.7f;  // Low stamina
    return 1.0f;
}

inline std::string ReputationToString(int rep) {
    if (rep >= 80)  return "Exemplary";
    if (rep >= 50)  return "Well-Regarded";
    if (rep >= 20)  return "Favorable";
    if (rep >= 0)   return "Neutral";
    if (rep >= -20) return "Unfavorable";
    if (rep >= -50) return "Distrusted";
    return "Despised";
}

}  // namespace Nauvoo
