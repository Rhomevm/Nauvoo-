# TECHNICAL ARCHITECTURE & SYSTEMS DESIGN

## Engine Recommendation: Unreal Engine 5

### Rationale
- **First-Person Excellence:** Built-in FPS controller, camera systems, animation blending
- **NPC Scheduling:** Blueprint visual scripting perfect for scheduling complex routines
- **Performance:** Optimized for large open worlds, 60+ FPS target achievable
- **Audio:** Advanced audio system (spatial, reverb, mixing)
- **Save/Load:** Robust serialization system for persistent world state
- **Community:** Large existing codebase for historical games

### Alternatives Evaluated
- **Unity HDRP:** Lighter weight, smaller learning curve, but less mature first-person tooling
- **Godot:** Open-source, but limited FPS infrastructure and no mature dialogue system
- *Recommendation:* Start with UE5; pivot to Unity if team/resources require it

## Core System Architecture

### 1. Save & Persistence System

**What Gets Saved:**
```
PlayerState {
  position: Vector3
  health: int
  inventory: Item[]
  equipped: Weapon
  rank: Rank
  legion_reputation: int
  community_reputation: int
  outsider_reputation: int
  personal_integrity: int
  action_history: PlayerAction[]
}

WorldState {
  current_time: DateTime
  current_season: Season
  npc_states: Map<NPC_ID, NPCState>
  location_states: Map<LocationID, LocationState>
  event_flags: Set<EventFlag>
  completed_quests: Set<QuestID>
}

NPCState {
  position: Vector3
  health: int
  faction: Faction
  relationships: Map<NPC_ID, Relationship>
  reputation_with_player: ReputationData
  current_schedule_activity: Activity
  status: Status (alive, dead, fled, imprisoned)
}

LocationState {
  building_damage: float (0-1, 0=pristine, 1=destroyed)
  bloodstains: List<Vector3>
  bodies: List<DeadNPC>
  items_on_ground: Item[]
  fortifications: List<Fortification>
}
```

**Save Implementation:**
- **Autosave:** Every in-game hour (player can toggle)
- **Manual Save:** At designated rest locations (home, barracks)
- **Multiple Slots:** Unlimited (cloud or local)
- **Ironman Mode:** Single save file; no reload (permadeath)

**World Persistence:**
- All NPC state saved to disk
- Time persists across save/load
- Reputation changes permanent
- Dead NPCs remain dead (unless special revival)

### 2. NPC Scheduling & AI System

**Scheduling Architecture:**

```cpp
class ScheduleManager {
  Map<NPC_ID, Schedule> npc_schedules;
  
  void UpdateAllNPCs(float delta_time) {
    for (auto& npc : all_npcs) {
      Activity current_activity = npc->schedule->GetActivityForTime(game_time);
      UpdateNPCBehavior(npc, current_activity);
    }
  }
  
  void UpdateNPCBehavior(NPC* npc, Activity& activity) {
    // Move to location
    npc->MoveTo(activity.location);
    
    // Perform action (work, rest, socialize)
    npc->PerformAction(activity.action);
    
    // Check for interactions (player, other NPCs)
    npc->CheckForInteractions();
    
    // Update relationships based on interactions
    npc->UpdateRelationships();
  }
}
```

**Routing & Pathfinding:**
- Use UE5 Recast Navigation mesh
- NPCs navigate between known locations
- Handles dynamic obstacles (other NPCs, structures)

**Social Interaction:**
- NPCs in same location (within perception radius) can talk
- Dialogue determined by relationship + current mood
- Gossip spreads through social networks

### 3. Reputation & Consequence System

**Reputation Manager:**

```cpp
class ReputationManager {
  int legion_reputation = 0;
  int community_reputation = 0;
  int outsider_reputation = 0;
  int personal_integrity = 0;
  
  vector<PlayerAction> action_history;
  map<NPC_ID, vector<ActionMemory>> npc_memories;
  
  void RecordPlayerAction(const PlayerAction& action) {
    // Look up modifiers from lookup table
    ReputationModifier mod = ACTION_MODIFIERS[action.type];
    
    // Apply changes
    legion_reputation += mod.legion_delta;
    community_reputation += mod.community_delta;
    outsider_reputation += mod.outsider_delta;
    
    // Clamp to [-100, 100]
    legion_reputation = FMath::Clamp(legion_reputation, -100, 100);
    community_reputation = FMath::Clamp(community_reputation, -100, 100);
    outsider_reputation = FMath::Clamp(outsider_reputation, -100, 100);
    
    // Notify affected NPCs
    for (NPC* witness : action.witnesses) {
      npc_memories[witness->id].push_back(action);
      witness->OnPlayerActionObserved(action);
    }
    
    // Broadcast rumor
    gossip_system.SpreadRumor(action);
    
    // Store action
    action_history.push_back(action);
  }
  
  bool CanAccessDialogue(const NPC& npc, const DialogueOption& option) {
    if (option.legion_requirement > 0 
        && legion_reputation < option.legion_requirement) {
      return false;
    }
    
    if (option.npc_trust_requirement > 0
        && npc.reputation_with_player.trust < option.npc_trust_requirement) {
      return false;
    }
    
    // Check other requirements...
    return true;
  }
}
```

**Consequence Application:**

```cpp
class ConsequenceSystem {
  void ApplyConsequence(const DialogueChoice& choice) {
    // Update reputation immediately
    reputation_manager.RecordPlayerAction(choice.as_action);
    
    // Trigger world events if consequence is significant
    if (choice.consequence_type == SIGNIFICANT) {
      TriggerWorldEvent(choice.consequence_event);
    }
    
    // Queue dialogue responses from NPCs
    for (NPC* npc : GetNearbyNPCs()) {
      if (npc->HasOpinionOnChoice(choice)) {
        QueueDialogueResponse(npc, choice);
      }
    }
  }
  
  void ApplyRepDec

ay(float delta_time) {
    const float DECAY_RATE = 0.05f;  // per day
    legion_reputation -= legion_decay_rate * delta_time;
    community_reputation -= community_decay_rate * delta_time;
    // Clamp values
  }
}
```

### 4. Dialogue & Choice System

**Dialogue Data Structure:**

```
DialogueTree {
  root_node: DialogueNode
  
  DialogueNode {
    id: string
    type: NodeType (speech, choice, condition, action)
    
    // Speech node
    speaker_id: NPC_ID
    text: string
    audio_cue: AudioCue
    
    // Choice node
    available_choices: DialogueChoice[]
    
    // Condition node
    conditions: Condition[]  // reputation checks, flag checks
    true_branch: DialogueNode
    false_branch: DialogueNode
    
    // Action node
    action_type: ActionType  // update_reputation, start_quest, etc
    action_parameter: any
    
    next_node: DialogueNode
  }
  
  DialogueChoice {
    text: string
    leads_to: DialogueNode
    availability_requirement: Requirement
    consequence_on_select: Consequence
    locks_out_dialogue: DialogueOption[]  // can't access these after
  }
}
```

**Dialogue Manager:**

```cpp
class DialogueManager {
  void StartDialogue(NPC* npc, DialogueTree* tree) {
    current_dialogue = tree;
    current_node = tree->root_node;
    DisplaySpeech(current_node);
  }
  
  void OnChoiceSelected(int choice_index) {
    DialogueChoice& choice = current_node->available_choices[choice_index];
    
    // Check if available
    if (!IsChoiceAvailable(choice)) {
      DisplayUnavailableMessage();
      return;
    }
    
    // Execute consequence
    consequence_system.ApplyConsequence(choice);
    
    // Update NPC relationship
    current_npc->OnDialogueChoice(choice);
    
    // Advance dialogue
    current_node = choice.leads_to;
    DisplaySpeech(current_node);
  }
  
  bool IsChoiceAvailable(const DialogueChoice& choice) {
    return reputation_manager.CanAccessDialogue(*current_npc, choice);
  }
}
```

### 5. Time System

**Game Time Manager:**

```cpp
class GameTimeManager {
  float current_minute = 0;  // 0-1440 per day
  int current_day = 0;
  Season current_season = SPRING;
  
  const float TIME_SCALE = 0.02f;  // 1 real sec = 1.2 game mins
  
  void UpdateTime(float delta_seconds) {
    current_minute += delta_seconds * TIME_SCALE;
    
    if (current_minute >= 1440) {
      // Day change
      current_minute = 0;
      current_day++;
      OnDayChanged();
    }
    
    if (current_day % 90 == 0) {
      // Season change (roughly 90 days/season)
      ChangeSeasonOnChange();
    }
  }
  
  void OnDayChanged() {
    // Update schedule for all NPCs
    schedule_manager.UpdateAllSchedules();
    
    // Apply reputation decay
    reputation_manager.ApplyDecay();
    
    // Process time-dependent events
    event_system.ProcessDailyEvents();
  }
}
```

**Time Display:**
- In-game HUD shows time in diegetic way (visible clock, sun position)
- Player can check journal for date
- No minimap time; encourage player to watch real environment cues

### 6. Combat System

**Combat Manager:**

```cpp
class CombatSystem {
  enum class CombatState { NORMAL, COMBAT, COOLDOWN };
  
  CombatState current_state = NORMAL;
  float combat_timeout = 0.f;  // when to exit combat
  
  void OnWeaponFired(APawn* firer, AWeapon* weapon) {
    // Calculate shot accuracy
    float base_accuracy = weapon->accuracy;
    float stance_modifier = GetStanceAccuracyMod(firer->stance);
    float fatigue_modifier = GetFatigueAccuracyMod(firer->stamina);
    float final_accuracy = base_accuracy * stance_modifier * fatigue_modifier;
    
    // Perform raycast
    FVector forward = firer->GetActorForwardVector();
    FVector spread = GetBulletSpread(final_accuracy);
    FVector target_direction = forward + spread;
    
    FHitResult hit_result;
    FVector end_pos = firer->GetActorLocation() + target_direction * 10000;
    
    if (GetWorld()->LineTraceSingleByChannel(hit_result, 
          firer->GetActorLocation(), end_pos, ...)) {
      // Handle hit
      if (AActor* hit_actor = hit_result.GetActor()) {
        if (APawn* pawn = Cast<APawn>(hit_actor)) {
          ApplyDamage(pawn, weapon->damage, hit_result.Location, hit_result.Normal);
          EnteredCombat(firer, pawn);
        }
      }
    }
    
    // Apply fatigue
    firer->stamina -= weapon->stamina_cost;
    
    // Audio feedback
    weapon->PlayFireSound(firer->GetActorLocation());
    
    // Visual feedback (muzzle flash, smoke)
    PlayMuzzleFlashVFX(firer, weapon);
    SpawnMuzzleSmokeCloud(weapon->GetMuzzleLocation());
  }
  
  void ApplyDamage(APawn* target, float damage, FVector hit_location) {
    // Determine hit location
    EBodyPart body_part = DetermineBodyPart(hit_location);
    
    // Apply damage
    target->health -= damage;
    
    // Create injury
    FInjury injury;
    injury.body_part = body_part;
    injury.severity = CalculateSeverity(damage);
    injury.bleed_rate = GetBleedRate(body_part);
    target->injuries.push_back(injury);
    
    // Audio feedback
    target->PlayPainVocalization();
    
    // Check if dead
    if (target->health <= 0) {
      OnCharacterDeath(target);
    }
  }
  
  void EnteredCombat(APawn* instigator, APawn* target) {
    if (current_state == CombatState::NORMAL) {
      current_state = CombatState::COMBAT;
      combat_timeout = 30.f;  // 30 sec before auto-exit if no more shooting
      
      // Alert nearby NPCs
      for (APawn* nearby : GetNearbyPawns(instigator, 500.f)) {
        nearby->OnCombatStarted(instigator, target);
      }
    }
  }
}
```

**Weapon System:**

```cpp
class AWeapon : public AActor {
  UPROPERTY() FString weapon_name = "Musket";
  UPROPERTY() float fire_rate = 1.0f;  // seconds between shots
  UPROPERTY() float reload_time = 50.f;  // seconds to reload
  UPROPERTY() float accuracy = 0.7f;  // accuracy base (0-1)
  UPROPERTY() float damage = 40.f;
  UPROPERTY() float stamina_cost = 15.f;
  
  UPROPERTY() int ammunition = 6;  // current rounds
  UPROPERTY() int max_ammunition = 6;
  
  void Fire(APawn* shooter) {
    if (ammunition <= 0) {
      DisplayTrace(TEXT("Out of ammo!"));
      return;
    }
    
    if (GetWorld()->GetTimerManager()->IsTimerActive(fire_rate_timer)) {
      return;  // Too soon after last shot
    }
    
    // Perform fire
    CombatSystem->OnWeaponFired(shooter, this);
    
    // Reduce ammo
    ammunition--;
    
    // Start reload timer
    GetWorld()->GetTimerManager()->SetTimer(fire_rate_timer, 
      fire_rate, false);
  }
  
  void Reload() {
    // Play reload animation
    PlayReloadAnimation();
    
    // Start reload timer
    GetWorld()->GetTimerManager()->SetTimer(reload_timer, 
      reload_time, false);
    
    // On completion
    GetWorld()->GetTimerManager()->SetTimerDelegate(reload_timer,
      FTimerDelegate::CreateUObject(this, &AWeapon::OnReloadComplete));
  }
  
  void OnReloadComplete() {
    ammunition = max_ammunition;
    DisplayTrace(TEXT("Reload complete"));
  }
}
```

### 7. Injury & Health System

**Health Manager:**

```cpp
class UHealthComponent : public UActorComponent {
  UPROPERTY() float max_health = 100.f;
  UPROPERTY() float current_health = 100.f;
  
  UPROPERTY() TArray<FInjury> injuries;
  
  UFUNCTION() void TakeDamage(float damage, const FVector& hit_location) {
    current_health -= damage;
    
    FInjury new_injury;
    new_injury.body_part = DetermineBodyPartFromLocation(hit_location);
    new_injury.severity = FMath::Min(damage / 10.f, 10.f);
    new_injury.bleed_rate = GetBleedRateForSeverity(new_injury.severity);
    new_injury.timestamp = GetWorld()->GetTimeSeconds();
    
    injuries.Add(new_injury);
    
    OnHealthChanged();
    
    if (current_health <= 0) {
      OnDeath();
    }
  }
  
  void UpdateBleeding(float delta_time) {
    float total_bleed = 0.f;
    
    for (FInjury& injury : injuries) {
      if (!injury.is_treated) {
        total_bleed += injury.bleed_rate;
        
        // Risk infection if untreated
        if (GetWorld()->GetTimeSeconds() - injury.timestamp > 60.f) {
          injury.infection_risk = true;
        }
      }
    }
    
    current_health -= total_bleed * delta_time;
  }
  
  void TreatInjury(int injury_index) {
    if (injury_index < injuries.Num()) {
      injuries[injury_index].is_treated = true;
      injuries[injury_index].bleed_rate = 0.f;
    }
  }
  
  void UpdateMovement(class ACharacter* owner) {
    // Determine movement penalty based on injuries
    float movement_multiplier = 1.0f;
    
    for (const FInjury& injury : injuries) {
      if (injury.body_part == EBodyPart::LEG && !injury.is_treated) {
        movement_multiplier *= 0.5f;  // legs broken = 50% speed
      }
    }
    
    owner->GetCharacterMovement()->MaxWalkSpeed *= movement_multiplier;
  }
}
```

## Performance Optimization

### NPC Management
- **LOD System:** Use Unreal's skeletal mesh LODs
  - High detail: Within ~50m (full animation)
  - Medium detail: 50-200m (simplified animation)
  - Low detail: 200m+ (debug capsule only)
- **Pathfinding cache:** Pre-compute common routes to minimize AI cost
- **Conversation culling:** Only simulate dialogue for nearby NPCs

### Rendering
- **Instancing:** Use FInstancedStaticMeshComponent for repetitive structures
- **Culling:** Frustum and occlusion culling enabled
- **Draw call batching:** Material atlasing for buildings
- **Target:** 60 FPS on RTX 2070 at 1440p

### Audio
- **Spatial audio:** 3D positioning for distant sounds
- **Culling:** Disable audio updates for distant NPCs
- **Streaming:** Music streamed (not loaded in memory)

## Development Roadmap

### Phase 1: Foundation (Months 0–2)
- [ ] UE5 project setup
- [ ] Player controller (movement, stamina)
- [ ] Basic world geometry (one district)
- [ ] Simple NPC with routine
- [ ] Save/load system

### Phase 2: Systems (Months 2–6)
- [ ] Full NPC scheduling
- [ ] Dialogue system
- [ ] Reputation tracking
- [ ] Combat (musket only)
- [ ] Injury system
- [ ] 10 full NPCs with personalities

### Phase 3: Content (Months 6–12)
- [ ] Drills & training
- [ ] Patrol missions
- [ ] Conflict scenarios
- [ ] Audio (voices, music, sfx)
- [ ] Art polish

### Phase 4: Integration & Polish (Months 12–18)
- [ ] Full world state integration
- [ ] Consequence chains
- [ ] Ending determination system
- [ ] Bug fixes & optimization
- [ ] QA & playtesting

---

**Status:** Comprehensive technical foundation defined  
**Next Step:** Engine setup and prototyping phase
