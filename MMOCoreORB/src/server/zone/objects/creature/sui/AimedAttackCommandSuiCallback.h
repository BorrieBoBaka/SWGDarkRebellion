#ifndef AIMEDATTACKCOMMANDSUICALLBACK_H_
#define AIMEDATTACKCOMMANDSUICALLBACK_H_

class AimedAttackCommandSuiCallback : public SuiCallback {
private:
	int state;
	int adminLevel;
	CreatureObject* targetCreature;

public:
	AimedAttackCommandSuiCallback(ZoneServer* server, int _state, int _adminLevel, CreatureObject* _targetCreature) : SuiCallback(server) {
		state = _state;
		adminLevel = _adminLevel;
		targetCreature = _targetCreature;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		BorCombat::AttackTarget(player, targetCreature, player, index + 2, false);
	}
};

#endif