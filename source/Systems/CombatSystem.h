#pragma once

#include "../Engine/CoreTypes.h"
#include <string>
#include <vector>
#include <memory>

namespace Nauvoo {

class ReputationManager;

/**
 * Manages combat: targeting, weapon fire, damage, injuries
 */
class CombatSystem {
public:
    CombatSystem(ReputationManager* reputation_mgr);
    ~CombatSystem();

    // Combat initialization
    void StartCombat(const std::string& enemy_npc_id, FNPC& enemy, FPlayerState& player);
    void EndCombat();
    bool IsInCombat() const { return in_combat; }

    // Weapon fire
    void FireWeapon(FPlayerState& player, const FVector3& target_position, 
                   std::vector<FNPC>& all_npcs, const std::string& enemy_npc_id);

    // Damage application
    void ApplyDamage(FPlayerState& target, float damage, EBodyPart hit_location, 
                    const std::string& attacker_id);
    void ApplyDamageToNPC(FNPC& target, float damage, EBodyPart hit_location, 
                         const std::string& attacker_id);

    // Injury management
    void TreatInjury(FNPC& npc, int injury_index);
    void TreatPlayerInjury(FPlayerState& player, int injury_index);

    // Combat statistics
    float CalculateAccuracy(const FPlayerState& player, EStance stance) const;
    float CalculateDamage(const FWeapon& weapon, const std::string& attacker_id) const;

    // Health checks
    bool IsCharacterDead(const FPlayerState& player) const { return player.health <= 0.0f; }
    bool IsNPCDead(const FNPC& npc) const { return npc.health <= 0.0f; }

    // Update bleeding and injuries
    void UpdateHealth(FPlayerState& player, float delta_time);
    void UpdateNPCHealth(FNPC& npc, float delta_time);

    // Enemy AI
    void UpdateEnemyBehavior(FNPC& enemy, const FPlayerState& player, float delta_time);

    // Debug
    void PrintCombatState() const;

private:
    bool in_combat = false;
    std::string current_enemy_id;
    float combat_timeout = 0.0f;

    ReputationManager* reputation_manager = nullptr;

    // Helper functions
    EBodyPart DetermineBodyPart(const FVector3& hit_location) const;
    float GetBleedRate(EInjuryType injury_type, int severity) const;
    void HandleCharacterDeath(FNPC& dead_npc, const std::vector<FNPC>& witnesses);
};

}  // namespace Nauvoo
