#include "../Systems/DialogueManager.h"
#include "ReputationManager.h"
#include <iostream>
#include <algorithm>

namespace Nauvoo {

DialogueManager::DialogueManager(ReputationManager* reputation_mgr)
    : reputation_manager(reputation_mgr) {
}

DialogueManager::~DialogueManager() = default;

void DialogueManager::LoadDialogueTrees(const std::string& dialogue_data_file) {
    std::cout << "[DialogueManager] Dialogue trees loaded from " << dialogue_data_file << std::endl;
}

void DialogueManager::AddDialogueTree(const FDialogueTree& tree) {
    dialogue_trees[tree.id] = tree;
    
    if (npc_available_dialogues.find(tree.npc_id) == npc_available_dialogues.end()) {
        npc_available_dialogues[tree.npc_id] = {};
    }
    npc_available_dialogues[tree.npc_id].push_back(tree.id);
    
    std::cout << "[DialogueManager] Added dialogue tree: " << tree.id << " for NPC " << tree.npc_id << std::endl;
}

void DialogueManager::StartDialogue(const std::string& npc_id, const std::string& dialogue_tree_id) {
    auto tree_it = dialogue_trees.find(dialogue_tree_id);
    if (tree_it == dialogue_trees.end()) {
        std::cout << "[DialogueManager] Dialogue tree not found: " << dialogue_tree_id << std::endl;
        return;
    }

    current_dialogue_tree = &tree_it->second;
    current_npc_id = npc_id;
    current_node_id = current_dialogue_tree->root_node_id;
    current_node = FindNode(current_node_id);
    
    std::cout << "[DialogueManager] Started dialogue: " << dialogue_tree_id << std::endl;
}

void DialogueManager::EndDialogue() {
    current_dialogue_tree = nullptr;
    current_node = nullptr;
    current_npc_id.clear();
    current_node_id.clear();
    std::cout << "[DialogueManager] Dialogue ended" << std::endl;
}

std::string DialogueManager::GetCurrentNodeText() const {
    if (!current_node) return "";
    return current_node->text;
}

std::vector<FDialogueOption> DialogueManager::GetAvailableChoices(const std::string& npc_id) const {
    std::vector<FDialogueOption> available;
    
    if (!current_node) return available;

    for (const auto& choice : current_node->choices) {
        if (IsChoiceAvailable(choice, npc_id)) {
            available.push_back(choice);
        }
    }

    return available;
}

void DialogueManager::SelectChoice(int choice_index, const std::string& npc_id) {
    if (!current_node) return;

    if (choice_index < 0 || choice_index >= static_cast<int>(current_node->choices.size())) {
        std::cout << "[DialogueManager] Invalid choice index" << std::endl;
        return;
    }

    const FDialogueOption& choice = current_node->choices[choice_index];

    // Apply consequences
    if (!choice.consequence_action.empty()) {
        std::cout << "[DialogueManager] Applying consequence: " << choice.consequence_action << std::endl;
        
        if (reputation_manager) {
            reputation_manager->ModifyNPCTrust(npc_id, choice.legion_rep_delta);
        }
    }

    // Move to next node
    current_node_id = choice.next_node_id;
    current_node = FindNode(current_node_id);
    std::cout << "[DialogueManager] Choice selected, moving to next node" << std::endl;
}

bool DialogueManager::CanStartDialogue(const std::string& npc_id, const std::string& dialogue_tree_id) const {
    auto npc_dialogues = npc_available_dialogues.find(npc_id);
    if (npc_dialogues == npc_available_dialogues.end()) return false;

    return std::find(npc_dialogues->second.begin(), npc_dialogues->second.end(), dialogue_tree_id)
           != npc_dialogues->second.end();
}

bool DialogueManager::IsChoiceAvailable(const FDialogueOption& choice, const std::string& npc_id) const {
    // Check reputation requirements
    if (choice.legion_rep_requirement > -999) {
        if (reputation_manager && reputation_manager->GetLegionReputation() < choice.legion_rep_requirement) {
            return false;
        }
    }

    if (choice.npc_trust_requirement > -999) {
        if (reputation_manager && reputation_manager->GetNPCTrust(npc_id) < choice.npc_trust_requirement) {
            return false;
        }
    }

    return true;
}

std::string DialogueManager::GetNPCName(const std::string& npc_id) const {
    // Would look up NPC name from game manager
    return npc_id;
}

FDialogueNode* DialogueManager::FindNode(const std::string& node_id) const {
    if (!current_dialogue_tree) return nullptr;

    for (auto& node : current_dialogue_tree->nodes) {
        if (node.id == node_id) {
            return &const_cast<FDialogueNode&>(node);
        }
    }

    return nullptr;
}

void DialogueManager::EvaluateConditionNode(FDialogueNode* condition_node) {
    if (!condition_node) return;

    // Would evaluate conditions and update current_node accordingly
    std::cout << "[DialogueManager] Evaluating condition: " << condition_node->condition_type << std::endl;
}

void DialogueManager::PrintCurrentDialogue() const {
    if (!current_node) {
        std::cout << "No dialogue active" << std::endl;
        return;
    }

    std::cout << "\n=== CURRENT DIALOGUE ===" << std::endl;
    std::cout << "NPC: " << current_npc_id << std::endl;
    std::cout << "Text: " << current_node->text << std::endl;
    
    auto available = GetAvailableChoices(current_npc_id);
    std::cout << "Available choices: " << available.size() << std::endl;
    for (int i = 0; i < static_cast<int>(available.size()); ++i) {
        std::cout << "  [" << i << "] " << available[i].display_text << std::endl;
    }
}

}  // namespace Nauvoo
