#include "../Systems/CombatSystem.h"
#include "ReputationManager.h"
#include <iostream>
#include <cmath>

namespace Nauvoo {

CombatSystem::CombatSystem(ReputationManager* reputation_mgr)
    : reputation_manager(reputation_mgr) {
}

CombatSystem::~CombatSystem() = default;

void CombatSystem::StartCombat(const std::string& enemy_npc_id, FNPC& enemy, FPlayerState& player) {
    in_combat = true;
    current_enemy_id = enemy_npc_id;
    combat_timeout = 30.0f;
    
    enemy.is_in_combat = true;
    
    std::cout << "[CombatSystem] Combat started with " << enemy.name << std::endl;
}

void CombatSystem::EndCombat() {
    in_combat = false;
    current_enemy_id.clear();
    std::cout << "[CombatSystem] Combat ended" << std::endl;
}

void CombatSystem::FireWeapon(FPlayerState& player, const FVector3& target_position,
                            std::vector<FNPC>& all_npcs, const std::string& enemy_npc_id) {
    if (!in_combat) {
        std::cout << "[CombatSystem] Not in combat, cannot fire" << std::endl;
        return;
    }

    // Get player's weapon
    FWeapon* weapon = nullptr;
    // Would get from inventory - for MVP, assume musket
    FWeapon musket;
    musket.name = "Musket";
    musket.accuracy = 0.7f;
    musket.damage = 40.0f;
    musket.stamina_cost = 15.0f;
    
    // Check ammunition
    if (musket.current_ammo <= 0) {
        std::cout << "[CombatSystem] Out of ammunition" << std::endl;
        return;
    }

    // Calculate accuracy
    float accuracy = CalculateAccuracy(player, EStance::STANDING);
    
    // Perform hit check (simplified)
    if (rand() % 100 < (accuracy * 100)) {
        // Hit
        EBodyPart hit_location = EBodyPart::TORSO;
        ApplyDamage(player, musket.damage, hit_location, "player");
        
        std::cout << "[CombatSystem] Hit! Dealt " << musket.damage << " damage" << std::endl;
    } else {
        std::cout << "[CombatSystem] Miss!" << std::endl;
    }

    // Reduce ammunition
    musket.current_ammo--;
    
    // Apply stamina cost
    player.stamina -= musket.stamina_cost;
    if (player.stamina < 0) player.stamina = 0;
}

void CombatSystem::ApplyDamage(FPlayerState& target, float damage, EBodyPart hit_location,
                              const std::string& attacker_id) {
    target.health -= damage;
    
    FInjury injury;
    injury.location = hit_location;
    injury.severity = static_cast<int>(damage / 10.0f);
    injury.type = EInjuryType::GUNSHOT;
    injury.bleed_rate = GetBleedRate(injury.type, injury.severity);
    
    target.injuries.push_back(injury);
    
    std::cout << "[CombatSystem] Player health: " << target.health << "/" << target.max_health << std::endl;
    
    if (target.health <= 0) {
        std::cout << "[CombatSystem] Player defeated!" << std::endl;
    }
}

void CombatSystem::ApplyDamageToNPC(FNPC& target, float damage, EBodyPart hit_location,
                                   const std::string& attacker_id) {
    target.health -= damage;
    
    FInjury injury;
    injury.location = hit_location;
    injury.severity = static_cast<int>(damage / 10.0f);
    injury.type = EInjuryType::GUNSHOT;
    injury.bleed_rate = GetBleedRate(injury.type, injury.severity);
    
    target.injuries.push_back(injury);
    
    std::cout << "[CombatSystem] " << target.name << " health: " << target.health << "/" << target.max_health << std::endl;
    
    if (target.health <= 0) {
        target.is_alive = false;
        HandleCharacterDeath(target, {});
    }
}

void CombatSystem::TreatInjury(FNPC& npc, int injury_index) {
    if (injury_index < static_cast<int>(npc.injuries.size())) {
        npc.injuries[injury_index].is_treated = true;
        npc.injuries[injury_index].bleed_rate = 0.0f;
        std::cout << "[CombatSystem] NPC injury treated" << std::endl;
    }
}

void CombatSystem::TreatPlayerInjury(FPlayerState& player, int injury_index) {
    if (injury_index < static_cast<int>(player.injuries.size())) {
        player.injuries[injury_index].is_treated = true;
        player.injuries[injury_index].bleed_rate = 0.0f;
        std::cout << "[CombatSystem] Player injury treated" << std::endl;
    }
}

float CombatSystem::CalculateAccuracy(const FPlayerState& player, EStance stance) const {
    float base_accuracy = 0.7f;
    
    // Apply stance modifier
    if (stance == EStance::STANDING) base_accuracy *= 0.7f;
    else if (stance == EStance::CROUCHING) base_accuracy *= 0.85f;
    else if (stance == EStance::PRONE) base_accuracy *= 0.95f;
    
    // Apply stamina penalty
    float stamina_percent = player.stamina / player.max_stamina;
    if (stamina_percent < 0.2f) base_accuracy *= 0.5f;
    else if (stamina_percent < 0.5f) base_accuracy *= 0.7f;
    
    return base_accuracy;
}

float CombatSystem::CalculateDamage(const FWeapon& weapon, const std::string& attacker_id) const {
    // Would modify based on weapon condition, etc.
    return weapon.damage;
}

void CombatSystem::UpdateHealth(FPlayerState& player, float delta_time) {
    float total_bleed = 0.0f;
    
    for (FInjury& injury : player.injuries) {
        if (!injury.is_treated) {
            total_bleed += injury.bleed_rate;
            
            // Risk infection
            // if (time_since_injury > 60) injury.infection_risk = true;
        }
    }
    
    player.health -= total_bleed * delta_time;
    if (player.health < 0) player.health = 0;
}

void CombatSystem::UpdateNPCHealth(FNPC& npc, float delta_time) {
    if (!npc.is_alive) return;
    
    float total_bleed = 0.0f;
    
    for (FInjury& injury : npc.injuries) {
        if (!injury.is_treated) {
            total_bleed += injury.bleed_rate;
        }
    }
    
    npc.health -= total_bleed * delta_time;
    if (npc.health < 0) {
        npc.health = 0;
        npc.is_alive = false;
        HandleCharacterDeath(npc, {});
    }
}

void CombatSystem::UpdateEnemyBehavior(FNPC& enemy, const FPlayerState& player, float delta_time) {
    if (!enemy.is_in_combat) return;
    
    // Simple AI: if hurt, retreat
    if (enemy.health < enemy.max_health * 0.3f) {
        std::cout << "[CombatSystem] " << enemy.name << " is retreating!" << std::endl;
        enemy.is_in_combat = false;
        return;
    }
    
    // Otherwise, stay in combat
}

EBodyPart CombatSystem::DetermineBodyPart(const FVector3& hit_location) const {
    // Simplified: just return torso for MVP
    return EBodyPart::TORSO;
}

float CombatSystem::GetBleedRate(EInjuryType injury_type, int severity) const {
    switch (injury_type) {
        case EInjuryType::LACERATION:
            return severity * 0.5f;
        case EInjuryType::GUNSHOT:
            return severity * 2.0f;
        case EInjuryType::INTERNAL_BLEEDING:
            return severity * 1.5f;
        default:
            return 0.0f;
    }
}

void CombatSystem::HandleCharacterDeath(FNPC& dead_npc, const std::vector<FNPC>& witnesses) {
    std::cout << "[CombatSystem] " << dead_npc.name << " died in combat" << std::endl;
    dead_npc.is_alive = false;
    
    // Would apply reputation consequences based on circumstances
    if (reputation_manager) {
        // Killing an NPC will affect reputation
        reputation_manager->RecordAction("npc_killed_" + dead_npc.id, {});
    }
}

void CombatSystem::PrintCombatState() const {
    std::cout << "\n=== COMBAT STATE ===" << std::endl;
    std::cout << "In combat: " << (in_combat ? "Yes" : "No") << std::endl;
    if (in_combat) {
        std::cout << "Enemy: " << current_enemy_id << std::endl;
        std::cout << "Combat timeout: " << combat_timeout << "s" << std::endl;
    }
}

}  // namespace Nauvoo
