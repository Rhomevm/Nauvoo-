# REPUTATION & MORAL SYSTEM

## Philosophy

There is **no single morality meter**. Instead, the player's choices create consequences through multiple reputation tracks and emerging world state.

The system tracks **what you do**, not **who you are**. Your actions ripple through the community, and NPCs respond based on their own values and memories.

## Four Reputation Tracks

### 1. Legion Reputation
How soldiers and officers perceive your dedication to duty.

**Range:** -100 (deserter/traitor) to +100 (exemplary soldier)

**Factors:**
- Attending drills (yes/no)
- Following orders (yes/no, or reluctantly)
- Battle performance (courage, restraint, brutality)
- Rank advancement (if applicable)
- Enforcement of orders on civilians
- Whistle-blowing vs. loyalty to officers

**NPC Interactions:**
- Officers address you more formally (high reputation) or with disdain (low)
- Soldiers follow your lead in conflict (if experienced)
- Promotions/demotions based on reputation threshold
- Access to restricted militia areas blocked if too low

**Historical Consequence:**
- High: You're entrusted with sensitive intelligence, officer roles
- Low: You're sidelined, given guard duties, passed over for promotion

### 2. Community Reputation
How civilians perceive your treatment of them.

**Range:** -100 (feared threat) to +100 (community hero)

**Factors:**
- Helping with tasks (repairs, food, protection)
- Enforcing Legion rules on civilians (harshly vs. mercifully)
- Prioritizing civilian welfare vs. military objectives
- Response to falsely accused community members
- Defending community from external threats
- Transparency in decisions

**NPC Interactions:**
- Civilians greet you warmly (high) or avoid you (low)
- They offer you discounts or refuse service
- Doors are opened to you or barred
- Family connections become available (social access)
- Rumors about you spread differently

**Historical Consequence:**
- High: Community defends you if accused, supports your leadership
- Low: Community may report you to authorities, withhold aid

### 3. Outsider Perception
How neighboring communities and external forces view you.

**Range:** -100 (active threat) to +100 (trusted liaison)

**Factors:**
- Aggressive vs. diplomatic interactions with outsiders
- Violation of their communities' borders
- Treatment of outsider prisoners/detainees
- Reputation for brutality (spreads among outsiders)
- Attempts to mediate disputes
- Legion's overall actions (your part in them)

**NPC Interactions:**
- Outsiders approach you openly (positive) or hostile (negative)
- If you encounter outsider communities, your reception varies
- Negotiation difficulty increases/decreases
- Risk of ambush or attack changes

**Historical Consequence:**
- High: Potential for peaceful negotiation, trade, movement through territory
- Low: Outsiders escalate hostility, cut off trade, restrict movement

### 4. Personal Integrity (Internal)
Not a reputation with others, but your consistency with your own stated values.

**Range:** -50 (completely contradictory) to +50 (aligned with choices)

**Factors:**
- Consistency between choices and stated values
- Hypocrisy (saying one thing, doing another)
- Moral courage (standing by unpopular principles)
- Compromise (accepting pragmatic vs. idealistic trade-offs)

**Effects:**
- Does NOT change how NPCs interact with you directly
- Affects dialogue availability (some personal conversations locked if inconsistent)
- Influences certain NPC trust gains (some care about your integrity)
- Personal agency in decision-making (you feel coherent or fractured)

## Choice Categories

### Duty vs. Conscience
**Example Scenarios:**
- **Order:** Execute a prisoner of war
  - **Duty Path:** Follow order (Legion +30, but Community -40, Integrity ?)
  - **Conscience Path:** Refuse or secretly release (Community +30, Legion -20, Integrity +)
  - **Compromise:** Detain but spare (Legion +5, Community +10, Integrity ?)

- **Order:** Confiscate food from a starving family
  - **Duty Path:** Full enforcement (Legion +20, Community -50)
  - **Conscience Path:** Turn a blind eye (Legion -15, Community +40)
  - **Compromise:** Take small amount, leave some (Legion +5, Community -5)

### Obedience vs. Independence
**Example Scenarios:**
- **Situation:** Officer orders you to punish a protester harshly
  - **Obey:** Execute order (Legion +25, Community -35)
  - **Disobey:** Refuse openly (Legion -40, Community +20)
  - **Negotiate:** "Sir, a lighter punishment will achieve the same result" (Legion +10, Community +5)

- **Situation:** You disagree with military leadership's strategy
  - **Silent Compliance:** Say nothing (Legion +10, but slow reputation decay if strategy fails)
  - **Reporting Up:** Appeal to higher authority (Legion +0, risk of being labeled troublemaker)
  - **Speak Privately:** Confide doubts to trusted officer (Legion +5 if they agree, -5 if dismissed)

### Peacekeeping vs. Escalation
**Example Scenarios:**
- **Situation:** Outsider insults the Legion publicly
  - **Restraint:** Ignore it, walk away (Outsider +5, Community +10, Legion -10)
  - **Controlled Response:** Verbal correction, no violence (Outsider -5, Legion +10, Community +0)
  - **Escalation:** Physical confrontation (Outsider -25, Legion +15, Community -10)

- **Situation:** A fight breaks out in the market
  - **De-escalation:** Talk down the combatants (Community +20, Legion +0)
  - **Enforcement:** Arrest both parties (Legion +10, Community +0)
  - **Intervention:** Side with one party against the other (Legion varies, Community -15)

### Community vs. Legion
**Example Scenarios:**
- **Situation:** A resource shortage; Legion gets priority, or civilians?
  - **Legion Priority:** Soldiers fed first (Legion +30, Community -40)
  - **Community Priority:** Distribute evenly or favor vulnerable (Community +30, Legion -20)
  - **Compromise:** Give soldiers extra but ensure kids/elderly don't starve (Legion +10, Community +15)

- **Situation:** A community member is accused of spying for outsiders
  - **Believe Accusation:** Help imprison them (Legion +40, Community -35)
  - **Defend Accused:** Demand evidence (Community +25, Legion -15)
  - **Investigate Fairly:** Look for actual proof (Legion +10, Community +15)

## Reputation Modifiers (Action Lookup Table)

| Action | Legion | Community | Outsider | Gossip Spread | NPC Anger |
|--------|--------|-----------|----------|---------------|-----------|
| Help injured NPC | 0 | +30 | 0 | High | None |
| Beat prisoner | +20 | -50 | -30 | Very High | Victims remember |
| Prevent a fight | +5 | +25 | +15 | Medium | None |
| Execute sentenced criminal | +30 | -10 | 0 | High | Victim's family |
| Secretly spare condemned | -40 | +50 | +5 | Very High | Superiors furious |
| Enforce curfew fairly | +15 | +10 | 0 | Low | None if fair |
| Enforce curfew harshly | +25 | -30 | -20 | Medium | Many angry |
| Donate supplies to needy | 0 | +40 | +10 | High | None |
| Steal from community | -30 | -50 | 0 | Very High | Everyone angry |
| Warn outsider of patrol | -50 | -20 | +40 | Massive | Officers furious |
| Stand down unfair order | -15 | +30 | +10 | High | Officers suspicious |
| Protect civilian from Legion | -25 | +50 | +20 | High | Officers angry |
| Participate in looting | +10 | -40 | -20 | Very High | Victims furious |
| Report fellow soldier misconduct | +40 | +50 | +30 | Very High | That soldier betrayed |
| Cover for fellow soldier's crime | +5 | -30 | -10 | Medium | Victims angry |
| Speak against government | -30 | +20 | +30 | Very High | Leaders suspicious |

## Dialogue Gate System

Certain dialogue options are locked based on reputation thresholds:

```
DialogueOption {
  text: string
  legion_requirement: int (default: any)
  community_requirement: int (default: any)
  outsider_requirement: int (default: any)
  integrity_requirement: bool (do you need to be consistent?)
  previously_chosen_requirement: DialogueOption[] (must have chosen this before)
}
```

**Example:**
- *"I think we should negotiate with the outsiders"* → Requires Outsider perception > +20 and Legion reputation > -10 (can't be a deserter AND try to negotiate)
- *"I'll help you hide from the Legion"* → Requires Community > +40 and personal trust with that NPC > +60
- *"Execute this order"* → Only available to Legion rank >= 2, or Legion reputation > +40

## Reputation Decay

Reputation doesn't stay static. Absence of action decays it:

```
decay_rate = base_decay * (time_since_last_relevant_action)

Example:
- Legion reputation: -10 per week if you miss drills
- Community reputation: -5 per week if you don't interact with townspeople
- Outsider perception: -3 per month (slowly forgets about you)
- Personal integrity: No decay (it's your choice to maintain or abandon values)
```

## World State Consequences

Your reputation determines what happens in the world:

### Early Game (Low Conflict)
- If Community reputation is low and Legion reputation is high → Some civilians avoid Legion (you included)
- If Community reputation is high → Civilians offer tips, shelter, supplies
- If Outsider perception is negative → Fewer outsider traders visit

### Mid Game (Rising Tension)
- If Legion reputation high, Community low → You may be assigned to suppress civilian protest
- If both reputations high → You must choose sides in a conflict
- If Outsider perception negative → Outsiders increase attacks
- If Outsider perception positive → Outsiders may approach you to negotiate

### Late Game (Crisis)
- Community reputation determines if community accepts or rejects military leadership
- Legion reputation determines if you're trusted with final decisions
- Your consistency (integrity) determines if NPCs believe promises you make

## Historical Outcomes

The game has multiple ending branches, determined by cumulative reputation:

```
Ending Branch Determination:

Final Legion Reputation + Final Community Reputation → Outcome

(+100 to +60) + (+100 to +60) = "Respected on Both Sides"
  - Most NPCs support peaceful resolution
  - You have influence to negotiate
  - Historical inevitability still occurs, but on better terms

(+30 to -30) + (+30 to -30) = "Caught in the Middle"
  - You lack influence; events overtake you
  - Outcome largely predetermined
  - Limited agency in final confrontation

(-60 to -100) + (-60 to -100) = "Outcast & Blamed"
  - You're blamed for community collapse
  - Limited options in final scenario
  - Forced to witness consequences of your actions

(High Legion, Low Community) = "Enforcer"
  - Tasked with suppressing civilian dissent
  - Final choice: obey or defect

(High Community, Low Legion) = "Traitor"
  - Viewed as disloyal by Legion officers
  - May be arrested or court-martialed
  - Final choice: defend yourself or submit
```

## Moral Complexity (Non-Binary)

The system avoids "good vs. evil" by presenting **no option that is purely good**:

**Example Scenario: Defending the Town**
- **Option A:** Aggressive militia action (protects town, traumatizes civilians, escalates outsider anger)
- **Option B:** Negotiation (avoids violence, risks appearing weak, outsiders may advance anyway)
- **Option C:** Fortification & defense (moderate outcome, resource drain, preparation time)
- **Option D:** Peaceful coexistence (idealistic, many won't support it, external pressure mounts)

Each choice has real costs. There's no "correct" answer—only trade-offs.

## Implementation Structure (Code Design)

```python
class ReputationSystem:
    def __init__(self):
        self.legion_rep = 0
        self.community_rep = 0
        self.outsider_rep = 0
        self.personal_integrity = 0
        self.action_history = []
        self.npc_memory = {}  # NPC_ID -> ActionMemory

    def record_action(self, action: PlayerAction):
        modifier = ACTION_LOOKUP_TABLE[action.type]
        self.legion_rep += modifier.legion
        self.community_rep += modifier.community
        self.outsider_rep += modifier.outsider
        
        # Notify NPCs who witnessed or will hear about this
        for affected_npc in action.witnesses:
            self.npc_memory[affected_npc].add(action)
        
        # Spread gossip
        self.gossip_system.spread_rumor(action, modifier.spread_rate)
        
        # Store in history
        self.action_history.append(action)

    def get_dialogue_availability(self, npc: NPC, dialogue_option: DialogueOption) -> bool:
        # Check all requirements
        if dialogue_option.legion_requirement and self.legion_rep < dialogue_option.legion_requirement:
            return False
        if dialogue_option.npc_trust_requirement and dialogue_option.npc_rep < npc.relationship_with_player.trust:
            return False
        # ... more checks
        return True

    def get_ending_branch(self) -> str:
        legion_score = self.legion_rep
        community_score = self.community_rep
        return ENDING_DETERMINATION[(legion_score, community_score)]

    def apply_decay(self, days_elapsed: int):
        # Apply time-based decay
        self.legion_rep = max(-100, self.legion_rep - (days_elapsed * 10))
        self.community_rep = max(-100, self.community_rep - (days_elapsed * 5))
        # Only decay if no relevant action performed
```

---

**Reputation System Status:** Ready for development  
**Complexity:** Medium-High (integration with NPC dialogue, world events)  
**Testing Required:** Extensive playtesting to ensure balance and variety
