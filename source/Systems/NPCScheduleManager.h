#pragma once

#include "../Engine/CoreTypes.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Nauvoo {

/**
 * Manages NPC daily routines and schedule-based behavior
 */
class NPCScheduleManager {
public:
    NPCScheduleManager();
    ~NPCScheduleManager();

    // Initialize schedules
    void LoadSchedules(const std::string& schedule_data_file);
    void AddSchedule(const FNPCSchedule& schedule);

    // Update routines based on time
    void UpdateNPCSchedules(FDateTime current_time, std::vector<FNPC>& all_npcs);

    // Get NPC's current activity
    FScheduleActivity* GetCurrentActivity(FNPC& npc, FDateTime current_time);

    // Check if NPC should be at location
    bool IsNPCAtLocation(const FNPC& npc, const std::string& location_id, FDateTime current_time) const;

    // Get all NPCs at a location
    std::vector<std::string> GetNPCsAtLocation(const std::string& location_id, 
                                              FDateTime current_time, 
                                              const std::vector<FNPC>& all_npcs) const;

    // Event override (interrupt normal schedule)
    void SetEventOverride(const std::string& npc_id, const std::string& event_id, 
                         const std::vector<FScheduleActivity>& override_activities);
    void ClearEventOverride(const std::string& npc_id);

    // Debug
    void PrintNPCSchedule(const std::string& npc_id) const;

private:
    std::map<std::string, FNPCSchedule> schedules;  // NPC_ID -> Schedule
    std::map<std::string, std::pair<std::string, std::vector<FScheduleActivity>>> event_overrides;  // NPC_ID -> (event_id, activities)

    FScheduleActivity* FindActivityForTime(const std::vector<FScheduleActivity>& activities, int minute) const;
};

}  // namespace Nauvoo
