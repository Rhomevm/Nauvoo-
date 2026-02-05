# CORE GAMEPLAY SYSTEMS DESIGN

## 1. Daily Life Loop

### Overview
The Daily Life loop is the foundation of the player experience. It encompasses all non-combat, non-crisis activities that make the world feel lived-in and real.

### Loop Phases

**Morning Routine (6:00 AM – 9:00 AM)**
1. Player wakes at assigned home/barracks
2. NPC greeting (neighbor, roommate, or officer)
3. Player can:
   - Eat breakfast (restores stamina)
   - Check message board for assignments
   - Interact with nearest NPCs (gossip, small quests)
   - Prepare equipment
4. Optional: Attend morning drill or work assignment

**Work Phase (9:00 AM – 12:00 PM)**
1. Player selects from available activities:
   - **Militia**: Join training drill (reputation gain)
   - **Trade Work**: Blacksmithing, carpentry, farming (earn currency)
   - **Civic Work**: Help with construction, maintenance (relationship gain)
   - **Personal**: Rest, practice, explore
2. Activities grant:
   - Reputation (faction-specific)
   - Skills (slow progression)
   - Currency (work-based)
   - Relationships (helping NPCs)

**Afternoon Phase (12:00 PM – 5:00 PM)**
1. Lunch time (optional eating, social time)
2. Continuation of work phase or new activity selection
3. NPCs have routine interactions (market shopping, visiting friends)
4. Rumors spread during this time
5. Potential small conflicts or events (not major plot)

**Evening Phase (5:00 PM – 10:00 PM)**
1. Guard duty rotation (optional for Legion members)
   - Walk patrol routes
   - Interact with other guards
   - Detect unusual activity
   - Report to commanding officer
2. Dinner time (communal or private)
3. Social interaction time
   - Visit other NPCs at home
   - Attend meetings (civilian gatherings, Legion discussions)
   - Gossip & news gathering

**Night Phase (10:00 PM – 6:00 AM)**
1. Player must rest (can be interrupted)
2. Sleep at designated location (home or barracks)
3. Injuries heal slowly (rest is critical for recovery)
4. Reputation decays if daily objectives not met
5. Next day scheduled

### Consequence System (Daily)
- **Skip work**: -reputation with employer, lose currency
- **Skip guard duty**: -Legion reputation, potential demerit
- **Help NPCs**: +community reputation, gain access to private dialogue
- **Gossip spreading**: Reputation changes ripple through community
- **Rumor manipulation**: Can spread false information (risky)

### Optional Side Activities
- **Travel**: Leave town for trade, scouting, personal errands
- **Training**: Musket practice, melee drills (improve combat)
- **Crafting**: Create ammunition, repair equipment
- **Teaching/Learning**: Learn skills from NPCs, teach others
- **Religious**: Attend meetings (LDS cultural immersion)

---

## 2. Legion Duty Loop

### Overview
Structured military responsibilities that define the player's role and opportunities. These are assigned or optional but incentivized.

### Assignment Types

**Drills (Repeating)**
- **Formation Marching**: 30 minutes of group movement
  - Tests coordination
  - Builds cohesion (reputation)
  - Commanded by officers
- **Musket Training**: 1 hour of target shooting
  - Improves accuracy skill
  - Generates marksmanship score
  - Officer evaluates performance
- **Hand-to-Hand Combat**: 45 minutes of wrestling/grappling practice
  - Improves melee skill
  - Can result in exhaustion
  - Relationship building with sparring partners
- **Mounted Drills**: Cavalry movement (if player has horse)
  - Horse bonding
  - Tactical maneuvers

**Assigned Patrols**
- **Gate Watch**: Stationary position at town entrance
  - Interact with arrivals (traders, travelers, suspicious people)
  - Report findings to commanding officer
  - Duration: 2–4 hours
- **Perimeter Patrol**: Walk boundary of town
  - Detect threats/intruders
  - Maintain defensive readiness
  - Interact with other guards
- **Intelligence Patrol**: Scout outside town
  - Gather information about outsider activity
  - Report back with findings
  - Risk of conflict

**Escort Missions**
- **Civilian Escort**: Guard townspeople traveling outside town
  - VIP treatment of civilians
  - Relationship building
  - Risk of attack (triggers combat)
- **Supply Run**: Accompany supply transport
  - Protect valuable cargo
  - Community gratitude if successful
- **Leadership Escort**: Guard officer or leadership
  - High trust gain with officer
  - Exposure to leadership decisions

**Special Assignments**
- **Investigation**: Look into reported problems
  - Talk to witnesses
  - Gather evidence
  - Report findings
- **Repair/Maintenance**: Fortify defensive positions
  - Work with other soldiers
  - Physical labor
- **Ceremony**: Participate in parades, celebrations
  - Build community morale
  - Relationship building

### Duty Performance Metrics
- **Attendance**: Did you show up?
- **Performance**: How well did you do?
- **Attitude**: Did you follow orders/grumble?
- **Initiative**: Did you go above and beyond?

**Scoring:**
- Excellent: +25 reputation
- Good: +15 reputation
- Satisfactory: +5 reputation
- Poor: -10 reputation
- Absent: -30 reputation + potential demerit

### Promotion System
Rank advancement based on cumulative reputation:

| Rank | Legion Rep Required | Benefits |
|------|---------------------|----------|
| Recruit | 0 | Basic duties, low authority |
| Legionnaire | +30 | Trusted with patrols, mentor status |
| Senior Legionnaire | +60 | Lead small groups, advanced training |
| Sergeant | +85 | Command authority, strategy input |
| Captain | +100 | Officer rank, make tactical decisions |

**Consequences of promotion:**
- Higher expectations from superiors
- Increased authority over other soldiers
- Access to restricted information
- Responsibility for subordinate actions
- Target for blame if things go wrong

---

## 3. Escalation Loop (Campaign Progression)

### Overview
The master narrative arc that ties all systems together. Player choices throughout Phases 1–3 determine the outcome.

### Phase 1: Arrival & Hope (5–8 hours)

**Tone:** Peaceful, welcoming, hopeful

**Key Events:**
1. **Arrival** (Tutorial)
   - Meet commanding officer
   - Tour of town
   - Assigned to Legion
   - First NPC interactions

2. **Integration**
   - Take first drill
   - Make initial relationships
   - Learn daily routines
   - Receive first simple assignment

3. **Community Life**
   - Attend town meeting
   - Help locals with tasks
   - Participate in religious activities
   - Establish routine

**World State:**
- Town feels peaceful
- NPCs are friendly and open
- Legion is defensive, not aggressive
- No external threats visible
- Economy stable, resources adequate

**Decision Points:** None (tutorial phase)

**Escalation Level:** 0/10

---

### Phase 2: Deepening Involvement & Tension (10–15 hours)

**Tone:** Stability eroding, tensions rising, first cracks

**Key Events:**

1. **First Outsider Incident (Week 2)**
   - Outsiders test town boundary
   - Could be traders, could be surveying
   - Player witnesses or enforces response
   - First dialogue choice:
     - **Welcoming:** Talk to outsiders professionally
     - **Defensive:** Order them to leave
     - **Aggressive:** Threaten/intimidate them
   - Outcome spreads as rumor

2. **Internal Disagreement (Week 3)**
   - Leadership debates defensive strategy
   - Some want aggressive action; others want pacifism
   - Player overhears discussion
   - Division of opinion becomes visible

3. **First False Accusation (Week 4)**
   - Community member accused of spying/disloyalty
   - Presented as fact by officer
   - Player must decide:
     - **Believe:** Help imprison/interrogate
     - **Doubt:** Question evidence
     - **Defend:** Actively shield the accused
   - Consequence: Reputation hits based on choice

4. **Community Strain (Week 5)**
   - Food shortage (minor; manageable)
   - Militia takes priority rations
   - Civilian discontent visible
   - Player can advocate for fairness or enforce order

5. **Growing Fear (Week 6)**
   - Rumors of outsider militia forming
   - Gates fortified further
   - Drills increase in intensity
   - Player notices change in NPC behavior

**World State:**
- External hostility increases
- Community divisions deepen
- Militia authority expands
- Resource strain visible
- Fear spreads among civilians

**Escalation Level:** 3/10

**Player Choices Determine:**
- Community trust in you
- Legion's faith in you
- Trust between community and Legion
- Which NPCs are allies vs. enemies
- Difficulty of later negotiations

---

### Phase 3: Crisis & Decision (8–12 hours)

**Tone:** Danger imminent, choices have weight, consequences unavoidable

**Key Events:**

1. **Major Outsider Provocation (Week 8)**
   - Outsider attack on town outpost
   - Several soldiers/civilians killed
   - Undeniable evidence of external threat
   - **Decision Point A: Response**
     - **Retaliate:** Immediate military action
     - **Investigate:** Determine actual threat level
     - **Defend:** Hunker down and prepare
   - Outcome cascades: Reputation changes, NPC positions solidify

2. **Authority Conflict (Week 9)**
   - Leadership gives order player considers unjust
   - Example: Execute prisoner, imprison innocent, conscript children
   - **Decision Point B: Obedience**
     - **Obey:** Follow order (Legion +50, Community -30)
     - **Refuse:** Risk consequences (Legion -40, Community +30)
     - **Compromise:** Find alternative (both parties -10)
   - NPC reactions based on personality & relationships

3. **Community Uprising (Week 10)**
   - Civilians demand change
   - Militia given order to suppress protest
   - **Decision Point C: Enforcement**
     - **Enforce Harshly:** Arrest leaders, use force
     - **Enforce Fairly:** Disperse without violence
     - **Join Protest:** Side with community
     - **Refuse Order:** Stand aside

4. **Personal Test (Week 11)**
   - Friend/ally arrested for disloyalty
   - You're asked to testify against them
   - **Decision Point D: Loyalty**
     - **Testify:** Loyalty to system (Legion +30, Personal -40)
     - **Refuse:** Loyalty to friend (Legion -40, Community +30)
     - **Lie:** False testimony (complicated consequences)

5. **Breaking Point (Week 12)**
   - External force threatens imminent attack
   - Community fracturing between militant and peaceful factions
   - Leadership demands everyone choose sides
   - **Decision Point E: Allegiance**
     - **Stay with Legion:** Continue as soldier
     - **Leave with Community:** Abandon military post
     - **Attempt Negotiation:** Try to prevent violence

**World State:**
- Open conflict possible
- Leadership authority contested
- NPC positions locked in (mostly)
- Reputation tracks determine available options
- Previous choices matter enormously

**Escalation Level:** 8/10

**Branching Determined By:**
- Total Legion vs. Community reputation
- Consistency across decisions
- Key choice outcomes (especially Decision Point B & E)
- NPC alliance states

---

### Phase 4: Culmination & Resolution (3–5 hours)

**Tone:** Inevitable but shaped by player actions

**Final Scenario:**
Based on previous phases, player faces one of several final scenarios:

**Scenario A: Negotiation Path** (if both legions high)
- Outsiders and Legion negotiate
- Player chosen as representative
- Outcome depends on dialogue choices
- Can achieve peaceful resolution (rare)

**Scenario B: Conflict Path** (if Legion high, Community low)
- Military action against external threat
- Player leads/participates in final battle
- Community may or may not support
- Victory is hollow if community is against you

**Scenario C: Community Defense Path** (if Community high, Legion low)
- Defense without military hierarchy
- Civilian-organized resistance
- Direct defense of homes/families
- More personal, less coordinated

**Scenario D: Trapped Path** (if both low)
- No allies
- Events unfold regardless
- Survival focused
- Limited agency

**Final Decision:**
- Witness the "end" of Nauvoo (historical inevitability)
- Your reputation determines who survives, who leaves, who dies
- Final judgement from community/Legion on your actions
- Epilogue showing long-term consequences

**Escalation Level:** 10/10

---

## 4. Social Loop (Relationship Dynamics)

### Overview
NPCs are not static quest-dispensers. They evolve, change opinions, and directly influence each other.

### NPC Relationship States

**First Meeting:**
- NPC neutral toward player
- Some initial prejudice based on reputation (Legion member = potential threat to outsider)
- Cautious but open

**Repeated Interaction:**
- Relationship gradually builds based on treatment
- Actions speak louder than words
- Reputation feedback reinforces or contradicts player's public persona

**Conversation Triggers:**
- Player can initiate talk at appropriate times
- Dialogue options limited by relationship
- Some topics locked until trust achieved
- NPCs may lie if trust is low

**Gossip Integration:**
- Rumors heard from NPCs affect player reputation
- NPCs judge player based on what they hear
- Can counteract rumors with personal relationships

**Alliance Formation:**
- Strong relationships (trust > +40) create allies
- Allies help in conflicts
- Betraying ally has severe consequences

---

## 5. Consequence Spreading (System Integration)

### Cascade Mechanics

**When Player Takes Action:**
1. **Witnesses** see it directly (highest impact)
2. **Direct gossip** spreads to people they know
3. **Secondary gossip** reaches people once removed
4. **Community opinion** forms over time
5. **Official response** (if action was illegal/significant)

**Example:**
- Player helps widow with repairs (10 witnesses)
- Widow tells family (5 more people)
- Family tells church congregation (20+ people)
- Community reputation increases
- Elderly NPCs remember and trust you
- Future dialogue opens up

**Multiplier Effects:**
- Reputation with one faction affects perception by others
- Officer's trust gives access to military information
- Community trust gives access to civilian secrets
- Actions on one system affect other systems

---

## Combat Integration

### When Combat Happens
Combat isn't a separate system; it's a consequence of escalation.

**Escalation → Conflict → Combat:**
1. **Rising Tension** (Phase 2): Social conflict, accusations, disagreement
2. **Breakdown** (Phase 3): Peaceful resolution impossible
3. **Violence** (unavoidable): Combat forced
4. **Resolution** (immediate): One side wins, flees, or surrenders

**Avoiding Combat:**
- Good reputation opens dialogue
- Showing restraint de-escalates
- Showing weakness invites aggression
- Creating alliance deters attack

**Combat Impact:**
- Death of NPC affects community
- Violence witnessed changes relationships
- Injuries persistent and meaningful
- Atrocities remembered forever

---

## Implementation Notes

- All loops are interconnected
- Skipping duties still has consequences
- No "right" path; all lead to historical resolution
- Replayability via different choices leading to different content
- Core events always occur; response varies

---

**Status:** Complete system documentation  
**Next Phase:** Prototyping & implementation
