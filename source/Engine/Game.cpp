#include "Game.h"
#include "../Systems/DialogueManager.h"
#include <iostream>
#include <fstream>

namespace Nauvoo {

NauvooGame::NauvooGame() {
    game_manager = std::make_unique<GameManager>();
}

NauvooGame::~NauvooGame() = default;

void NauvooGame::Initialize() {
    std::cout << "===========================================\n";
    std::cout << "   NAUVOO: LEGION - Initialization\n";
    std::cout << "===========================================\n" << std::endl;

    game_manager->Initialize();
    CreateInitialNPCs();
    CreateDialogueTrees();
    CreateStartingLocation();

    std::cout << "\n✓ Game initialized successfully\n" << std::endl;
}

void NauvooGame::LoadContent() {
    std::cout << "[Game] Loading content..." << std::endl;
    // Would load textures, models, audio, etc.
    std::cout << "[Game] Content loaded" << std::endl;
}

void NauvooGame::Run() {
    std::cout << "[Game] Starting main game loop..." << std::endl;
    
    const float DELTA_TIME = 0.016f;  // ~60 FPS
    int frame_count = 0;
    
    // Run for demonstration (100 in-game days)
    while (is_running && frame_count < 6000) {
        Update(DELTA_TIME);
        Render();
        frame_count++;
    }
    
    std::cout << "[Game] Main loop exited" << std::endl;
}

bool NauvooGame::Update(float delta_time) {
    game_manager->Update(delta_time);
    
    // Every 100 frames (roughly 1.6 seconds), print time
    static int frame_counter = 0;
    frame_counter++;
    
    if (frame_counter % 100 == 0) {
        FDateTime time = game_manager->GetCurrentTime();
        std::cout << "Game Time: " << time.year << "-" << time.month << "-" << time.day 
                  << " " << (time.minute / 60) << ":" << (time.minute % 60 < 10 ? "0" : "") 
                  << (time.minute % 60) << std::endl;
    }
    
    return is_running;
}

void NauvooGame::Render() {
    // In a real engine, this would render the 3D scene
    // For MVP, we're console-based
}

void NauvooGame::CreateInitialNPCs() {
    std::cout << "[Game] Creating initial NPCs..." << std::endl;
    
    // Load NPCs from JSON or create programmatically
    // For MVP, create a few key NPCs
    
    FNPC captain;
    captain.id = "npc_captain_isaiah_marks";
    captain.name = "Captain Isaiah Marks";
    captain.age = 42;
    captain.occupation = "officer";
    captain.faction = EFaction::LEGION_SOLDIER;
    captain.rank = ELegionRank::CAPTAIN;
    captain.health = 100.0f;
    captain.max_health = 100.0f;
    captain.is_alive = true;
    captain.position = {0, 0, 0};
    game_manager->SpawnNPC(captain);
    
    FNPC sara;
    sara.id = "npc_sara_williams";
    sara.name = "Sara Williams";
    sara.age = 28;
    sara.occupation = "healer";
    sara.faction = EFaction::LDS_CIVILIAN;
    sara.health = 100.0f;
    sara.max_health = 100.0f;
    sara.is_alive = true;
    sara.position = {10, 0, 0};
    game_manager->SpawnNPC(sara);
    
    FNPC thomas;
    thomas.id = "npc_thomas_brown";
    thomas.name = "Thomas Brown";
    thomas.age = 35;
    thomas.occupation = "blacksmith";
    thomas.faction = EFaction::LDS_CIVILIAN;
    thomas.health = 100.0f;
    thomas.max_health = 100.0f;
    thomas.is_alive = true;
    thomas.position = {20, 0, 0};
    game_manager->SpawnNPC(thomas);
    
    FNPC elder;
    elder.id = "npc_elder_joseph";
    elder.name = "Elder Joseph Fielding";
    elder.age = 68;
    elder.occupation = "preacher";
    elder.faction = EFaction::LDS_CIVILIAN;
    elder.health = 100.0f;
    elder.max_health = 100.0f;
    elder.is_alive = true;
    elder.position = {30, 0, 0};
    game_manager->SpawnNPC(elder);
    
    FNPC commander;
    commander.id = "npc_commander_john";
    commander.name = "Commander John Smith";
    commander.age = 52;
    commander.occupation = "officer";
    commander.faction = EFaction::LEGION_SOLDIER;
    commander.rank = ELegionRank::COMMANDER;
    commander.health = 100.0f;
    commander.max_health = 100.0f;
    commander.is_alive = true;
    commander.position = {5, 0, 0};
    game_manager->SpawnNPC(commander);
    
    std::cout << "  Created 5 initial NPCs" << std::endl;
}

void NauvooGame::CreateDialogueTrees() {
    std::cout << "[Game] Creating dialogue trees..." << std::endl;
    
    // Would load from dialogue_trees.json
    // For MVP, create basic dialogue trees
    
    auto dialogue_mgr = game_manager->GetDialogueManager();
    
    // Example dialogue tree for Captain Marks introduction
    FDialogueTree marks_tree;
    marks_tree.id = "dialogue_captain_marks_intro";
    marks_tree.npc_id = "npc_captain_isaiah_marks";
    marks_tree.root_node_id = "node_marks_intro_1";
    
    FDialogueNode intro_node;
    intro_node.id = "node_marks_intro_1";
    intro_node.type = "speech";
    intro_node.speaker_npc_id = "npc_captain_isaiah_marks";
    intro_node.text = "Welcome to the Nauvoo Legion, recruit. I'm Captain Isaac Marks. I expect you'll pull your weight around here.";
    intro_node.audio_cue_id = "";
    intro_node.next_node_id = "node_marks_choices";
    marks_tree.nodes.push_back(intro_node);
    
    FDialogueNode choice_node;
    choice_node.id = "node_marks_choices";
    choice_node.type = "choice";
    
    FDialogueOption opt1;
    opt1.id = "choice_marks_eager";
    opt1.display_text = "I'm ready to serve the Legion with honor.";
    opt1.next_node_id = "node_marks_response_eager";
    opt1.legion_rep_delta = 10;
    choice_node.choices.push_back(opt1);
    
    FDialogueOption opt2;
    opt2.id = "choice_marks_questions";
    opt2.display_text = "What exactly will be expected of me?";
    opt2.next_node_id = "node_marks_response_questions";
    choice_node.choices.push_back(opt2);
    
    marks_tree.nodes.push_back(choice_node);
    
    dialogue_mgr->AddDialogueTree(marks_tree);
    
    std::cout << "  Created basic dialogue trees" << std::endl;
}

void NauvooGame::CreateStartingLocation() {
    std::cout << "[Game] Setting starting location..." << std::endl;
    
    // Set player starting position
    FPlayerState& player = game_manager->GetPlayerState();
    player.position = {0, 0, 0};  // Town square
    
    std::cout << "  Player starting position set" << std::endl;
}

}  // namespace Nauvoo
