# NAUVOO: LEGION
## Comprehensive Game Design Document

**Working Title:** Nauvoo: Legion  
**Genre:** Historical First-Person Simulation  
**Setting:** Nauvoo, Illinois (1841–1846)  
**Target Platform:** PC (Windows, Linux, Mac)  
**Estimated Scope:** 30–50 hour campaign  
**Target Audience:** 18+ (mature themes, historical conflict)  

---

## 1. EXECUTIVE SUMMARY

**Nauvoo: Legion** is a narrative-driven first-person historical simulation set during the defining years of the Nauvoo settlement in Illinois. The player takes on the role of a settler and member of the Nauvoo Legion, experiencing daily life, civic duty, and the escalating political tensions that ultimately led to the community's collapse.

The game prioritizes **immersion, consequence, and moral complexity** over action-oriented gameplay. Rather than a power fantasy, it explores themes of duty, loyalty, fear, and the pressure of divided identities.

### Core Pillars
- **Historical grounding** (no fantasy, no supernatural)
- **Immersive simulation** (daily routines, NPC relationships, persistent world state)
- **Moral consequence** (choices reshape the world within historical plausibility)
- **Rare, weighty violence** (combat is dangerous and consequential)
- **Player agency in a constrained role** (you're not the hero; you're part of a community)

---

## 2. SETTING & WORLD

### Historical Context
**Nauvoo, Illinois: 1841–1846** — a period of rapid growth, religious fervor, and mounting external pressure.

- The Latter-day Saint (LDS) community establishes a town in the Mississippi Valley
- Population grows to ~12,000+ settlers
- The **Nauvoo Legion** is formed as a state militia (officially sanctioned)
- External hostility from neighboring communities increases
- Theological controversies and internal rifts emerge
- Political power generates fear and opposition
- The settlement ultimately dissolves amid violence and forced exodus

### Map Structure
The playable world consists of:
- **Central District** (first district fully playable)
  - Meeting house and civic buildings
  - Market square
  - Residential blocks (2-3 story homes)
  - Workshops and trades
- **Outlying areas** (accessible via roads)
  - Farmland
  - Mississippi River shoreline
  - Militia drill grounds
  - Defensive positions (earthworks, fortifications)
- **Neighboring areas** (partially explorable)
  - Roads to surrounding settlements
  - Conflict hotspots
  - Wilderness

### Time & Season
- **Day/Night Cycle:** 24-hour gameplay hour = ~20 real-time minutes
- **Seasonal Changes:** Affect travel, farming, NPC availability
  - Spring: Growth, hope
  - Summer: Tension rising
  - Fall: Harvest and resource pressure
  - Winter: Isolation, limited access to some areas
- **Weather:** Rain, snow, clear skies affect movement, visibility, and NPC behavior

### Environmental Storytelling
- Architecture reflects 1840s frontier America
- Worn paths show frequent travel routes
- Militia structures dominate civic space
- Growing defensive implementations (walls, watches)
- Trade goods and craftwork visible in workshops
- Wear patterns on buildings show community stress

---

## 3. PLAYER CHARACTER & ROLE

### Starting Identity
The player is a **newly arrived settler** who voluntarily joins the Nauvoo Legion. No custom character creation; the player inherits a predetermined but narrative-flexible role.

- Age: ~20–30 (player-assumed background)
- Reason for joining Nauvoo: Varies by player interpretation (faith, opportunity, escape)
- Initial rank: Recruit in the Nauvoo Legion
- Initial skills: Basic physical capability; no combat training

### Progression Path
**Rank Advancement (Optional but available):**
- Recruit → Trained Legionnaire → Senior Legionnaire → Commissioned Officer → Commander
- Rank provides:
  - Access to restricted areas
  - Authority over other soldiers
  - Higher expectations from superiors
  - Increased responsibility for conflicts
  - More leverage in dialogue

**Identity Systems:**
1. **Legion Reputation** — How officers and soldiers view you
   - Loyalty, competence, brutality, mercy
2. **Community Reputation** — How townspeople view you
   - Trust, fear, respect, suspicion
3. **Outsider Perception** — How enemies/external groups view you
   - Threat level, tactical value, prejudice
4. **Moral Integrity** — Personal consistency in choices
   - Affects availability of certain dialogue options
   - Influences NPC trust in you

### Player Agency Within Constraint
The player **cannot** escape the role (desertion has severe consequences). Instead, the game explores:
- How you fulfill your duty when it conflicts with your conscience
- Whether you enforce laws or show mercy
- How you navigate between community, Legion, and personal integrity

---

## 4. CORE GAMEPLAY LOOPS

### 4.1 Daily Life Loop (Sandbox Foundation)
What the player does on a typical day:

**Morning:**
- Wake in assigned quarters or home
- Check message board for daily assignments
- Opt into work shifts (blacksmithing, farming, construction, etc.)
- Interact with townspeople (rumors, gossip, small quests)

**Midday:**
- Complete work or training
- Participate in Legion drills
- Attend community meetings
- Investigate rumors

**Evening:**
- Guard duty (rotating watch assignments)
- Interact socially (meals, conversations)
- Plan next day
- Sleep/rest

**Consequence:** Work affects standing, pay (currency), resource access.

### 4.2 Legion Duty Loop (Structured Gameplay)
Official militia responsibilities:

**Drills:**
- Formation marching
- Musket training and accuracy practice
- Hand-to-hand combat drills
- Cavalry maneuvers (if mounted)
- Officer lessons (if promoted)

**Assignments:**
- Perimeter patrols
- Gate watches
- Escort missions (civilians or supplies)
- Intelligence gathering (investigating rumors, scouting)
- Maintenance of defensive structures

**Consequence:** Failure in duty affects rank, trust, and community stability.

### 4.3 Escalation Loop (Campaign Progression)
The central narrative arc:

**Phase 1 (Early Game): Honeymoon**
- Town feels peaceful
- NPCs are welcoming
- Legion is defensive, not aggressive
- External conflicts are distant rumors

**Phase 2 (Mid Game): Tension**
- Outsider incidents increase
- False accusations emerge
- Resource scarcity limits civilian options
- Martial exercises become more emphasized
- Internal divisions surface among settlers

**Phase 3 (Late Game): Pressure**
- External violence escalates
- Defensive positions harden
- Legion authority expands
- Moral choices become starkly binary
- Consequences compound

**Phase 4 (End Game): Breaking Point**
- Player choices determine final outcome(s)
- Historical inevitability vs. player agency balance

**Consequence:** Player decisions throughout Phases 1–3 determine which ending paths open.

### 4.4 Social Loop (Relationship System)
NPCs are not quest-dispensers; they are dynamic agents:

**Daily Routines:**
- Each NPC follows a schedule (work, home, meals, meetings)
- Routines vary by season and current events

**Relationships:**
- Player action/inaction affects NPC trust, fear, respect
- Gossip spreads player reputation through the community
- Some NPCs lie or manipulate for their own goals
- Relationships can improve, decay, or become hostile

**Consequence:** Social standing opens/closes dialogue options and mission access.

---

## 5. MOVEMENT & INTERACTION SYSTEMS

### 5.1 First-Person Movement

**Base Movement:**
- Walk (default speed)
- Sprint (faster, exhausts stamina, causes fatigue)
- Crouch (quieter, slower, harder to spot)
- Prone (silent, very slow, difficult to maintain)
- Jump (grounded, realistic arc, stamina cost)

**Momentum System:**
- Movement has weight and inertia (not instantaneous)
- Difficult terrain slows movement naturally
- Stamina depletes with exertion and recovers with rest
- Fatigue affects aim, climbing, and melee accuracy

**Contextual Movement:**
- Vault over low walls/fences
- Lean around corners
- Slide (if injured or moving fast)
- Pushing through crowds (with social/physical consequence)

### 5.2 Climbing & Traversal

**Ladder Climbing:**
- Ladders against buildings
- Wells
- Guard towers
- Slow, requires both hands (vulnerable)

**Fence Vaulting:**
- Low wooden fences (1–2 meters)
- Stone walls (select locations)
- Requires sprint approach and stamina
- Risk of failure if exhausted

**Rooftop Movement:**
- Low residential roofs only
- Unstable surfaces (tiles, wood)
- Scouting advantage but trespassing risk
- High fall danger

**No Parkour:** Movement is grounded, physical, and limited. No wall-running, no superhuman abilities.

### 5.3 Horseback Riding

**Mounting & Control:**
- Find horse (at livery, stables, or from soldiers)
- Mount/dismount (animation, time investment)
- Walk, trot, canter, gallop (speed vs. control trade-off)
- Stamina limit on speed (horse tires)

**Horse Care:**
- Feed horse at stable (costs money)
- Water needs (can use river)
- Brush/grooming improves bonding
- Bonded horses follow commands better
- Injured horse requires veterinary care

**Optional Third-Person Toggle:** Only on horseback; switches perspective for better situational awareness.

**Consequence:** Reliable horses are valuable for patrol routes and escapes.

### 5.4 Interaction System

**Object Interaction:**
- Hold/press interaction button to use doors, pick up items, operate tools
- Animation-based (not instant)
- Can be interrupted

**Environmental Hazards:**
- Climb down ravines carefully (fall damage)
- Cross rivers (swimming stamina drain)
- Fire burns (heat damage over time)
- Weather exposure (cold/heat exhaustion)

**Item Pickup & Inventory:**
- Limited carrying capacity (realistic)
- Weight affects movement speed
- Drop items when full
- Equipment impacts visibility (armor, weapons, tools)

---

## 6. NPC SYSTEMS

### 6.1 NPC Architecture

**Every NPC has:**
- **Identity:** Name, age, occupation, belief
- **Schedule:** Daily routine tied to location, time, and season
- **Relationships:** With other NPCs and the player
- **Memory:** Recalls player actions (helping, harming, ignoring)
- **Motivations:** Wants, fears, secrets
- **Social Network:** Relationships affect gossip and alliance

### 6.2 NPC Behavior

**Daily Routines:**
- Wake at home
- Work shift or personal tasks
- Meal times (communal or private)
- Social time (church, market, gatherings)
- Sleep
- Routines change based on season and world state

**Social Dynamics:**
- NPCs have conversations with each other
- Gossip spreads player information through community
- Some NPCs initiate conflicts with each other
- Social hierarchies affect who listens to whom
- Families and groups stick together

**Response to Player:**
- Recognition of player rank and reputation
- Friendly, neutral, or hostile based on history
- Conditional dialogue (some topics only available if trust > X)
- Risk of lying or false accusations
- Memory of specific player actions

### 6.3 Crowd Behavior

**Crowds as Dynamic Systems:**
- Multiple NPCs in one space create crowd dynamics
- Player actions affect crowd reaction
- Violence triggers panic/flight/retaliation
- Peaceful presence calms crowds
- Rumors spread faster in crowds
- Authority figures command respect

**Escalation & De-escalation:**
- Player words can calm tensions
- Aggression increases hostility exponentially
- Neutral stance allows observation
- Crowd size determines player safety/danger

### 6.4 Example NPC: Militia Officer

| Attribute | Details |
|-----------|---------|
| Name | Captain Isaiah Marks |
| Age | 42 |
| Occupation | Militia officer, blacksmith |
| Belief | Strong faith in Legion's defensive mandate |
| Schedule | Drill grounds (6am–12pm), smithy (1pm–5pm), home (evening) |
| Relationships | Married, has 2 children; allied with other officers |
| Motivations | Protect Nauvoo, maintain order, advance rank |
| Secrets | Doubts Legion's leadership direction |
| Memory of Player | [Varies by choices] |

---

## 7. COMBAT SYSTEM (REALISTIC & CONSTRAINED)

### 7.1 Philosophy

Combat is **dangerous, slow, and consequential:**
- A single musket shot can be lethal
- Injuries persist and worsen untreated
- Most conflicts should be avoided through dialogue or stealth
- Violence has social consequences (witnesses matter)
- Physical exhaustion affects performance
- Heavy gear limits mobility

Violence is **rare early and escalates late:**
- Early game: Conflicts are personal disputes, easily resolved
- Mid game: Tension increases; confrontations become physical
- Late game: Open conflict, militia actions, defensive battles

### 7.2 Weapons

**Muskets:**
- Primary ranged weapon
- Slow fire rate (30–60 sec reload)
- Good stopping power (1–2 shots lethal at close range)
- Low accuracy at distance without training
- Smoke obscures vision
- Misfires (10–20% chance based on maintenance)

**Pistols:**
- Rare, expensive
- Faster than muskets but still slow (10–15 sec reload)
- Useful for self-defense
- Unreliable at range
- Limited ammunition

**Melee Weapons:**
- Clubs, sabers, knives, bayonets
- Silent (important for stealth)
- Stamina-based (tiring to use in prolonged conflict)
- Can disarm or trip opponents
- Grappling possible

**Bayonets:**
- Attached to muskets
- Melee option after shooting
- Reduces reload speed when attached
- Iconic militia weapon

### 7.3 Gunplay Mechanics

**Stance & Accuracy:**
- Standing: Fast aim, worse accuracy
- Crouching: Balanced
- Prone: Slow to aim, best accuracy
- Shooting while moving: Significant accuracy penalty

**Combat Flow:**
1. Aim (must produce "sights" on musket—iron sights or nothing)
2. Hold breath (brief stability window)
3. Fire
4. Smoke blooms (obscures vision)
5. Reload (long animation; vulnerable)

**Fatigue & Performance:**
- Sprinting before shooting: Aim sway increases
- After melee: Stamina depleted, aim unstable
- Hunger/thirst: Physical performance degrades
- Injuries: Dominant arm damage increases aim sway

**Ammunition:**
- Scarce and valuable
- Must be crafted or looted
- Different types (standard, buckshot-like for crowd control)
- Running out of ammo mid-combat is realistic risk

### 7.4 Melee System

**Basic Melee:**
- Light attacks (clubs, fists, unarmed)
- Heavy attacks (sabers, axes)
- Stamina governs number of swings before fatigue

**Grappling:**
- Grab opponent (disables both momentarily)
- Struggle (stamina-based winner thrown/pinned)
- Trip or disarm
- Hold position for allies to strike

**Injury & Damage:**
- Cuts and lacerations (minor bleed, reduced arm function)
- Broken bones (severe mobility reduction)
- Internal injuries (from blunt trauma, gradual health loss)
- Infection risk (untreated wounds worsen)

### 7.5 Injury & Death

**Injury Persistence:**
- Wounds don't heal automatically
- Medical care (herbalism, doctoring) needed
- Some injuries leave scars/permanent effects
- Recovery takes time (sleeping, medicine)

**Death:**
- Death is possible but relatively rare
- Happens quickly if player is overwhelmed
- Death triggers reload from last save
- No resurrection; permadeath in ironman mode

**Pain & Morale:**
- Injuries reduce stamina and aim
- Witnessing death reduces NPC morale
- Fear spreads from one soldier to others
- Panic can break formations

---

## 8. MORAL & CONSEQUENCE SYSTEM

### 8.1 No Morality Meter

Instead of a numerical alignment system, the game tracks:

**Duty vs. Conscience:**
- Orders from superiors vs. personal belief
- Example: "Execute a prisoner" vs. "Spare them"
- Long-term consequences either way

**Obedience vs. Independence:**
- Follow Legion hierarchy strictly
- Or advocate for differing approaches
- Affects your rank and authority

**Peacekeeping vs. Escalation:**
- De-escalate conflicts through dialogue
- Enforce laws strictly
- Use violence to suppress problems
- Each approach has ripple effects

**Community vs. Legion:**
- Prioritize civilian welfare
- Prioritize military objectives
- Navigate conflicting loyalties

### 8.2 Choice Examples

**Scenario: Outsider Provocation**
- **Response A (Restraint):** Overlook the insult; maintain the peace
  - Community sees you as reasonable
  - Outsider feels emboldened to escalate
  - Legion leadership questions your toughness
- **Response B (Controlled Force):** Arrest/detain for questioning
  - Legion approves of authority assertion
  - Outsider community protests false imprisonment
  - Community divided on justice
- **Response C (Escalation):** Violent confrontation
  - Quick resolution but reputation damage
  - Outsiders rally for retaliation
  - Community fears Legion overreach

**Scenario: Food Shortage During Harsh Winter**
- **Option A (Ration Fairly):** Distribute evenly, community suffers equally
  - Morale stays stable; trust maintained
  - Longer crisis duration; resources depleted slower
- **Option B (Favor Soldiers):** Prioritize Legion's strength
  - Soldiers well-equipped; civilians resentful
  - Potential for internal division
  - Faster recovery but trust damaged
- **Option C (Aid Vulnerable):** Give more to sick, elderly, children
  - Soldiers feel abandoned; unity fractures
  - Community sees you as compassionate
  - But some soldiers might mutiny

### 8.3 Reputation & Consequence Tracking

**Track Player Actions:**
- Every significant choice is logged
- NPCs remember and discuss
- Reputation modifiers accumulate

**Consequence is Non-Linear:**
- Early mercy builds trust, enabling later leverage
- Early brutality creates fear, limiting dialogue options
- Inconsistency damages trust across all factions

**Historical Plausibility:**
- Outcomes must align with 1841–1846 Nauvoo history
- But player choices determine *which* historical path unfolds
- Multiple ending branches exist but all converge on dissolution (to varying degrees)

---

## 9. UI & IMMERSION DESIGN

### 9.1 Minimalist HUD Philosophy

**In-Combat:**
- No crosshair (unless iron sights enabled)
- No ammo counter (count manually or check ammunition pouch)
- No health bar (watch for visual/audio cues: breathing, blood screen effect, groaning)
- No minimap (optional compass only; no real-time tracking)

**Out-of-Combat:**
- Stamina indicator (breathing audio, visual bobbing)
- Interaction prompts (context-sensitive labels)
- Quest marker (optional, off by default)
- Objective reminder (periodic), read via journal

**Accessibility:** Players can enable aids (crosshair, HUD elements, map) to accommodate needs. Core experience remains immersive.

### 9.2 Diegetic Elements

**Where possible, UI exists in the world:**
- Journal (physical book, characters reference it)
- Maps (hold and read written maps; not a telepathic overlay)
- Orders (received verbally or written by commanding officer)
- Objectives (inscribed in your journal)

**Audio Cues:**
- Footsteps on different surfaces (wood, dirt, stone)
- Breathing during exertion
- Musket mechanics (loading sounds, misfires)
- Crowd murmurs
- Alarm bells for alerts
- Voices calling orders

### 9.3 Menus & Navigation

**Main Menu:**
- Period-appropriate typography (serif fonts, muted colors)
- No modern UI chrome
- Simple: New Game / Load / Settings / Quit

**In-Game Menus:**
- Journal (quests, notes, character relationships)
- Inventory (physical representation; weight matters)
- Map (physical item; must be in possession to use)
- Settings (accessibility, graphics, audio)

**Pause Menu:**
- Optional (game can be paused or continues in real-time)
- Clean, minimal design
- No modern aesthetic

### 9.4 Text & Dialogue

**Dialogue System:**
- First-person perspective: Player hears themselves think, doesn't see own face
- Choice-based branching
- Dialogue outcomes depend on reputation, rank, previous choices
- Some dialogue locked based on trust/fear levels

**Dialogue Types:**
- **Duty-based:** Orders, assignments, drills
- **Social:** Inquiries, small talk, relationship building
- **Tense:** Accusations, accusations, arguments
- **Intimate:** Confessions, secrets, vulnerable moments

**Journal Entries:**
- Player can read previous notes
- NPC relationships documented
- Quests tracked via written notes (not a quest log)

### 9.5 Audio Design

**Music:**
- Sparse and ambient
- Somber orchestral tone
- Tension builds gradually as conflict escalates
- Silence is used meaningfully (absence of music = unease)

**Sound Effects:**
- Footsteps vary by surface (wooden floorboards, dirt, cobblestone)
- Musket cocking, pouring powder, ramming ball
- Reload mechanics audible (reload must be heard, not seen, for full reload time)
- Crowd ambience (distant conversations, children playing)
- Weather (rain on roofs, wind through buildings)
- Animals (horses, chickens, cattle)

**Voice Acting:**
- NPCs speak with period appropriate dialect (subtle, not caricature)
- Player voiceless (first-person perspective)
- Crowd voices (generic murmurs, distinguishable)
- Radio silence treated as meaningful (tension)

---

## 10. PROGRESSION & CONTENT

### 10.1 Campaign Structure

**Acts:**
1. **Arrival & Acclimation (5–8 hours)**
   - Learn the town, join Legion
   - Establish initial relationships
   - First drills and assignments
   - Tone: Hopeful, exploratory

2. **Deepening Involvement (10–15 hours)**
   - Rank advancement
   - Escalating assignments
   - First conflicts with outsiders
   - Internal community divisions emerge
   - Tone: Tension building

3. **Crisis & Decision (8–12 hours)**
   - Open conflict scenarios
   - Major moral choices
   - Player decisions determine ending branch
   - Tone: Pressure, consequence

4. **Culmination (3–5 hours)**
   - Multiple possible endings
   - Resolution based on player choices
   - Historical inevitability balanced with agency

### 10.2 Initial Build Target (Alpha/MVP)

**One Fully Playable District:**
- Central Nauvoo (meeting house, market, residences, workshops, militia grounds)
- ~15 named NPCs with full schedules
- 3–5 conflict chains leading to different resolutions
- Full day/night cycle
- 2-3 seasonal changes

**Systems to Include:**
- Daily routine loop
- Legion drill system (training, marching)
- One major escalation scenario with multiple outcomes
- One patrol mission with waypoints
- One moral decision with lasting consequence
- Reputation system (simplified but functional)
- Combat with muskets and melee
- Injury system

**Estimated Time:** 4–6 hours of singular playthrough

### 10.3 Future Expansions

**Additional Districts:**
- Riverfront (docks, militia water patrol)
- Outlying farmsteads
- Disputed frontier areas

**Extended Conflict Chains:**
- 3–5 major scenario branches
- Dozens of small NPC storylines
- Multiple historical parallels (based on actual Nauvoo events)

**Deeper Systems:**
- Marriage/family (major life choice)
- Children/dependents
- Religious factions (internal LDS disagreements)
- External pressure (neighbor militias, government authorities)

---

## 11. TECHNICAL FOUNDATION

### 11.1 Engine Selection

**Recommended: Unreal Engine 5**
- Strong first-person tooling
- High-fidelity environmental detail
- NPC scheduling via Blueprints (initially) or custom systems
- Mature save/load systems
- Good performance optimization

**Alternative: Unity HDRP**
- More lightweight option
- Easier for smaller teams
- Less overhead for CPU-intensive systems

**Why Not:**
- Godot: Limited first-person tool ecosystem
- Proprietary: Not viable for indie project constraints

### 11.2 Core Systems (Architecture)

**1. Save/Load System**
- Save player state (position, inventory, rank, health)
- Save world state (NPC relationships, building damage, resources)
- Save time state (current time, season, day counter)
- Permadeath option (ironman mode)

**2. NPC System**
- Scheduling engine (location, activity, availability per hour)
- Reputation tracking (per-NPC, relationship, trust, fear)
- Dialogue system (branching, conditional on reputation)
- Spatial awareness (NPCs know where player is, respond accordingly)

**3. Reputation System**
- Legion reputation (loyalty, obedience, brutality, competence)
- Community reputation (trust, respect, fear)
- Outsider perception (threat, prejudice, value)
- Tracks cumulative actions, not meter-based

**4. Combat System**
- Weapon mechanics (muskets, pistols, melee)
- Stamina/fatigue (affects action availability)
- Damage & injury (persistent, requires treatment)
- Ammunition (scarce, must be managed)

**5. Time System**
- 24-hour day cycle
- Seasonal calendar (spring, summer, fall, winter)
- Event scheduling (drills, meetings, incidents tied to date/time)
- Time passage affects NPC availability and world state

### 11.3 Performance Targets

- **Resolution:** 1440p target (1080p minimum)
- **Frame Rate:** 60 FPS (lock or uncapped)
- **Platforms:** Windows PC (primary), Linux, Mac (secondary)
- **System Requirements:** Mid-tier PC (RTX 2070 equivalent or better for high settings)
- **No requirements for:** Ray tracing, DLSS/FSR (nice-to-have, not required)

### 11.4 Data & Content

**World Data:**
- Map layout (buildings, streets, landmarks)
- NPC definitions (name, job, schedule, relationships)
- Item definitions (weapons, tools, food, etc.)
- Dialogue trees (branching conversations)

**Narrative Data:**
- Quest/scenario definitions
- Dialogue text and voice lines
- Journal entries and world lore

### 11.5 Team & Scope

**Estimated Team:**
- 1 Gameplay Programmer
- 1 Systems Programmer
- 1 Dialogue/Narrative Designer
- 1 Level Designer
- 1 Audio Designer
- 1–2 Artists (modeling, materials, VFX)
- 1 Voice Director / Actor
- 1 Project Manager

**Development Timeline:**
- Prototype: 3 months
- Alpha (one district): 9 months
- Beta (content expansion, polish): 6 months
- Gold: 3 months
- **Total: ~21 months**

---

## 12. TONE & RESPECT

### 12.1 Historical Responsibility

This game respects Nauvoo's complexity:
- No parody or caricature
- No modern political messaging (anachronistic)
- Religious belief portrayed with seriousness
- Community devotion shown as genuine
- Conflict grounded in historical fact

### 12.2 Sensitivity & Representation

**Faith & Belief:**
- LDS belief portrayed respectfully
- Non-believers also portrayed fairly
- Religious conflict is documented historical fact
- No mockery of faith itself

**Violence & Conflict:**
- Violence shown as devastating, not glorified
- Death has weight
- Conflict driven by historical pressure, not individual evil

**Gender & Agency:**
- Women are visible in town (not just background)
- Women can be NPCs with agency and storylines
- Historically appropriate role limitations, but not erased from narrative

### 12.3 Educational Value

Without being didactic, the game teaches:
- What frontier life felt like
- How a community forms and fractures
- The pressure of conflicting loyalties
- How ordinary people experience historical crisis

---

## 13. DELIVERABLES & SUCCESS METRICS

### 13.1 MVP Criteria (Vertical Slice)

✓ One fully playable district (Central Nauvoo)  
✓ 15+ named NPCs with daily schedules  
✓ Full day/night cycle (30 min real-time = 1 game day)  
✓ Drill system (training, marching formation)  
✓ One escalating conflict chain (3 decision points)  
✓ Musket combat (training & one combat scenario)  
✓ Patrol mission (with waypoints, NPC interaction)  
✓ One moral decision with lasting consequence  
✓ Reputation system (Legion, community, personal)  
✓ Save/load system (world state persistence)  
✓ Base audio design (footsteps, voices, ambient)  

### 13.2 Quality Metrics

- **Immersion:** Player forgets they're in a game (no HUD intrusion)
- **Consequence:** Every major choice visibly affects world state
- **NPCs Feel Alive:** Schedules are maintained; gossip spreads plausibly
- **Performance:** Consistent 60 FPS without stutters
- **Accessibility:** Core gameplay playable with UI aids enabled

### 13.3 Scope Boundaries

**In Scope:**
- One district
- 15–20 NPCs
- 3–5 conflict branches
- 60+ hours of dialogue
- Muskets, melee, basic injuries

**Out of Scope (Future):**
- Multiple districts
- Horseback combat
- Relationship marriages
- Religious factions
- Exterior armies
- DLC/post-launch content

---

## 14. REFERENCES & INSPIRATION

**Historical Sources:**
- "The Nauvoo Legion" by John D. Lee
- "The LDS Church & Its Civil Defense, 1838–1846" (academic papers)
- Contemporary accounts (journals, letters, period texts)

**Game Design Inspiration:**
- **Red Dead Redemption 2:** First-person immersion, animation weight, NPC worlds
- **Disco Elysium:** Choice consequence, dialogue trees, internal conflict
- **Fallout: New Vegas:** Faction reputation, branching ending outcomes
- **Dwarf Fortress:** NPC agency and simulation depth
- **Kingdom Come: Deliverance:** Historical grounding, permadeath, limited UI

**Tone Inspiration:**
- **This War of Mine:** Moral complexity, no heroes
- **Spec Ops: The Line:** Consequence of violence
- **Firewatch:** Atmospheric immersion, dialogue-heavy

---

## 15. CONCLUSION

**Nauvoo: Legion** aims to create a historically grounded, narrative-driven first-person experience that makes the player feel what it was like to live, serve, and struggle in a community under pressure. 

Rather than glorifying conflict, the game explores the **weight of ordinary choices** in extraordinary circumstances. Through immersive systems, meaningful NPCs, and consequence-laden decisions, the player experiences Nauvoo's defining historical moment not as observer, but as participant.

**Core promise:** You are not the hero; you are a person caught between duty, conscience, and community.

---

**Document Version:** 1.0  
**Last Updated:** February 5, 2026  
**Status:** Ready for Development
