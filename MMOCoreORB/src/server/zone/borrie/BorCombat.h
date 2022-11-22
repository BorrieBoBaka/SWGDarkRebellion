#ifndef BORCOMBAT_H_
#define BORCOMBAT_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

#include "server/zone/borrie/BorrieRPG.h"
#include "server/zone/borrie/BorCharacter.h"
#include "server/zone/borrie/BorDice.h"

class BorCombat : public Logger {
public:
	static void AttackTarget(CreatureObject* attacker, CreatureObject* defender, CreatureObject* commander, int bodyPartTarget, bool powerAttack) {
        ManagedReference<WeaponObject*> weapon = attacker->getWeapon();
        if(weapon->isBroken()) {
            commander->sendSystemMessage("Your weapon is broken, and you can't attack with a broken weapon.");
            return;
        }

        if (!CollisionManager::checkLineOfSight(attacker, defender)) {
            commander->sendSystemMessage("You don't have a direct line of sight of your target.");
            return;
        }

        String attackVerb = powerAttack ? "power attacked" : "attacked";
        if(bodyPartTarget != -1) 
            attackVerb = "aimed at "+defender->getFirstName()+"'s "+GetSlotDisplayName(bodyPartTarget);
        else
            attackVerb += " " + defender->getFirstName();

        //To Hit
        int toHitDC = GetToHitModifier(attacker, defender, weapon) + 10;
        int aimMod = 0;
        if(bodyPartTarget != -1) { //A Body Part was specified.
            aimMod = bodyPartTarget;
            DrainActionOrWill(attacker, 1);
        }
        int skillCheck = 0;
        if(weapon->isMeleeWeapon()) skillCheck = attacker->getSkillMod("rp_melee");
        else if(weapon->isRangedWeapon()) skillCheck = attacker->getSkillMod("rp_ranged");
        else if(weapon->isJediWeapon()) skillCheck = attacker->getSkillMod("rp_lightsaber");
        int toHitRoll = BorDice::Roll(1, 20);

        if(toHitRoll + skillCheck >= toHitDC || toHitRoll == 20) {
            if(bodyPartTarget != -1) {
                //If we specified a target, we need to see if we can hit it.
                if(toHitRoll + skillCheck + aimMod < toHitDC || toHitRoll == 20) {
                    //We failed to hit the target, so get a new target that isn't the one we specified.
                    int newTarget = BorDice::Roll(1, 10);
                    while(bodyPartTarget == newTarget) {
                        newTarget = BorDice::Roll(1, 10);
                    }
                    bodyPartTarget = newTarget;
                } 
            } else {
                //Randomly getting a body part.
                bodyPartTarget = BorDice::Roll(1, 10);
            }
        } else {
            //Miss
            BorrieRPG::BroadcastMessage(attacker, attacker->getFirstName() + " "+attackVerb+ " and missed! \\#DBDBDB" + GenerateOutputSpam(toHitRoll, skillCheck, toHitDC) + "\\#FFFFFF");
            BorEffect::PerformReactiveAnimation(defender, attacker, "miss", GetSlotHitlocation(bodyPartTarget), true);
            return;
        }

        if(powerAttack) {
            DrainActionOrWill(attacker, 1);
            if(toHitRoll + skillCheck + (15 - skillCheck) < toHitDC) {
                //Miss
                BorrieRPG::BroadcastMessage(attacker, attacker->getFirstName() + " "+attackVerb+ " and missed!  \\#DBDBDB" + GenerateOutputSpam(toHitRoll, skillCheck, toHitDC) + "\\#FFFFFF"); 
                BorEffect::PerformReactiveAnimation(defender, attacker, "miss", GetSlotHitlocation(bodyPartTarget), true);
                return;
            } 
        }

        //We've hit! Calculate Damage and apply it to the body part. Get the armor of that part. 
        int damageDieCount = weapon->getMinDamage();
        int damageDieType = weapon->getMaxDamage();

        int totalDamage = GetDamageRoll(damageDieType, damageDieCount, weapon->getBonusDamage());

        if(powerAttack) totalDamage = totalDamage * 2;

        //Calculate the Reaction

        String reactionResult = HandleCombatReaction(attacker, defender, totalDamage, toHitRoll + skillCheck, bodyPartTarget, powerAttack, false);
        
        //Apply Followup as per the reaction.
        String toHitString = "\\#DBDBDB" + GenerateOutputSpam(toHitRoll, skillCheck, toHitDC) + "\\#FFFFFF";

        String combatSpam = attacker->getFirstName() + " "+attackVerb+ " and hit!";
        

        BorrieRPG::BroadcastMessage(attacker, combatSpam + " " + toHitString +  reactionResult);
	}

    static void FlurryAttackTarget(CreatureObject* attacker, CreatureObject* defender, CreatureObject* commander) {
        ManagedReference<WeaponObject*> weapon = attacker->getWeapon();
        if(weapon->isBroken()) {
            commander->sendSystemMessage("Your weapon is broken, and you can't attack with a broken weapon.");
            return;
        }

        if (!CollisionManager::checkLineOfSight(attacker, defender)) {
            commander->sendSystemMessage("You don't have a direct line of sight of your target.");
            return;
        }

        //Dark Rebellion Rulebook Edition I, on Flurry Attack
        /* Instead of simply one attack, you’ll roll three to-hit to determine three different attacks, each providing half damage if they succeed. 
        If the target is using a combat stance that uses action points, they’ll have to spend twice as many action points to counter your attack, 
        though they’ll only need to defeat your highest to-hit roll in order to counter all three attacks. */

        int toHitDC = GetToHitModifier(attacker, defender, weapon) + 10;
        int roll1 = BorDice::Roll(1, 20); 
        int roll2 = BorDice::Roll(1, 20); 
        int roll3 = BorDice::Roll(1, 20); 

        int skillCheck = 0;
        if(weapon->isMeleeWeapon()) skillCheck = attacker->getSkillMod("rp_melee");
        else if(weapon->isRangedWeapon()) skillCheck = attacker->getSkillMod("rp_ranged");
        else if(weapon->isJediWeapon()) skillCheck = attacker->getSkillMod("rp_lightsaber");

        bool hit1 = roll1 + skillCheck >= toHitDC;
        bool hit2 = roll2 + skillCheck >= toHitDC + 5;
        bool hit3 = roll3 + skillCheck >= toHitDC + 10;

        DrainActionOrWill(attacker, 1);

        //Absolute Miss
        if(!hit1 && !hit2 && !hit3) {
            BorrieRPG::BroadcastMessage(attacker, attacker->getFirstName() + " flurry attacked " +  defender->getFirstName() + " and missed! \\#DBDBDB" + GenerateFlurryOutputSpam(roll1, roll2, roll3, skillCheck, toHitDC) + "\\#FFFFFF");
            BorEffect::PerformReactiveAnimation(defender, attacker, "miss", GetSlotHitlocation(BorDice::Roll(1, 10)), true);
            BorEffect::PerformReactiveAnimation(defender, attacker, "miss", GetSlotHitlocation(BorDice::Roll(1, 10)), true);
            BorEffect::PerformReactiveAnimation(defender, attacker, "miss", GetSlotHitlocation(BorDice::Roll(1, 10)), true);
            return;
        }

        int damageDieCount = weapon->getMinDamage();
        int damageDieType = weapon->getMaxDamage();
        int bonusDamage = weapon->getBonusDamage();

        int damage1 = GetDamageRoll(damageDieType, damageDieCount, bonusDamage) / 2;
        int damage2 = GetDamageRoll(damageDieType, damageDieCount, bonusDamage) / 2;
        int damage3 = GetDamageRoll(damageDieType, damageDieCount, bonusDamage) / 2;

        int totalDamage = 0;
        if(hit1) totalDamage += damage1;
        if(hit2) totalDamage += damage2;
        if(hit3) totalDamage += damage3;

        if(totalDamage < 1) totalDamage = 1;

        int hitCount = 0;
        if(hit1) hitCount++;
        if(hit2) hitCount++;
        if(hit3) hitCount++;

        int highestRoll = roll1;
        if(roll2 > highestRoll) highestRoll = roll2;
        if(roll3 > highestRoll) highestRoll = roll3; 

        String reactionResult = HandleCombatReaction(attacker, defender, totalDamage, highestRoll + skillCheck, BorDice::Roll(1, 10), false, true);

        //Apply Followup as per the reaction.
        String toHitString = "\\#DBDBDB" + GenerateFlurryOutputSpam(roll1, roll2, roll3, skillCheck, toHitDC) + "\\#FFFFFF";

        String combatSpam = attacker->getFirstName() + " flurry attacked " +  defender->getFirstName();
        
        if(hitCount == 1) {
            combatSpam += " and hit once!";
        } else {
            combatSpam += " and hit " + String::valueOf(hitCount) + " times!";
        }

        
        BorrieRPG::BroadcastMessage(attacker, combatSpam + " " + toHitString +  reactionResult);
    }

    static int GetDamageRoll(int dieType, int dieCount, int bonusDamage) {
        int totalDamage = bonusDamage;
        for(int i = 0;i<dieCount;i++) {
            totalDamage += BorDice::Roll(1, dieType);
        }

        return totalDamage;
    }

    static String GenerateOutputSpam(int roll, int skillMod, int diceCheck) {
        return "(1d20: " + String::valueOf(roll) + " + " + String::valueOf(skillMod) + ") = " + String::valueOf(roll + skillMod) + " vs. DC: " + String::valueOf(diceCheck) + ")";
    }

    static String GenerateFlurryOutputSpam(int roll1, int roll2, int roll3, int skillMod, int diceCheck) {
        String result = "(3d20: "+ String::valueOf(roll1) + ", ";
        result += String::valueOf(roll2) + ", ";
        result += String::valueOf(roll3) + " ";
        result += "+ " + String::valueOf(skillMod) + ") vs. DC: " + String::valueOf(diceCheck) + ", " + String::valueOf(diceCheck+5)+", " + String::valueOf(diceCheck+10) +" )"; 
        return result;
    }

    static String HandleCombatReaction(CreatureObject* attacker, CreatureObject* defender, int incomingDamage, int toHit, int slot, bool powerAttacked, bool flurryAttacked) {
        WeaponObject* attackerWeapon = attacker->getWeapon();
        WeaponObject* defenderWeapon = defender->getWeapon();
        int defenderReactionType = defender->getStoredInt("reaction_stance");
        //int defenderAction = defender->getHAM(3);

        String reactionSpam = "";
        String damageModString = powerAttacked ? " X 2" : "";

        int actionPointMod = 1;
        if(flurryAttacked)
            actionPointMod = 2;

        if(CanPerformReaction(defender, defenderReactionType, incomingDamage, attackerWeapon, defenderWeapon)) {
            if(defenderReactionType == 1) { //Defend
                int defenseRoll = BorDice::Roll(1, 20);
                int defenseSkill = defender->getSkillMod("rp_defense");
                DrainActionOrWill(defender, 1 * actionPointMod);
                if(defenseRoll + defenseSkill > toHit) { //Success
                    defenderWeapon->setConditionDamage(defenderWeapon->getConditionDamage() + incomingDamage);
                    reactionSpam += defender->getFirstName() + " successfully defends against the attack (1d20 = " + String::valueOf(defenseRoll) + " + " + String::valueOf(defenseSkill) + ")";
                    reactionSpam += ", absorbing \\#FF9999" + String::valueOf(incomingDamage) + "\\#FFFFFF damage into their weapon.";
                    BorEffect::PerformReactiveAnimation(defender, attacker, "defend", GetSlotHitlocation(slot), true);
    
                } else {
                    BorCharacter::ModPool(defender, "health", incomingDamage * -1, true);
                    reactionSpam += defender->getFirstName() + "tries to defend against the attack, but fails (1d20 = " + String::valueOf(defenseRoll) + " + " + String::valueOf(defenseSkill) + ")";
                    reactionSpam += ", taking \\#FF9999" + String::valueOf(incomingDamage) + "\\#FFFFFF damage.";
                    BorEffect::PerformReactiveAnimation(defender, attacker, "defend", GetSlotHitlocation(slot), false);
                }
                return reactionSpam;
            } else if(defenderReactionType == 2) { //Parry
                int meleeRoll = BorDice::Roll(1, 20);
                int meleeSkill = defender->getSkillMod("rp_melee");
                if(meleeRoll + meleeSkill >= toHit) {
                    //Successful Parry
                    DrainActionOrWill(defender, 3 * actionPointMod);
                    BorCharacter::ModPool(attacker, "health", (incomingDamage / 2) * -1, true);
                    BorEffect::PerformReactiveAnimation(defender, attacker, "parry", GetSlotHitlocation(slot), true);
                } else {
                    //Unsuccessful Parry
                    DrainActionOrWill(defender, 2 * actionPointMod);
                    defenderWeapon->setConditionDamage(defenderWeapon->getConditionDamage() + incomingDamage);
                    BorEffect::PerformReactiveAnimation(defender, attacker, "parry", GetSlotHitlocation(slot), false);
                }
                return reactionSpam;
            } else if(defenderReactionType == 3) { //Dodge
                int athleticsSkill = defender->getSkillMod("rp_athletics");
                int maneuverabilitySkill = defender->getSkillMod("rp_maneuverability");
                int dodgeRoll = BorDice::Roll(1, 20);
                int highestSkill = athleticsSkill > maneuverabilitySkill ? athleticsSkill : maneuverabilitySkill;
                DrainActionOrWill(defender, 1 * actionPointMod);
                if(dodgeRoll + highestSkill >= toHit) { //Successful Dodge
                    reactionSpam += ", but" + defender->getFirstName() + " dodges out of the way! (1d20 = " + String::valueOf(dodgeRoll) + " + " + String::valueOf(highestSkill) + ")";
                    BorEffect::PerformReactiveAnimation(defender, attacker, "dodge", GetSlotHitlocation(slot), true);
                } else if(dodgeRoll + highestSkill >= toHit / 2 ) { //Partial Dodge
                    reactionSpam += ", " + defender->getFirstName() + " struggles to dodge out of the way! (1d20 = " + String::valueOf(dodgeRoll) + " + " + String::valueOf(highestSkill) + ") ";
                    reactionSpam += defender->getFirstName() + " stumbles, but only takes \\#FF9999" + String::valueOf(incomingDamage / 2) + "\\#FFFFFF damage.";
                    BorCharacter::ModPool(defender, "health", (incomingDamage / 2) * -1);
                    BorEffect::PerformReactiveAnimation(defender, attacker, "dodge", GetSlotHitlocation(slot), true);
                } else { //full fail
                    reactionSpam += ", " + defender->getFirstName() + " tries to dodge out of the way and fails! (1d20 = " + String::valueOf(dodgeRoll) + " + " + String::valueOf(highestSkill) + ") ";
                    reactionSpam += defender->getFirstName() +" takes \\#FF9999" + String::valueOf(incomingDamage) + "\\#FFFFFF damage.";
                    BorCharacter::ModPool(defender, "health", incomingDamage * -1, true);
                    BorEffect::PerformReactiveAnimation(defender, attacker, "dodge", GetSlotHitlocation(slot), false);
                }
                return reactionSpam;
            } else if(defenderReactionType == 4) { //Lightsaber Deflect
                return reactionSpam;
            } else if(defenderReactionType == 5) { //Force Deflect
                return reactionSpam;
            } else if(defenderReactionType == 6) { //Force Absorb
                return reactionSpam;
            }
            return reactionSpam;
        } else {
            //Simply accept the damage. 
            BorCharacter::ModPool(defender, "health", incomingDamage * -1, true);
            BorEffect::PerformReactiveAnimation(defender, attacker, "hit", GetSlotHitlocation(slot), true);
            return ", doing (" + GetWeaponDamageString(attackerWeapon) + ") = \\#FF9999" + String::valueOf(incomingDamage) + "\\#FFFFFF damage.";
        }
    }

    static void ApplyAdjustedHealthDamage(CreatureObject* creature, WeaponObject* attackerWeapon, int damage, int slot) {
        if(creature->isPlayerCreature()) { //Use their equipped armor
            ManagedReference<ArmorObject*> armor = BorCharacter::GetArmorAtSlot(creature, GetSlotName(slot));
            if(armor != nullptr) {
                if(!armor->isBroken()) {
                    String damageType = GetDamageType(attackerWeapon);
                    if(damageType == "Lightsaber") { //Special Lightsaber Rules
                        if(armor->getLightSaber() > 0) { //Can Resist Lightsabers
                            //Take only 10 percent damage.
                            BorCharacter::ModPool(creature, "health", (damage / 10) * -1, true);
                        } else { //Take Full Damage
                            BorCharacter::ModPool(creature, "health", damage * -1, true);
                        }
                    } else {
                        //Get Defense
                        int weaponArmorPiercing = attackerWeapon->getArmorPiercing();
                        int armorRating = armor->getRating();
                        int damageDivider = GetWeaponPenetrationDivisionModifier(weaponArmorPiercing, armorRating);
                        if(damageDivider != 0) {
                            int adjustedDamage = damage / damageDivider;
                            int armorProtection = GetArmorProtection(armor, GetDamageType(attackerWeapon));
                            int finalDamage = adjustedDamage - armorProtection;
                            if(finalDamage < 1) finalDamage = 1;
                            armor->setConditionDamage(armor->getConditionDamage() + armorProtection);
                            BorCharacter::ModPool(creature, "health", finalDamage * -1, true);
                        } else { //Take Full Damage
                            BorCharacter::ModPool(creature, "health", damage * -1, true);
                        }                        
                    }
                } else { //Take Full Damage
                    BorCharacter::ModPool(creature, "health", damage * -1, true);
                }
            } else { //Take Full Damage
                BorCharacter::ModPool(creature, "health", damage * -1, true);
            }
        } else { //Use their skill mod armor. 
            String armorSlot = GetSlotName(slot);
            String damageType = GetDamageType(attackerWeapon);
            if(damageType == "Lightsaber") {
                if(creature->getStoredInt("rp_armor_" + armorSlot + "_Lightsaber") > 0) {
                    //Take only 10 percent damage.
                    BorCharacter::ModPool(creature, "health", (damage / 10) * -1, true);
                } else {
                    BorCharacter::ModPool(creature, "health", damage * -1, true);
                }
            } else {
                int armorRating = creature->getStoredInt("rp_armor_rating_" + armorSlot);
                int weaponArmorPiercing = attackerWeapon->getArmorPiercing();
                int damageDivider = GetWeaponPenetrationDivisionModifier(weaponArmorPiercing, armorRating);
                if(damageDivider != 0) {
                    int adjustedDamage = damage / damageDivider;
                    int armorProtection = creature->getStoredInt("rp_armor_" + armorSlot + "_" + GetDamageType(attackerWeapon));
                    int finalDamage = adjustedDamage - armorProtection;
                    BorCharacter::ModPool(creature, "health", finalDamage * -1, true);
                } else { //Take Full Damage
                    BorCharacter::ModPool(creature, "health", damage * -1, true);
                }
            }            
        }
    }

    static int GetArmorProtection(ArmorObject* armor, String damageType) {
        if(damageType == "Kinetic")             return Integer::valueOf(armor->getKinetic());
        else if(damageType == "Energy")         return Integer::valueOf(armor->getEnergy());
        else if(damageType == "Electricity")    return Integer::valueOf(armor->getElectricity());
        else if(damageType == "Stun")           return Integer::valueOf(armor->getStun());
        else if(damageType == "Blast")          return Integer::valueOf(armor->getBlast());
        else if(damageType == "Heat")           return Integer::valueOf(armor->getHeat());
        else if(damageType == "Cold")           return Integer::valueOf(armor->getCold());
        else if(damageType == "Acid")           return Integer::valueOf(armor->getAcid());
        else return 0;
    }

    static int GetWeaponCondition(WeaponObject* weapon) {
        return weapon->getMaxCondition() - weapon->getConditionDamage();
    }

    static int GetWeaponPenetrationDivisionModifier(int weaponPiercing, int armorRating) {
        if(armorRating == 0) {
            if(weaponPiercing == 0) return 1; //None
            else if(weaponPiercing == 1) return 1; //Light
            else if(weaponPiercing == 2) return 0; //Medium
            else if(weaponPiercing == 3) return 0; //Heavy
            else return 1;
        } else if(armorRating == ArmorObject::LIGHT) {
            if(weaponPiercing == 0) return 2; //None
            else if(weaponPiercing == 1) return 1; //Light
            else if(weaponPiercing == 2) return 1; //Medium
            else if(weaponPiercing == 3) return 0; //Heavy
            else return 1;
        } else if(armorRating == ArmorObject::MEDIUM) {
            if(weaponPiercing == 0) return 2; //None
            else if(weaponPiercing == 1) return 2; //Light
            else if(weaponPiercing == 2) return 1; //Medium
            else if(weaponPiercing == 3) return 1; //Heavy
            else return 1;            
        } else if(armorRating == ArmorObject::HEAVY) {
            if(weaponPiercing == 0) return 2; //None
            else if(weaponPiercing == 1) return 2; //Light
            else if(weaponPiercing == 2) return 2; //Medium
            else if(weaponPiercing == 3) return 1; //Heavy
            else return 1;  
        } else return 1;
    }

    static String GetDamageType(WeaponObject* weapon) {
	    String result;

	    switch (weapon->getDamageType()) {
	    case SharedWeaponObjectTemplate::KINETIC:
	    	result = "Kinetic";
	    	break;
	    case SharedWeaponObjectTemplate::ENERGY:
	    	result = "Energy";
	    	break;
	    case SharedWeaponObjectTemplate::ELECTRICITY:
	    	result = "Electricity";
	    	break;
	    case SharedWeaponObjectTemplate::STUN:
	    	result = "Stun";
	    	break;
	    case SharedWeaponObjectTemplate::BLAST:
	    	result = "Blast";
	    	break;
	    case SharedWeaponObjectTemplate::HEAT:
	    	result = "Heat";
	    	break;
	    case SharedWeaponObjectTemplate::COLD:
	    	result = "Cold";
	    	break;
	    case SharedWeaponObjectTemplate::ACID:
	    	result = "Acid";
	    	break;
	    case SharedWeaponObjectTemplate::LIGHTSABER:
	    	result = "Lightsaber";
	    	break;
	    default:
	    	result = "Unknown";
	    	break;
	    }

        return result;
    }

    static String GetSlotName(int slot) {
        if(slot == 1) return "chest";
        else if(slot == 2) return "chest";
        else if(slot == 3) return "pants1";
        else if(slot == 4) return "shoes";
        else if(slot == 5) return "bracer_upper_l";
        else if(slot == 6) return "bracer_upper_r";
        else if(slot == 7) return "bicep_l";
        else if(slot == 8) return "bicep_r";
        else if(slot == 9) return "gloves";
        else if(slot == 10) return "hat";
        else return "chest";
    }

    static String GetSlotDisplayName(int slot) {
        if(slot == 1) return "chest";
        else if(slot == 2) return "chest";
        else if(slot == 3) return "legs";
        else if(slot == 4) return "feet";
        else if(slot == 5) return "left forearm";
        else if(slot == 6) return "right forearm";
        else if(slot == 7) return "left bracer";
        else if(slot == 8) return "right bracer";
        else if(slot == 9) return "hands";
        else if(slot == 10) return "head";
        else return "chest";
    }

    static uint8 GetSlotHitlocation(int slot) {
        if(slot == 1) return CombatManager::HIT_BODY;
        else if(slot == 2) return CombatManager::HIT_BODY;
        else if(slot == 3) return CombatManager::HIT_LLEG;
        else if(slot == 4) return CombatManager::HIT_RLEG;
        else if(slot == 5) return CombatManager::HIT_LARM;
        else if(slot == 6) return CombatManager::HIT_RARM;
        else if(slot == 7) return CombatManager::HIT_LARM;
        else if(slot == 8) return CombatManager::HIT_RARM;
        else if(slot == 9) return CombatManager::HIT_BODY;
        else if(slot == 10) return CombatManager::HIT_HEAD;
        else return CombatManager::HIT_BODY;
    }


    static String GetWeaponDamageString(WeaponObject* weapon) {
        if(weapon->getBonusDamage() > 0)
            return String::valueOf(weapon->getMinDamage()) + "d" + String::valueOf(weapon->getMaxDamage()) + " + " + String::valueOf(weapon->getBonusDamage());
        else
            return String::valueOf(weapon->getMinDamage()) + "d" + String::valueOf(weapon->getMaxDamage());
    }

    static bool CanPerformReaction(CreatureObject* defender, int reactionType, int incomingDamage, WeaponObject* attackerWeapon, WeaponObject* defenderWeapon) {
        int defenderAction = GetAvailableActionPoints(defender);
        if(reactionType == 0) return false; //Returns false so the catch of "none" will use the same code
        else if(reactionType == 1 && defenderAction > 0 && GetWeaponCondition(defenderWeapon) <= incomingDamage) return true;
        else if(reactionType == 2 && defenderWeapon->isMeleeWeapon() && attackerWeapon->isMeleeWeapon() && defenderAction > 1 && GetWeaponCondition(defenderWeapon) <= incomingDamage) return true;
        else if(reactionType == 3 && defender->isStanding() && defenderAction > 0) return true;
        else if(reactionType == 4 || reactionType == 5 || reactionType == 6 ) {
            if(reactionType == 4 || reactionType == 5) {
                int lightsaberSkill = defender->getSkillMod("rp_lightsaber");
                if(defenderWeapon->isJediWeapon()) {
                    if(defenderAction >= (11 - lightsaberSkill)) {
                        return true;
                    } else return false;
                } else return false;
            } else {
                int inwardSkill = defender->getSkillMod("rp_inward");
                int forcePool = 999;
                if(defender->isPlayerCreature()) {
                    forcePool = defender->getPlayerObject()->getForcePower();
                }
                if(forcePool >= (12 - inwardSkill)) {
                    return true;
                } else return false;
            }
        } else return false;
    }

    static int GetAvailableActionPoints(CreatureObject* creature) {
        if(creature->getHAM(3) == 0)
            return creature->getHAM(6);
        else return creature->getHAM(3) + creature->getHAM(6);
    }

    static void DrainActionOrWill(CreatureObject* creature, int amount) {
        if(creature->getHAM(3) >= amount)
            BorCharacter::ModPool(creature, "action", amount * -1, true);
        else {
            int remainingAction = creature->getHAM(3);
            BorCharacter::ModPool(creature, "action", remainingAction * -1, true);
            BorCharacter::ModPool(creature, "will", (amount - remainingAction) * -1, true);
        }
    }

    static int GetToHitModifier(CreatureObject* attacker, CreatureObject* defender, WeaponObject* attackerWeapon) {
        int distance = BorCharacter::GetTargetDistance(attacker, defender);
        int minRange = attackerWeapon->getPointBlankRange();
        int maxRange = attackerWeapon->getMaxRange();
        int prefRange = attackerWeapon->getIdealRange();

        int distanceModifier = 0;
        bool tooClose = false;

        if(distance < minRange) {
            //distanceModifier = attackerWeapon->getPointBlankAccuracy();
            distanceModifier = 5;
            tooClose = true;
        } else if(distance <= prefRange) {
            distanceModifier = attackerWeapon->getPointBlankAccuracy();
        } else if(distance > prefRange && distance < maxRange) {
            distanceModifier = attackerWeapon->getIdealAccuracy();
        } else if(distance > maxRange) {
            distanceModifier = 99;
        }

        int postureModifier = 0;

        if(attacker->isKneeling() && !tooClose) {
            postureModifier -= 2;
        } 

        if(defender->isKneeling() && !tooClose) {
            postureModifier += 2;
        } 

        if(attacker->isProne() && !tooClose) {
            postureModifier -= 5;
        }

        if(defender->isProne() && !tooClose) {
            postureModifier += 5;
        } 

        return distanceModifier + postureModifier;
    }
};

#endif /*BORCOMBAT_H_*/