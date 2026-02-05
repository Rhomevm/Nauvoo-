#include "../Systems/NPCScheduleManager.h"
#include <iostream>

namespace Nauvoo {

NPCScheduleManager::NPCScheduleManager() = default;

NPCScheduleManager::~NPCScheduleManager() = default;

void NPCScheduleManager::LoadSchedules(const std::string& schedule_data_file) {
    // Would load from JSON file
    // For MVP, schedules are hard-coded in character creation
    std::cout << "[ScheduleManager] Schedules loaded from " << schedule_data_file << std::endl;
}

void NPCScheduleManager::AddSchedule(const FNPCSchedule& schedule) {
    schedules[schedule.npc_id] = schedule;
    std::cout << "[ScheduleManager] Schedule added for NPC: " << schedule.npc_id << std::endl;
}

void NPCScheduleManager::UpdateNPCSchedules(FDateTime current_time, std::vector<FNPC>& all_npcs) {
    for (auto& npc : all_npcs) {
        if (!npc.is_alive) continue;
        
        auto schedule_it = schedules.find(npc.id);
        if (schedule_it == schedules.end()) continue;
        
        const FNPCSchedule& schedule = schedule_it->second;
        
        // Get activities for this season
        const auto& activities = schedule.daily_routine;
        
        // Find current activity based on time
        FScheduleActivity* current_activity = FindActivityForTime(activities, current_time.minute);
        
        if (current_activity) {
            npc.current_activity = current_activity;
        }
    }
}

FScheduleActivity* NPCScheduleManager::GetCurrentActivity(FNPC& npc, FDateTime current_time) {
    auto schedule_it = schedules.find(npc.id);
    if (schedule_it == schedules.end()) return nullptr;
    
    const FNPCSchedule& schedule = schedule_it->second;
    return FindActivityForTime(schedule.daily_routine, current_time.minute);
}

bool NPCScheduleManager::IsNPCAtLocation(const FNPC& npc, const std::string& location_id, 
                                       FDateTime current_time) const {
    if (!npc.is_alive) return false;
    
    auto schedule_it = schedules.find(npc.id);
    if (schedule_it == schedules.end()) return false;
    
    const FNPCSchedule& schedule = schedule_it->second;
    const auto& activity = FindActivityForTime(
        const_cast<std::vector<FScheduleActivity>&>(schedule.daily_routine), 
        current_time.minute);
    
    return activity && activity->location_id == location_id;
}

std::vector<std::string> NPCScheduleManager::GetNPCsAtLocation(const std::string& location_id,
                                                             FDateTime current_time,
                                                             const std::vector<FNPC>& all_npcs) const {
    std::vector<std::string> npcs_at_location;
    
    for (const auto& npc : all_npcs) {
        if (IsNPCAtLocation(npc, location_id, current_time)) {
            npcs_at_location.push_back(npc.id);
        }
    }
    
    return npcs_at_location;
}

void NPCScheduleManager::SetEventOverride(const std::string& npc_id, const std::string& event_id,
                                         const std::vector<FScheduleActivity>& override_activities) {
    event_overrides[npc_id] = { event_id, override_activities };
    std::cout << "[ScheduleManager] Event override set for NPC " << npc_id << std::endl;
}

void NPCScheduleManager::ClearEventOverride(const std::string& npc_id) {
    auto it = event_overrides.find(npc_id);
    if (it != event_overrides.end()) {
        event_overrides.erase(it);
        std::cout << "[ScheduleManager] Event override cleared for NPC " << npc_id << std::endl;
    }
}

FScheduleActivity* NPCScheduleManager::FindActivityForTime(const std::vector<FScheduleActivity>& activities,
                                                          int minute) const {
    for (auto& activity : const_cast<std::vector<FScheduleActivity>&>(activities)) {
        if (minute >= activity.time_start_minute && minute < activity.time_end_minute) {
            return &activity;
        }
    }
    
    // Return last activity (sleep/idle)
    if (!activities.empty()) {
        return &const_cast<std::vector<FScheduleActivity>&>(activities).back();
    }
    
    return nullptr;
}

void NPCScheduleManager::PrintNPCSchedule(const std::string& npc_id) const {
    auto schedule_it = schedules.find(npc_id);
    if (schedule_it == schedules.end()) {
        std::cout << "Schedule not found for NPC: " << npc_id << std::endl;
        return;
    }
    
    const FNPCSchedule& schedule = schedule_it->second;
    std::cout << "\n=== SCHEDULE FOR " << npc_id << " ===" << std::endl;
    
    for (const auto& activity : schedule.daily_routine) {
        int start_hour = activity.time_start_minute / 60;
        int start_min = activity.time_start_minute % 60;
        int end_hour = activity.time_end_minute / 60;
        int end_min = activity.time_end_minute % 60;
        
        std::cout << start_hour << ":" << (start_min < 10 ? "0" : "") << start_min << " - "
                 << end_hour << ":" << (end_min < 10 ? "0" : "") << end_min << ": "
                 << activity.location_id << std::endl;
    }
}

}  // namespace Nauvoo
