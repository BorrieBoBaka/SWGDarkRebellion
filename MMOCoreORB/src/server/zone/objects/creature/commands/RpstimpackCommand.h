/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPSTIMPACKCOMMAND_H_
#define RPSTIMPACKCOMMAND_H_

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/borrie/BorCharacter.h"

class RpstimpackCommand : public QueueCommand {
	float range;
	float mindCost;

public: 
	RpstimpackCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
		range = 5;
	}

	StimPack* findStimPack(CreatureObject* creature) const {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr)
			return nullptr;

		bool melee = range <= 5.0f;

		for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			SceneObject* item = inventory->getContainerObject(i);

			if (!item->isPharmaceuticalObject())
				continue;

			PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>(item);

			if (melee && pharma->isStimPack() && !pharma->isRangedStimPack() && !pharma->isPetStimPack() && !pharma->isDroidRepairKit()) {
				StimPack* stimPack = cast<StimPack*>(pharma);

				return stimPack;
			}

			if (pharma->isRangedStimPack()) {
				RangedStimPack* stimPack = cast<RangedStimPack*>(pharma);

				return stimPack;
					
			}
		}

		return nullptr;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void doAnimationsRange(CreatureObject* creature, CreatureObject* creatureTarget, int oid, float range) const {
		String crc;

		if (range < 10.0f) {
			crc = "throw_grenade_near_healing";
		}
		else if (10.0f <= range && range < 20.0f) {
			crc = "throw_grenade_medium_healing";
		}
		else {
			crc = "throw_grenade_far_healing";
		}

		CombatAction* action = new CombatAction(creature, creatureTarget,  crc.hashCode(), 1, 0L);
		creature->broadcastMessage(action, true);
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, StimPack* stimPack) const {
		if (stimPack == nullptr) {
			creature->sendSystemMessage("@healing_response:healing_response_60"); //No valid medicine found.
			return false;
		}

		if (creature->getHAM(CreatureAttribute::ACTION) < 1) {
			creature->sendSystemMessage("You do not have enough action to do that.");
			return false;
		} else if (creature->getHAM(CreatureAttribute::MIND) < 1) {
			creature->sendSystemMessage("You do not have enough will to do that.");
			return false;
		}

		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH)) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("@healing_response:healing_response_61"); //You have no damage to heal.
			} else if (creatureTarget->isPlayerCreature()) {
				StringIdChatParameter stringId("healing_response", "healing_response_63"); //%NT has no damage to heal.
				stringId.setTT(creatureTarget->getObjectID());
				creature->sendSystemMessage(stringId);
			} else {
				StringBuffer message;
				message << creatureTarget->getDisplayedName() << " has no damage to heal.";
				creature->sendSystemMessage(message.toString());
			}
			return false;
		}

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != nullptr) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != nullptr && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else {
					creature->sendSystemMessage("@healing_response:healing_response_62"); //Target must be a player or a creature pet in order to heal damage.
					return GENERALERROR;
				}
			}
		} else {
			object = creature;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		Locker clocker(targetCreature, creature);

		if ( targetCreature->isDroidObject() || targetCreature->isVehicleObject() || targetCreature->isDead() || targetCreature->isRidingMount() || targetCreature->isAttackableBy(creature))
			targetCreature = creature;

		uint64 pharmaceuticalObjectID = 0;

		try {
			if (!arguments.isEmpty())
				pharmaceuticalObjectID = UnsignedLong::valueOf(arguments.toString());
		} catch (Exception& e) {

		}

		ManagedReference<StimPack*> stimPack;

		if (pharmaceuticalObjectID == 0) {
			stimPack = findStimPack(creature);
		} else {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != nullptr) {
				stimPack = inventory->getContainerObject(pharmaceuticalObjectID).castTo<StimPack*>();
			}
		}

		if (!canPerformSkill(creature, targetCreature, stimPack))
			return GENERALERROR;

		float rangeToCheck = 7;

		if (stimPack->isRangedStimPack())
			rangeToCheck = (cast<RangedStimPack*>(stimPack.get()))->getRange();

		if(!checkDistance(creature, targetCreature, rangeToCheck))
			return TOOFAR;

		if (creature != targetCreature && !CollisionManager::checkLineOfSight(creature, targetCreature)) {
			creature->sendSystemMessage("@healing:no_line_of_sight"); // You cannot see your target.
			return GENERALERROR;
		}

		if (creature->isPlayerCreature() && targetCreature->getParentID() != 0 && creature->getParentID() != targetCreature->getParentID()) {
			Reference<CellObject*> targetCell = targetCreature->getParent().get().castTo<CellObject*>();

			if (targetCell != nullptr) {
				if (!targetCreature->isPlayerCreature()) {
					auto perms = targetCell->getContainerPermissions();

					if (!perms->hasInheritPermissionsFromParent()) {
						if (!targetCell->checkContainerPermission(creature, ContainerPermissions::WALKIN)) {
							creature->sendSystemMessage("@combat_effects:cansee_fail"); // You cannot see your target.
							return GENERALERROR;
						}
					}
				}

				ManagedReference<SceneObject*> parentSceneObject = targetCell->getParent().get();

				if (parentSceneObject != nullptr) {
					BuildingObject* buildingObject = parentSceneObject->asBuildingObject();

					if (buildingObject != nullptr && !buildingObject->isAllowedEntry(creature)) {
						creature->sendSystemMessage("@combat_effects:cansee_fail"); // You cannot see your target.
						return GENERALERROR;
					}
				}
			}
		}

		Locker locker(stimPack);
		stimPack->decreaseUseCount();

		if(BorCharacter::HealWithStimpack(stimPack, creature, targetCreature)) {
			if (stimPack->isRangedStimPack()) {
				doAnimationsRange(creature, targetCreature, stimPack->getObjectID(), creature->getWorldPosition().distanceTo(targetCreature->getWorldPosition()));
			} else {
				doAnimations(creature, targetCreature);
			}
		}

		return SUCCESS;
	}

	

};

#endif //RPSTIMPACKCOMMAND_H_