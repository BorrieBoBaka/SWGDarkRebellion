#ifndef RESTRPCOMMANDSUICALLBACK_H_
#define RESTRPCOMMANDSUICALLBACK_H_

class RestRPCommandSuiCallback : public SuiCallback {
private:
	//int state;
	uint64 target;
	//int adminLevel;

public:
	RestRPCommandSuiCallback(ZoneServer* server, uint64 _target) : SuiCallback(server) {
		//state = _state;
		target = _target;
		//adminLevel = _adminLevel;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);
		int index = Integer::valueOf(args->get(0).toString());

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == nullptr)
			return;

		int adminLevelCheck = ghost->getAdminLevel();

		//Assigning who the target will be when it comes to rolling these bones.
		ManagedReference<CreatureObject*> targetCreature;
		if (adminLevelCheck > 0) {
			ManagedReference<SceneObject*> object;
			if (target != 0) {
				object = player->getZoneServer()->getObject(target, false);
			}

			if (object != nullptr) {
				if (object->isCreatureObject()) {
					targetCreature = object->asCreatureObject();
				} else {
					targetCreature = player;
				}
			} else {
				targetCreature = player;
			}

		} else {
			targetCreature = player;
		}

		if (cancelPressed)
			return;

		if(index == 0) {
			BorCharacter::PerformShortRest(targetCreature);
		} else if(index == 1) {
			BorCharacter::FillAllPools(targetCreature);
		}
	}
};

#endif