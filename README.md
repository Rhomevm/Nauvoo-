# NAUVOO: LEGION - Project Overview

**Status:** Initial Design Complete  
**Last Updated:** February 5, 2026  
**Project Manager:** Senior Game Designer / Lead Engineer  

---

## Quick Start Guide

This repository contains the complete design and initial scaffolding for **Nauvoo: Legion**, a historical first-person simulation set in 1840s Illinois.

### What's Included

```
Nauvoo-/
├── README.md (this file)
├── docs/
│   ├── GAME_DESIGN_DOCUMENT.md          [Complete GDD - START HERE]
│   └── IMPLEMENTATION_ROADMAP.md         [Development timeline & checklist]
├── design/
│   ├── NPC_SYSTEM_ARCHITECTURE.md       [NPC scheduling, relationships, behavior]
│   ├── REPUTATION_AND_MORAL_SYSTEM.md   [Reputation mechanics, consequences]
│   ├── COMBAT_SYSTEM_SPECIFICATION.md   [Weapons, damage, tactics]
│   ├── TECHNICAL_ARCHITECTURE.md        [Engine, systems, performance]
│   └── GAMEPLAY_LOOPS_DESIGN.md         [Daily life, Legion duty, escalation]
├── source/
│   ├── Engine/
│   │   └── CoreTypes.h                  [C++ type definitions]
│   ├── Systems/
│   │   └── action_modifiers.json        [Reputation modifier lookup table]
│   ├── Characters/
│   ├── Data/
│   │   ├── npc_schema.json              [NPC definition schema]
│   │   ├── Dialogue/
│   │   │   └── dialogue_schema.json     [Dialogue tree schema]
│   │   └── Locations/
│   ├── Tools/
│   └── (additional code modules)
├── art/
│   └── (future: models, textures, animations)
├── audio/
│   └── (future: music, voice lines, sound effects)
└── design/
    └── (documentation)
```

### Key Documents to Read (In Order)

1. **GAME_DESIGN_DOCUMENT.md**
   - Full creative vision
   - Setting, tone, and philosophy
   - All systems overview
   - Historical context

2. **TECHNICAL_ARCHITECTURE.md**
   - Engine selection and rationale
   - Core system design (C++ pseudo-code)
   - Performance targets
   - Development roadmap

3. **NPC_SYSTEM_ARCHITECTURE.md**
   - How NPCs work
   - Scheduling, relationships, behavior
   - Gossip and reputation spreading
   - Sample NPC data

4. **REPUTATION_AND_MORAL_SYSTEM.md**
   - Four reputation tracks
   - Choice consequences
   - Dialogue gating
   - No "good/evil" meter philosophy

5. **COMBAT_SYSTEM_SPECIFICATION.md**
   - Weapon mechanics (muskets, pistols, melee)
   - Damage and injury system
   - Enemy AI behavior
   - Combat scenarios

6. **GAMEPLAY_LOOPS_DESIGN.md**
   - Daily life routine
   - Legion duty assignments
   - Campaign progression (4 phases)
   - Social dynamics

7. **IMPLEMENTATION_ROADMAP.md**
   - Development timeline
   - Phase-by-phase breakdown
   - Technical debt tracking
   - Success metrics

---

## Core Design Pillars

### 1. Historical Grounding
- No fantasy or supernatural elements
- Respectful portrayal of faith and community
- Accurate portrayal of conflict (no caricatures)
- Period-appropriate technology and aesthetics

### 2. Immersive Simulation
- NPCs follow daily routines (not quest-dispensers)
- World state persists (actions have lasting consequences)
- Reputation is distributed (not binary good/evil)
- Time system affects everything (daily cycles, seasons)

### 3. Rare, Weighty Violence
- Combat is dangerous and consequential
- Most conflicts solvable through dialogue
- Injuries persist and require treatment
- Death is possible but relatively uncommon

### 4. Player Agency Within Constraint
- Can't escape the role (desertion has consequences)
- Can fulfill duty differently (merciful vs. strict)
- Can choose between competing loyalties
- Actions reshape the world within historical bounds

---

## Game Overview

### Setting
**Nauvoo, Illinois: 1841–1846**

The Latter-day Saint settler community establishes a town, forms a militia (the Nauvoo Legion), and faces escalating external pressure from neighboring communities. The player experiences this volatile period as a Legion member and townsperson.

### Player Role
A young settler who voluntarily joins the Nauvoo Legion. No origin customization; the character gains identity through choices and relationships.

**Progression:**
- Recruit → Trained Legionnaire → Officer (optional)
- Reputation in three tracks: Legion, Community, Outsiders
- Moral integrity measured through consistency

### Core Loops

**Daily Life Loop** (5–8 hours per day)
- Morning routines, work, meals, social time, guard duty, sleep
- Repeat: NPCs follow schedules, world state evolves

**Legion Duty Loop** (structured assignments)
- Drills, patrols, training, escort missions, investigation
- Performance affects rank and reputation

**Escalation Loop** (campaign progression)
- Phase 1: Peaceful arrival and integration
- Phase 2: Tensions rise, divisions emerge
- Phase 3: Crisis point, major decision moments
- Phase 4: Resolution based on player choices

---

## Technical Foundation

### Engine
**Unreal Engine 5** (recommended)
- Mature first-person systems
- Strong NPC scheduling capability (Blueprints)
- High-fidelity graphics
- Robust save/load infrastructure

### Core Systems
1. **Save & Persistence:** World state, NPC state, player progress
2. **NPC System:** Scheduling, relationships, gossip, behavior
3. **Reputation System:** Three tracks, action lookup table, consequence chains
4. **Dialogue System:** Branching trees, conditional availability, voice support
5. **Time System:** 24-hour day/night, seasonal changes, event scheduling
6. **Combat System:** Weapons, damage, injuries, NPC AI
7. **Consequence System:** Reputation ripples, NPC reaction, world changes

### Performance Target
- **60 FPS** at 1440p on mid-tier PC (RTX 2070 equivalent)
- No ray-tracing dependency
- Scalable NPC LOD system

---

## Development Timeline

### Phase 0: Engine Setup
**2 weeks**
- UE5 project creation
- Version control setup
- Asset import and configuration

### Phase 1: Foundation Systems
**8 weeks**
- Player controller and movement
- World geometry and locations
- Game time and scheduling
- Save/load system
- Basic dialogue
- **Deliverable:** Vertical slice with player in world, NPCs with routines

### Phase 2: Reputation & NPCs
**10 weeks**
- Reputation tracking and modifiers
- NPC relationships and gossip
- 10+ NPCs with full personalities
- Campaign Phase 1 events
- **Deliverable:** NPC system fully functional, player choices matter

### Phase 3: Combat
**8 weeks**
- Weapons (muskets, pistols, melee)
- Damage and injury system
- Enemy AI and combat behavior
- 3 combat scenarios
- **Deliverable:** Combat system complete and balanced

### Phase 4: Content & Campaign
**12 weeks**
- Campaign Phases 2–4
- Patrol and mission system
- Voice acting and audio
- 20+ NPCs, expanded content
- **Deliverable:** Full campaign playable

### Phase 5: Polish & QA
**6 weeks**
- Performance optimization
- Bug fixes
- Balance tuning
- Final playtesting
- **Deliverable:** Gold master ready

**Total: ~44 weeks (~10 months)**

---

## Design Highlights

### Choice & Consequence
- **No morality meter** — instead track Legion, Community, Outsider reputation
- **No "correct" choice** — all options have real costs
- **Cascading consequences** — ripples through community via gossip
- **Permanent changes** — NPC death, community trust, historical outcomes

### NPC Simulation
- **Daily routines** — NPCs follow schedules (work, eat, socialize, pray, sleep)
- **Relationships** — Trust, fear, respect, intimacy scores between all NPCs
- **Memory system** — NPCs remember player actions and spread rumors
- **Conditional behavior** — Actions change schedules (emergencies, conflicts)

### Immersion Systems
- **Minimal HUD** — No health bar, minimap, or quest markers (optional)
- **Diegetic UI** — Journal instead of quest log, maps are physical items
- **Animation weight** — All actions have realistic timing and cost
- **Audio atmosphere** — Footsteps, crowd ambience, sparse music

### Combat Philosophy
- **Dangerous, not empowering** — Musket shot can be lethal
- **Slow and deliberate** — Reload takes 45–60 seconds
- **Avoidable** — Most conflicts solvable through dialogue
- **Consequential** — Injuries persist, death is permanent (permadeath mode)

---

## Sample Content: Captain Isaiah Marks

**Example NPC combining all systems:**

| Attribute | Value |
|-----------|-------|
| Name | Captain Isaiah Marks |
| Age | 42 |
| Occupation | Militia officer, blacksmith |
| Faction | Nauvoo Legion |
| Rank | Captain |
| Belief | Defensive militia mandate |
| Relationship | Married, 2 children |
| Secret | Doubts leadership direction |

**Schedule (Daily):**
- 6:00–7:00 AM: Wake, breakfast with family
- 7:00–8:00 AM: Travel to HQ, brief soldiers
- 8:00 AM–12:00 PM: Drill supervision (20+ soldiers)
- 12:00–1:00 PM: Lunch (often discusses tensions with other officers)
- 1:00–5:00 PM: Smithing work at forge
- 5:00–6:00 PM: Perimeter patrol
- 6:00–8:00 PM: Dinner and family time
- 8:00–9:00 PM: Officers' meeting (planning, discussion)
- 9:00–10:00 PM: Evening walk (often patrol preparation)
- 10:00 PM+: Sleep

**Relationships:**
- Wife Sarah: Trust +80 (intimate)
- Commander John: Trust +70 (respects but secretly doubts)
- Sergeant James: Respect +60 (underling, reliable)
- Outer village scout: Fear +40 (potential threat)

**Reputation with Player:**
- Initial (new recruit): Neutral (0)
- After attending drills regularly: +15 Legion rep
- After befriending a civilian (his friend): -5 with Marks (views civilian-focused)
- After showing restraint in conflict: +20 Legion rep, +5 Community rep

**Dialogue:**
- Cannot discuss doubts until trust > +40
- Cannot ask for promotion until drills attended 5+ times
- Will defend player if they show loyalty
- Will report player misconduct to commander

---

## Design Philosophy: No Heroes

This game is **not** about power fantasy. You are:
- **A person** in a community, not its savior
- **Caught between loyalties** — duty vs. conscience
- **Subject to authority** — consequences for disobedience
- **Responsible for impacts** — actions ripple through community
- **Morally pressured** — face difficult choices with no "right" answer

## Implementation Status

- [x] Complete game design document
- [x] Technical architecture specification
- [x] NPC system design
- [x] Reputation system design
- [x] Combat system specification
- [x] Gameplay loops specification
- [x] Development roadmap
- [x] Core type definitions
- [x] Data schemas (JSON)
- [ ] Engine setup
- [ ] Phase 1 implementation (foundation)
- [ ] Phase 2–5 implementation

---

## Next Steps

1. **Engine Setup:** Initialize UE5 project, configure settings
2. **Prototype:** Build vertical slice with one NPC and player interaction
3. **Validation:** Test core systems (scheduling, dialogue, reputation)
4. **Iteration:** Refine based on playtest feedback
5. **Expansion:** Add more content and NPCs

---

## Team Structure

### Core Team (Minimum)
- **1 Lead Programmer** — Systems architecture, core gameplay
- **1 Systems Programmer** — NPC, dialogue, UI
- **1 Designer** — Level design, content, balance
- **1 Artist** — Modeling, materials, animations
- **1 Audio Designer** — SFX, voice direction, mixing

### Recommended Full Team
- Above + 2 additional programmers
- Above + 1–2 additional artists
- 1 voice director
- 1 QA tester
- 1 producer

---

## References & Inspiration

**Historical:**
- "The Nauvoo Legion" by John D. Lee
- Period journals and accounts
- Archaeological research

**Game Design:**
- Red Dead Redemption 2 (immersion, NPC routines)
- Disco Elysium (dialogue, consequence)
- Fallout: New Vegas (reputation, endings)
- Kingdom Come: Deliverance (historical grounding)

**Tone:**
- This War of Mine (moral complexity)
- Spec Ops: The Line (consequence of violence)
- Firewatch (atmospheric storytelling)

---

## Design Philosophy Summary

> Create an immersive first-person historical experience that makes the player feel what it was like to live, serve, and struggle in Nauvoo during a volatile and defining period of American history.

> You are not the hero. You are a person caught between duty, conscience, and community.

> Do not simplify. Do not modernize. Do not gamify tragedy.

---

## Contact & Questions

For design clarifications or technical questions, refer to the detailed specification documents. Each system has comprehensive documentation with implementation notes and technical details.

**Last Updated:** February 5, 2026  
**Project Status:** Ready for Development (Phase 0: Engine Setup)

---

**Nauvoo: Legion** - A historical first-person game exploring faith, duty, and the pressure of conflicting loyalties in pre-exodus Nauvoo.