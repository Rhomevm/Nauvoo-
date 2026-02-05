#pragma once

#include "../Engine/CoreTypes.h"
#include <string>
#include <vector>
#include <map>

namespace Nauvoo {

/**
 * Manages player reputation across three factions and tracks consequences
 */
class ReputationManager {
public:
    ReputationManager();
    ~ReputationManager();

    // Initialize with default values
    void Initialize();

    // Core reputation tracking
    int GetLegionReputation() const { return legion_reputation; }
    int GetCommunityReputation() const { return community_reputation; }
    int GetOutsiderReputation() const { return outsider_reputation; }
    int GetPersonalIntegrity() const { return personal_integrity; }

    // Record player action and apply reputation modifiers
    void RecordAction(const std::string& action_id, const std::vector<std::string>& witnesses);

    // NPC-specific reputation
    int GetNPCTrust(const std::string& npc_id) const;
    void ModifyNPCTrust(const std::string& npc_id, int delta);
    void AddNPCMemory(const std::string& npc_id, const FActionMemory& memory);

    // Action history
    const std::vector<FPlayerAction>& GetActionHistory() const { return action_history; }
    void ClearActionHistory() { action_history.clear(); }

    // Check dialogue availability
    bool CanAccessDialogue(const std::string& npc_id, const std::string& dialogue_option_id) const;

    // Determine ending branch
    std::string DetermineEndingBranch() const;

    // Apply daily decay
    void ApplyDailyDecay();

    // Get reputation string for UI
    std::string GetReputationString(int reputation) const;

    // Debug
    void PrintReputation() const;

private:
    int legion_reputation = 0;       // -100 to 100
    int community_reputation = 0;    // -100 to 100
    int outsider_reputation = 0;     // -100 to 100
    int personal_integrity = 0;      // -50 to 50

    std::vector<FPlayerAction> action_history;
    std::map<std::string, FReputationData> npc_reputation_map;  // NPC_ID -> Reputation

    // Load reputation modifiers from action_modifiers.json
    void LoadActionModifiers();
    std::map<std::string, std::map<std::string, int>> action_modifiers;  // action_id -> {faction -> delta}
};

}  // namespace Nauvoo
