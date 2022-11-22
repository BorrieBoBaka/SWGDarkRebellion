/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPIMPHEALCOMMAND_H_
#define RPIMPHEALCOMMAND_H_

class RpimphealCommand : public QueueCommand {

public: 
	RpimphealCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, StimPack* stimPack, int mindCostNew) const {
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

		if ((targetCreature->isAiAgent() && !targetCreature->isPet()) || targetCreature->isDroidObject() || targetCreature->isVehicleObject() || targetCreature->isDead() || targetCreature->isRidingMount() || targetCreature->isAttackableBy(creature))
			targetCreature = creature;

		if(!checkDistance(creature, targetCreature, 7))
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

		if(BorCharacter::PerformImprovHeal(creature, targetCreature)) {
			doAnimations(creature, targetCreature);
		}

		return SUCCESS;
	}

};

#endif //RPIMPHEALCOMMAND_H_