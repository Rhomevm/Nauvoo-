#pragma once

#include "Engine/GameManager.h"
#include "Engine/Game.h"
#include "Systems/ReputationManager.h"
#include "Systems/DialogueManager.h"
#include "Systems/CombatSystem.h"
#include <iostream>
#include <cassert>

namespace Nauvoo {

/**
 * Test harness for validating all game systems
 */
class GameTestSuite {
public:
    GameTestSuite() : passed(0), failed(0) {}

    void RunAllTests() {
        std::cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
        std::cout << "║           NAUVOO: LEGION - TEST SUITE v1.0                ║\n";
        std::cout << "╚═══════════════════════════════════════════════════════════╝\n\n";

        TestTimeSystem();
        TestReputationSystem();
        TestNPCSystem();
        TestDialogueSystem();
        TestCombatSystem();
        TestGameInitialization();

        PrintResults();
    }

private:
    int passed;
    int failed;

    void Assert(bool condition, const std::string& test_name) {
        if (condition) {
            std::cout << "  ✓ " << test_name << std::endl;
            passed++;
        } else {
            std::cout << "  ✗ FAILED: " << test_name << std::endl;
            failed++;
        }
    }

    void TestTimeSystem() {
        std::cout << "\n[TEST SUITE] Time System\n";
        
        GameManager gm;
        gm.Initialize();
        
        FDateTime time = gm.GetCurrentTime();
        Assert(time.year == 1841, "Game starts in 1841");
        Assert(time.month == 5, "Game starts in May");
        Assert(time.day == 15, "Game starts on day 15");
        
        gm.AdvanceGameTime(120);
        time = gm.GetCurrentTime();
        Assert(time.minute == 480, "120 minutes advanced correctly");
        
        gm.AdvanceGameTime(960);
        time = gm.GetCurrentTime();
        Assert(time.day == 16, "Day rollover works");
        Assert(time.minute == 0, "Minute reset on day rollover");
        
        std::cout << std::endl;
    }

    void TestReputationSystem() {
        std::cout << "[TEST SUITE] Reputation System\n";
        
        GameManager gm;
        gm.Initialize();
        
        ReputationManager* rep_mgr = gm.GetReputationManager();
        
        // Test initial reputation
        int legion_rep = rep_mgr->GetLegionReputation();
        Assert(legion_rep == 0, "Initial Legion reputation is 0");
        
        // Test recording action
        rep_mgr->RecordAction("help_with_task", {});
        int legion_rep_after = rep_mgr->GetLegionReputation();
        int community_rep = rep_mgr->GetCommunityReputation();
        Assert(legion_rep_after == 0, "help_with_task doesn't affect Legion");
        Assert(community_rep == 30, "help_with_task increases Community by 30");
        
        // Test reputation clamping
        for (int i = 0; i < 5; i++) {
            rep_mgr->RecordAction("attend_drill", {});
        }
        legion_rep = rep_mgr->GetLegionReputation();
        Assert(legion_rep == 100, "Legion reputation clamped at 100");
        
        // Test ending determination
        std::string ending = rep_mgr->DetermineEndingBranch();
        Assert(!ending.empty(), "Ending path determined");
        
        std::cout << std::endl;
    }

    void TestNPCSystem() {
        std::cout << "[TEST SUITE] NPC System\n";
        
        GameManager gm;
        gm.Initialize();
        
        // Create test NPC
        FNPC test_npc;
        test_npc.id = "test_captain";
        test_npc.name = "Test Captain";
        test_npc.health = 100.0f;
        test_npc.max_health = 100.0f;
        test_npc.is_alive = true;
        test_npc.faction = EFaction::LEGION_SOLDIER;
        test_npc.rank = ELegionRank::CAPTAIN;
        
        gm.SpawnNPC(test_npc);
        
        FNPC* retrieved = gm.GetNPCById("test_captain");
        Assert(retrieved != nullptr, "NPC spawned and retrieved");
        Assert(retrieved->name == "Test Captain", "NPC data preserved");
        
        const auto& all_npcs = gm.GetAllNPCs();
        Assert(all_npcs.size() > 0, "NPC list not empty");
        
        std::cout << std::endl;
    }

    void TestDialogueSystem() {
        std::cout << "[TEST SUITE] Dialogue System\n";
        
        GameManager gm;
        gm.Initialize();
        
        DialogueManager* dialogue_mgr = gm.GetDialogueManager();
        Assert(dialogue_mgr != nullptr, "Dialogue manager initialized");
        
        // Create test dialogue tree
        FDialogueTree test_tree;
        test_tree.id = "test_dialogue";
        test_tree.npc_id = "test_npc";
        test_tree.root_node_id = "root";
        
        FDialogueNode root;
        root.id = "root";
        root.type = "speech";
        root.text = "Hello, test!";
        
        test_tree.nodes.push_back(root);
        
        dialogue_mgr->AddDialogueTree(test_tree);
        Assert(true, "Dialogue tree added successfully");
        
        std::cout << std::endl;
    }

    void TestCombatSystem() {
        std::cout << "[TEST SUITE] Combat System\n";
        
        GameManager gm;
        gm.Initialize();
        
        CombatSystem* combat_mgr = gm.GetCombatSystem();
        FPlayerState& player = gm.GetPlayerState();
        
        // Set player initial state
        player.health = 100.0f;
        player.max_health = 100.0f;
        player.stance = EStance::STANDING;
        player.stamina = 100.0f;
        
        // Test accuracy calculation
        float accuracy = combat_mgr->CalculateAccuracy(player, EStance::STANDING);
        Assert(accuracy > 0.0f && accuracy <= 1.0f, "Accuracy calculated in valid range");
        
        // Test accuracy modification by stance
        float prone_accuracy = combat_mgr->CalculateAccuracy(player, EStance::PRONE);
        float standing_accuracy = combat_mgr->CalculateAccuracy(player, EStance::STANDING);
        Assert(prone_accuracy > standing_accuracy, "Prone stance has better accuracy");
        
        std::cout << std::endl;
    }

    void TestGameInitialization() {
        std::cout << "[TEST SUITE] Game Initialization\n";
        
        NauvooGame game;
        game.Initialize();
        
        GameManager* gm = game.GetGameManager();
        Assert(gm != nullptr, "GameManager created");
        
        FPlayerState& player = gm->GetPlayerState();
        Assert(player.health == 100.0f, "Player initialized with 100 health");
        Assert(player.max_health == 100.0f, "Player max health set");
        
        const auto& npcs = gm->GetAllNPCs();
        Assert(npcs.size() >= 5, "At least 5 NPCs spawned");
        
        FWorldState& world = gm->GetWorldState();
        Assert(world.current_time.year == 1841, "World starts in 1841");
        
        std::cout << std::endl;
    }

    void PrintResults() {
        std::cout << "╔═══════════════════════════════════════════════════════════╗\n";
        std::cout << "║                      TEST RESULTS                          ║\n";
        std::cout << "║  Passed: " << passed << "  |  Failed: " << failed << "                          ║\n";
        
        if (failed == 0) {
            std::cout << "║                   ✓ ALL TESTS PASSED                      ║\n";
        } else {
            std::cout << "║                  ✗ SOME TESTS FAILED                      ║\n";
        }
        
        std::cout << "╚═══════════════════════════════════════════════════════════╝\n\n";
    }
};

}  // namespace Nauvoo
