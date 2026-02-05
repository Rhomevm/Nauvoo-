#pragma once

#include "../Engine/CoreTypes.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Nauvoo {

class ReputationManager;

/**
 * Manages dialogue trees, choices, and NPC conversations
 */
class DialogueManager {
public:
    DialogueManager(ReputationManager* reputation_mgr);
    ~DialogueManager();

    // Load dialogue trees from data
    void LoadDialogueTrees(const std::string& dialogue_data_file);
    void AddDialogueTree(const FDialogueTree& tree);

    // Dialogue state
    void StartDialogue(const std::string& npc_id, const std::string& dialogue_tree_id);
    void EndDialogue();
    bool IsInDialogue() const { return current_dialogue_tree != nullptr; }

    // Navigation
    std::string GetCurrentNodeText() const;
    std::vector<FDialogueOption> GetAvailableChoices(const std::string& npc_id) const;
    void SelectChoice(int choice_index, const std::string& npc_id);

    // State tracking
    std::string GetCurrentNPCId() const { return current_npc_id; }
    std::string GetCurrentNodeId() const { return current_node_id; }

    // Dialogue availability
    bool CanStartDialogue(const std::string& npc_id, const std::string& dialogue_tree_id) const;

    // Check if option available based on reputation
    bool IsChoiceAvailable(const FDialogueOption& choice, const std::string& npc_id) const;

    // Get NPC name for dialogue display
    std::string GetNPCName(const std::string& npc_id) const;

    // Debug
    void PrintCurrentDialogue() const;

private:
    std::map<std::string, FDialogueTree> dialogue_trees;  // Tree_ID -> Tree
    std::map<std::string, std::vector<std::string>> npc_available_dialogues;  // NPC_ID -> [Tree_IDs]

    // Current dialogue state
    FDialogueTree* current_dialogue_tree = nullptr;
    FDialogueNode* current_node = nullptr;
    std::string current_npc_id;
    std::string current_node_id;

    ReputationManager* reputation_manager = nullptr;

    // Helper functions
    FDialogueNode* FindNode(const std::string& node_id) const;
    void EvaluateConditionNode(FDialogueNode* condition_node);
};

}  // namespace Nauvoo
