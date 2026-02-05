# NPC SYSTEM ARCHITECTURE

## Overview
The NPC system is the backbone of world simulation. Every NPC follows a schedule, maintains relationships, and responds dynamically to world state changes and player actions.

## Core Data Structure

### NPC Definition
```
NPC {
  id: string (unique identifier)
  name: string
  age: int
  occupation: Occupation (enum: farmer, soldier, blacksmith, etc.)
  appearance: AppearanceData
  beliefs: Belief[] (e.g., "faithful", "skeptical", "defensive")
  
  home: Location (building reference)
  faction: Faction (LDS_Civilian, Legion_Soldier, Outsider)
  rank: Rank (if applicable)
  
  schedule: Schedule (see below)
  relationships: Map<NPC_ID, Relationship>
  reputation_with_player: ReputationData
  memory: ActionMemory[]
}
```

### NPC Schedule
```
Schedule {
  daily_routine: Activity[] (ordered by time)
  seasonal_variations: Map<Season, Activity[]>
  event_overrides: Map<Event, Activity[]>
}

Activity {
  time_start: int (0-1440 minutes)
  time_end: int
  location: Location
  action: Action (enum: "work", "rest", "socialize", "pray", "eat", etc.)
  interruptible: bool (can NPCs leave early if urgent?)
  social_group: NPC[] (who is this NPC with during this activity?)
}
```

### Relationships
```
Relationship {
  target_npc: NPC_ID
  trust: int (-100 to 100)
  fear: int (0 to 100)
  respect: int (-100 to 100)
  intimacy: int (0 to 100)
  last_interaction: datetime
  shared_memories: ActionMemory[]
}
```

### Reputation with Player
```
ReputationData {
  trust: int (-100 to 100)
  fear: int (0 to 100)
  respect: int (-100 to 100)
  memory_of_player: PlayerAction[]
  will_help: bool
  will_report: bool (to superiors, to rivals?)
  will_lie_to_player: bool (based on trust/fear)
  dialogue_availability: DialogueOption[] (conditional on values)
}
```

### Action Memory
```
ActionMemory {
  player_action: string (description)
  timestamp: datetime
  relevance: int (how much does this matter to this NPC?)
  emotional_response: Emotion (angry, grateful, fearful, confused)
  will_gossip_about: bool
}
```

## NPC Simulation Loop

### Per-Day Execution
1. **Time Initialization:** Set game time to 6:00 AM
2. **Schedule Check:** For each NPC, determine their current activity based on time
3. **Location Spawning:** Spawn NPC at their scheduled location
4. **Interaction:** If player is nearby, run NPC behavior
5. **Social Interaction:** NPCs interact with other NPCs in the same location
6. **Gossip:** Spread rumors, update relationships based on conversation
7. **Time Advance:** Move to next scheduled activity (or next hour if no change)
8. **Repeat:** Continue until 12:00 AM, save world state

### NPC Behavior Tree
```
BehaviorTree(NPC) {
  1. Check Schedule
     → If time matches scheduled activity, execute activity
     → Else, go idle at current location
  
  2. Player Presence Check
     → Is player within perception range?
     → What is NPC's trust/fear of player?
     → Adjust dialogue availability
  
  3. Social Behavior
     → Are other NPCs in same location?
     → Should I interact? (based on relationship)
     → Engage in dialogue or joint activity
  
  4. Event Response
     → Has a significant event occurred? (violence, announcement, etc.)
     → Does this NPC care?
     → Update behavior/routine temporarily
  
  5. Player Interaction
     → Is player attempting to talk to me?
     → What dialogue options are available?
     → How does my response affect my reputation with player?
     → How does this spread as gossip?
}
```

## Gossip & Information Spread

### Gossip System
```
Gossip {
  source_npc: NPC_ID
  claim: string (description of information)
  truth_value: float (0.0 = complete lie, 1.0 = truth)
  emotional_spin: Spin (favorable, neutral, damaging)
  heard_by: Set<NPC_ID>
  timestamp_heard: datetime
  spread_likelihood: float (will this NPC repeat this?)
}
```

### Spread Mechanics
1. **Witnessing:** NPC witnesses player action → Creates memory
2. **Processing:** NPC processes memory → Determines importance & emotional response
3. **Spreading:** At next social interaction, NPC may mention action to other NPCs
4. **Viral:** Other NPCs add own interpretation → Gossip becomes distorted
5. **Culmination:** Reputation shifts based on what others have heard

**Factors Affecting Spread:**
- Trust/fear between gossiper and listener
- Emotional charge of the gossip
- Social status of gossiper (officer's gossip spreads faster)
- Location frequency (marketplace gossip spreads wider)
- Competing narratives (conflicting reports reduce impact)

## Faction Reputation

### Three Reputation Tracks

**Legion Reputation** (soldiers & officers)
- How loyal you are to commands
- How well you perform duty
- How brutal you are (impacts recruitment/morale)
- Track: -100 (deserter) to +100 (exemplary soldier)

**Community Reputation** (civilians)
- How much you help townspeople
- How fairly you enforce rules
- Whether you prioritize them over Legion
- Track: -100 (threat) to +100 (hero)

**Outsider Perception**
- Whether you're seen as a threat
- Prejudicial assumptions about Legion members
- Your individual standing among outside groups
- Track: -100 (target) to +100 (respected outsider liaison)

### Reputation Modifiers
```
Modifier {
  action: HistoricalAction
  legion_delta: int
  community_delta: int
  outsider_delta: int
  decay_rate: float (how fast does reputation decay?)
  spread_radius: int (how many NPCs hear about this?)
}
```

Example modifiers:
- Beating a prisoner (Legion: +20, Community: -50, Outsider: -30)
- Helping injured child (Legion: -5, Community: +30, Outsider: +10)
- Preventing a fight (Legion: +0, Community: +25, Outsider: +15)

## NPC Decision-Making

### NPC Motivations
```
Motivation {
  type: MotivationType (survive, prosper, protect_family, maintain_order, etc.)
  strength: int (0-100; how important?)
  conflicts_with: Motivation[] (conflicting goals?)
  triggers: Condition[] (what sparks this motivation?)
}
```

### NPC Response to Player
When player approaches NPC:
1. **Threat Assessment:** Is this person dangerous? (based on reputation)
2. **Opportunity Assessment:** Is this person useful? (based on rank/ability)
3. **Emotional State:** What is my current emotional state? (fear, joy, anger)
4. **Dialogue Branch:** Choose dialogue tree based on above factors
5. **Action:** Engage, flee, report, attack, or assist

## Implementation Priority (MVP)

### Phase 1: Core Framework
- [ ] NPC data structure definition
- [ ] Schedule system (simple: 6 activities per day)
- [ ] Location spawning (appear at right place, right time)
- [ ] Basic dialogue system (text only, no voice)
- [ ] Reputation tracking (Legion, Community, Personal)

### Phase 2: Simulation Depth
- [ ] NPC-to-NPC relationships
- [ ] Gossip system (spreading rumors)
- [ ] Memory system (remembering player actions)
- [ ] Dynamic dialogue (branching based on reputation)
- [ ] Faction allegiance

### Phase 3: Polish
- [ ] Voice acting integration
- [ ] Animation-driven activities
- [ ] Crowd behavior (multiple NPCs interacting)
- [ ] Event-driven behavior changes
- [ ] Emotional expression (animation, posture)

## Example NPC Schedule (Captain Isaiah Marks)

| Time | Activity | Location | Social | Notes |
|------|----------|----------|--------|-------|
| 6:00–7:00 | Wake, breakfast | Home | Family | Alone if family away |
| 7:00–8:00 | Travel & prep | HQ | Soldiers | Brief soldiers for day |
| 8:00–12:00 | Drill supervision | Drill grounds | 20+ soldiers | Leads training |
| 12:00–1:00 | Lunch | Market | Other officers | Often discusses tensions |
| 1:00–5:00 | Smithing work | Smithy | Customers | Also militia repairs |
| 5:00–6:00 | Patrol | Streets/gates | Patrol team | Secures perimeter |
| 6:00–8:00 | Dinner & family | Home | Family | Evening with children |
| 8:00–9:00 | Meeting | Hall | Officers | Planning, discussion |
| 9:00–10:00 | Hometown walk | Streets | Variable | Often patrol prep |
| 10:00+ | Sleep | Home | — | Exits public spaces |

**Seasonal Variation (Summer):**
- Drills extended to 1:00 PM (heat, preparation for conflict)
- Smith closes earlier (heat exhaustion)
- Patrol increases to 6:00–7:00 PM

**Event Override (Outsider Attack Alert):**
- Abandons all activities
- Moves to HQ
- Begins emergency drill

---

**NPC System Status:** Ready for development  
**Implementation Complexity:** High (multi-system dependency)  
**Team Size:** 1 Systems Programmer + 1 Designer
