# COMBAT SYSTEM SPECIFICATION

## Philosophy

Combat is **dangerous, rare, and consequential**. A single musket shot can be lethal. The goal is not to create a fluid shooter experience, but an immersive simulation of 1840s militia combat.

- **Early game:** Combat is avoided through diplomacy
- **Mid game:** Conflicts arise but can still be talked down
- **Late game:** Combat becomes unavoidable but remains terrifying, not empowering

## Core Combat Loop

```
1. Threat Identification
   ├─ Player detects hostile NPC visually
   ├─ Hostile NPC attempts to flee, talk, or attack
   └─ Combat state initiated

2. Positioning Phase
   ├─ Player moves to cover (walls, buildings, terrain)
   ├─ Enemy NPCs seek positions
   ├─ Stamina drain during movement
   └─ Visibility determined by line-of-sight

3. Engagement Phase
   ├─ Aim & fire (musket) or melee approach
   ├─ Reload (long, vulnerable)
   ├─ Reposition or advance
   └─ Enemy responds in kind

4. Resolution
   ├─ Injury/death occurs (if hit)
   ├─ Morale check (do combatants continue?)
   ├─ Retreat or standoff
   └─ Combat resolved (dead, fled, surrendered)

5. Aftermath
   ├─ Injuries persist and require treatment
   ├─ Reputation changes based on fight outcome
   ├─ Witnesses spread information
   └─ Bodies may need to be handled
```

## Weapon Systems

### Muskets (Primary Weapon)

**Mechanics:**
- Fire rate: 1 shot per 45–60 seconds (realistic reload)
- Damage: High (2–3 body shots lethal)
- Range: Effective to ~100m (reduced accuracy beyond)
- Accuracy: Dependent on stance, training, fatigue

**Realistic Musket Operation:**
1. **Aiming** (2–3 sec)
   - Raise to shoulder
   - Look down barrel (no modern iron sights; period-correct)
   - Hold position (stamina drains during hold)
   - Window of stability: brief (2–3 seconds)

2. **Firing** (instant)
   - Pull trigger
   - Recoil pushes aim up/back
   - Muzzle flash + smoke blooms (vision obscured 1–2 seconds)

3. **Reload** (45–60 sec)
   - Pour powder down barrel
   - Spit/insert ball
   - Ram down with ramrod
   - Prime pan
   - Each step can be interrupted
   - Reload can fail if powder is damp (misfires)

**Training Impact:**
- Untrained: Full reload time, higher misfire rate (~20%)
- Trained: Faster reload (40 sec), lower misfire rate (~5%)
- Expert: Very fast reload (30 sec), rare misfires (~1%)

**Stamina & Fatigue:**
- Sprinting before shooting: Aim sway increases 30%
- After melee: Hands shake, aim sway 50%
- Hunger/thirst: Stamina depletes faster, aim wavers
- Injuries: Dominant arm damage increases sway; shot damage reduces accuracy

### Pistols (Rare, Expensive)

**Mechanics:**
- Fire rate: 1 shot per 20–30 seconds
- Damage: Moderate (3–4 shots lethal)
- Range: Effective to ~30m (beyond that, very inaccurate)
- Cost: ~100x cost of musket ammunition

**Characteristics:**
- Shorter reload than musket but still noticeable
- Less accurate than musket (no long sight line)
- Valued for close-quarters defense
- Officers may carry (status symbol)

### Melee Weapons

**Types:**
- **Clubs/Batons:** Available, non-lethal (mostly)
- **Sabers/Blades:** Rare, prestigious, lethal
- **Bayonets:** Attached to muskets (~20cm blade)
- **Knives:** Utility tools, usable as weapons
- **Fists:** Always available, least effective

**Melee Mechanics:**
- Stamina-based (each swing drains stamina)
- Slow animations (1–2 second swing time)
- Can grapple opponents (break free with strength)
- Can disarm if enemy is knocked back
- Range: ~2 meters for weapons, ~1 meter for fists

**Hit Locations:**
- Head: High damage, can incapacitate
- Torso: Medium damage, affects mobility
- Limbs: Lower damage, reduces arm/leg usage
- Wounds bleed and require treatment

## Stance System

Affects accuracy, mobility, and readiness:

| Stance | Accuracy | Speed | Stamina | Use Case |
|--------|----------|-------|---------|----------|
| **Standing** | 70% | Fast | Normal | Default, mobile |
| **Crouching** | 85% | Slow | High drain | Better accuracy, less mobile |
| **Prone** | 95% | Very slow | Very high drain | Best accuracy, stuck position |
| **Moving** | 40% | Fast | High drain | Repositioning, impossible to aim well |
| **Behind cover** | 80% | Moderate | Moderate drain | Protected from return fire |

**Cover Mechanics:**
- Full cover: Enemy can't see/shoot you
- Partial cover: Player exposed from angles
- Leaning: Briefly expose to sight/fire then retract
- Breaking cover: Full exposure, highest danger

## Ammunition System

**Musket Ammunition:**
- Musket balls + powder + wadding = 1 round
- ~6–10 rounds per pouch (limited carry)
- Takes ~10 seconds to reload one round from pouch
- Found in: Traders, military depot, dropped by defeated enemies
- Scarcity: Early game abundant; late game scarce

**Storage:**
- Ammunition pouch (10–15 rounds)
- Powder horn or flask (1–2 refills)
- Can't carry unlimited (weight limit)
- Wet/damaged ammunition (misfires increase)

**Crafting:**
- Player can craft ammunition if they have:
  - Powder (from traders or captured)
  - Lead balls (from traders or melted)
  - Wadding (cloth scraps)
- Takes time (~5 min per 10 rounds)
- Success dependent on crafting skill

## Damage & Injury System

### Injury Types

**Lacerations (cuts):**
- Source: Blades, bayonets
- Effect: Bleeding (lose 1 HP per 10 sec)
- Treatment: Bandaging (stops bleeding)
- Recovery: Scar remains; reduced arm function if severe

**Blunt Trauma:**
- Source: Clubs, fists, falls
- Effect: Bruising, possible fracture
- Treatment: Rest + splinting
- Recovery: Takes longer; mobility reduced

**Fractures/Breaks:**
- Source: Heavy blunt trauma, falls
- Effect: Limb unusable for combat
- Treatment: Doctor/herbalist (bone-setting painful)
- Recovery: Weeks of reduced mobility

**Gunshot Wounds:**
- Source: Muskets, pistols
- Effect: Massive bleeding + internal damage
- Treatment: Doctor or death (high lethality)
- Recovery: Slow; permanent damage possible

### Bleeding Mechanic

```
Bleeding {
  location: BodyPart (arm, leg, torso, head)
  severity: int (1-10)
  bleed_rate: int (HP/10 sec)
  treatment_required: bool
  
  if (untreated && duration > 60 sec) {
    infection_risk = true
    severity += 1
  }
  
  if (severity >= 8) {
    death_likely = true  // without medical intervention
  }
}
```

### Health & Vitals

**Player Health:**
- Max: 100 HP
- Starts damaged at 80–90 (can have pre-existing injuries)
- Below 40: Wounded (movement slowed, breathing heavy)
- Below 20: Critical (vision darkens, can barely move)
- 0: Death (game over, reload)

**Visible Indicators (No Health Bar):**
- Breathing (audio: heavy breathing = low health)
- Vignetting (vision darkens at edges when wounded)
- Limping (walk animation changes)
- Hand trembling (aim affected)
- Blood dripping from hands/clothing

## Enemy AI (Combat Behavior)

### NPC Aggression States

**1. Neutral**
- NPC goes about daily routine
- Will flee if approached aggressively
- Can be talked to normally

**2. Suspicious**
- Player has drawn weapon
- Or player is trespassing
- NPC watches player, may warn others
- Will not attack yet unless provoked

**3. Hostile**
- NPC has decided to attack
- Will seek cover and attempt to engage
- May call for help
- Will not talk down (unlikely)

**4. Fleeing**
- NPC is losing badly
- Breaks engagement and runs
- May alert others as they flee
- Can be pursued

### Combat Targeting

**Priority System:**
1. Is this person a threat? (wounded, armed?)
2. Am I trained to fight them? (militia fights better than civilians)
3. What are my numbers? (alone = flee, group = fight)
4. What are my options? (escape route, allies nearby?)

**Realistic Behavior:**
- Untrained NPC (civilian) will often flee rather than fight Legion
- Soldiers will stand their ground or retreat in formation
- Officers will take command of groups
- Panicked NPCs may attack irrationally or freeze

### Crowd Effects

**Morale:**
- Seeing ally die: -20 morale (flee if morale < 0)
- Seeing enemy fall: +10 morale
- Being outnumbered: -10 morale per extra enemy
- Officer killed: -30 morale (group likely to break)

**Panic:**
- If morale breaks, unit scatters
- Panicked NPCs can attack randomly
- Witnesses may run toward fight (get in way) or away

## Stealth & Quiet Combat

**Silent Approach:**
- Crouching + staying out of line-of-sight
- If detected, violence becomes loud
- Nearby NPCs hearing gunshots will investigate

**Eliminating Quietly:**
- Use melee in stealth (one-hit kill not guaranteed)
- If successful, no one alerted
- If body found, investigation begins
- Hiding bodies prevents alarm

**Consequences:**
- Killing without witnesses: Harder to pin on you
- Killing with witnesses: Reputation hit + possible arrest
- Stealth is viable but risky

## Combat Scenarios (MVP Content)

### Scenario 1: Training Drill (Non-lethal)
- Legion trains with muskets
- Player participates in marksmanship
- Targets are paper/wooden (no death)
- Recoil, reload, and accuracy matter
- Officer grades performance

### Scenario 2: Gate Confrontation (Escalatable)
- Outsiders attempt to enter town
- Scenario can go multiple ways:
  - **Dialogue:** Convince them to leave (no combat)
  - **Standoff:** Both sides armed but not firing
  - **Violence:** Shots exchanged; someone dies
- Outcome affects faction reputation

### Scenario 3: Mob Confrontation (Crowd Dynamics)
- Civilian crowd gathers (protest or riot)
- Militia present to maintain order
- Player must choose response:
  - **De-escalate:** Talk to crowd leaders
  - **Enforce:** Arrest ringleaders
  - **Retreat:** Let them disperse
- Each choice has different outcome

### Scenario 4: Ambush Defense (Late Game)
- Outsiders attack town
- Player defends position
- Allies assist (or don't, based on reputation)
- Goal: Survive and repel attack
- High lethality; real danger

## Balance & Difficulty

### Scaling (Based on Settings)
- **Easy:** Enemy accuracy reduced, player healing faster, more ammo
- **Normal:** Realistic accuracy, realistic damage
- **Hard:** All shots lethal, bleeding quickens, ammo scarce

### Early Game (Training & Low Stakes)
- Combat avoidable; NPCs won't escalate
- Drills teach mechanics without danger
- Safe environment to learn

### Late Game (High Stakes)
- Combat forced
- Untrained player at significant disadvantage
- Death likely if outnumbered
- Choices have led to this point

## Implementation Notes

### Required assets:
- Musket reload animations (7 steps)
- Melee attack animations (light/heavy swing)
- Injury/death animations (per damage type)
- Muzzle flash effect (brief, realistic)
- Smoke effect (obscures vision)
- Blood effects (on body, on ground)

### Required sounds:
- Musket fire (loud, recognizable)
- Musket reload (cocking, ramming)
- Melee impact (metal, impact sound)
- Pain vocalization (NPCs and player)
- Breathing (audio indicator of health)
- Commands (officers ordering fire)

### Performance considerations:
- Limit active combatants (8–12 max)
- Smoke effects culled after time
- Bodies remain briefly then fade
- Distant combat simplified (no individual targeting)

---

**Combat System Status:** Detailed specification complete  
**Implementation Priority:** High (core gameplay pillar)  
**Complexity Level:** Very High (physics, AI, animation, audio integration)
