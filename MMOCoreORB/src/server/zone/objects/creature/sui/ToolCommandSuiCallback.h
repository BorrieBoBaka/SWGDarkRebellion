#ifndef TOOLCOMMANDSUICALLBACK_H_
#define TOOLCOMMANDSUICALLBACK_H_

class ToolCommandSuiCallback : public SuiCallback {
private:
	int state;
	uint64 target;
	int adminLevel;

public:
	ToolCommandSuiCallback(ZoneServer* server, uint64 _target, int _state, int _adminLevel) : SuiCallback(server) {
		state = _state;
		target = _target;
		adminLevel = _adminLevel;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed)
			return;
	}
};

#endif