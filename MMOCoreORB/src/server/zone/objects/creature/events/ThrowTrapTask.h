/*
 * ThrowTrapTask.h
 *
 *  Created on: Nov 20, 2010
 *      Author: da
 */

#ifndef THROWTRAPTASK_H_
#define THROWTRAPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "templates/tangible/TrapTemplate.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class ThrowTrapTask : public Task {
	ManagedReference<CreatureObject* > player;
	ManagedReference<CreatureObject* > target;
	ManagedReference<Buff*> buff;
	StringIdChatParameter message;
	int damage;
	short pool;
	bool hit;
	TrapTemplate* trapData;
	
public:
	ThrowTrapTask(CreatureObject* p, CreatureObject* t,
			Buff* b, const StringIdChatParameter& m, short po, int d, bool h, TrapTemplate* td) : Task(2300) {
		player = p;
		target = t;
		buff = b;
		message = m;
		damage = d;
		pool = po;
		hit = h;
		trapData = td;
	}

	virtual ~ThrowTrapTask() {
	}

	void run() {
		if (player == nullptr || target == nullptr)
			return;

		Locker locker2(player);

		player->removePendingTask("throwtrap");

		Locker locker(target, player);

		if(!CombatManager::instance()->startCombat(player, target))
			return;

		player->sendSystemMessage(message);

		String defenseMod = trapData->getDefenseMod();
		uint64 trapState = trapData->getState();
		String startSpam = trapData->getStartSpam();
		String stopSpam = trapData->getStopSpam();
		String successMessage = trapData->getSuccessMessage();
		String failMessage = trapData->getFailMessage();
		int range = 12; //TODO: Needs to be from trapData.

		if(hit) {
			int xp = target->getLevel() * 15;
			hitTarget(player, target, buff, damage, pool);
				
			//Get AOE.
			if(range > 0) {
				SortedVector<QuadTreeEntry*> closeObjects;
				Zone* zone = player->getZone();
				if (player->getCloseObjects() == nullptr) {
					zone->getInRangeObjects(player->getPositionX(), player->getPositionY(), range, &closeObjects, true);
				} else {
					CloseObjectsVector* closeVector = (CloseObjectsVector*) player->getCloseObjects();
					closeVector->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);
				}

				int trappingSkill = player->getSkillMod("trapping");

				for(int i = 0;i<closeObjects.size();i++) {
					SceneObject* targetObject = static_cast<SceneObject*>(closeObjects.get(i));
					if(targetObject->isCreatureObject()) {
						ManagedReference<CreatureObject*> aoeTarget = targetObject->asCreatureObject();
						Locker locker(aoeTarget, player);
						//Get if we can attack the potential victim, and see if he's in range of the original target
						if(aoeTarget->isAttackableBy(player) && target->isInRange(aoeTarget, range)) {
							//Taking the hit data out of the ThrowTrapCommand
							int targetDefense = aoeTarget->getSkillMod(defenseMod);
							float hitChance = CombatManager::instance()->hitChanceEquation(trappingSkill, System::random(199) + 1, targetDefense, System::random(199) + 1);

							if (hitChance > 100)
								hitChance = 100.0;
							else if (hitChance < 0)
								hitChance = 0;

							int roll = System::random(100);
							bool aoeHit = roll < hitChance && (trapState == 0 || (trapState != 0 && !aoeTarget->hasState(trapState)));
							StringIdChatParameter aoeMessage;
							if(aoeHit) {
								aoeMessage.setStringId("trap/trap" , successMessage);
								ManagedReference<Buff*> aoeBuff = new Buff(aoeTarget, buff->getBuffCRC(), buff->getBuffDuration(), buff->getBuffType());

								Locker aoeBuffLocker(aoeBuff);

								if(trapState != 0)
									aoeBuff->addState(trapState);

								const auto skillMods = trapData->getSkillMods();
								for(int i = 0; i < skillMods->size(); ++i) {
									aoeBuff->setSkillModifier(skillMods->elementAt(i).getKey(), skillMods->get(i));
								}
								
								if(!startSpam.isEmpty())
									aoeBuff->setStartFlyText("trap/trap", startSpam,  0, 0xFF, 0);

								if(!stopSpam.isEmpty())
									aoeBuff->setEndFlyText("trap/trap", stopSpam,  0xFF, 0, 0);

								int aoeDamage = System::random(trapData->getMaxDamage() - trapData->getMinDamage()) + trapData->getMinDamage();

								hitTarget(player, aoeTarget, aoeBuff, aoeDamage, pool);
								xp += target->getLevel() * 15;
							} else {
								if(failMessage.isEmpty()) {
									aoeMessage.setStringId("trap/trap", failMessage);
								}
							}

							aoeMessage.setTT(aoeTarget->getDisplayedName());

							player->sendSystemMessage(message);
						}
					}
				}
			} 
			

			//Not sure on exact xp value, estimate now and update later
			ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();
			if(playerManager != nullptr)
				playerManager->awardExperience(player, "trapping", xp, true);
		}

	}

	void hitTarget(CreatureObject* player, CreatureObject* target, Buff* buff, int damage, short pool) {
			if(buff != nullptr) {
				Locker buffLocker(buff);

				target->addBuff(buff);
			}

			target->inflictDamage(player, pool, damage, true);
	}
};

}
}
}
}
}

using namespace server::zone::objects::creature::events;

#endif /* THROWTRAPTASK_H_ */
