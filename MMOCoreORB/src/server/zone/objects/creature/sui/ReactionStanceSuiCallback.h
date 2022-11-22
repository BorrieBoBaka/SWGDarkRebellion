#ifndef REACTIONSTANCESUICALLBACK_H_
#define REACTIONSTANCESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class ReactionStanceSuiCallback : public SuiCallback {
private:
	int state;
	int selection;

public:
	ReactionStanceSuiCallback(ZoneServer* server, int _state, int _selection) : SuiCallback(server) {
		state = _state;
		selection = _selection;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);
		int index = Integer::valueOf(args->get(0).toString());

		if (cancelPressed)
			return;

		if(index == 0) { //0 None
			player->sendExecuteConsoleCommand("/rpsetstance none");
		} else if(index == 1) { //1 Defend
			player->sendExecuteConsoleCommand("/rpsetstance defend");
		} else if(index == 2) { //2 Parry
			player->sendExecuteConsoleCommand("/rpsetstance parry");			
		}else if(index == 3) { //3 Dodge
			player->sendExecuteConsoleCommand("/rpsetstance dodge");			
		}else if(index == 4) { //4 Lightsaber Deflect
			player->sendExecuteConsoleCommand("/rpsetstance deflect");			
		}else if(index == 5) { //5 Force Deflect
			player->sendExecuteConsoleCommand("/rpsetstance fdeflect");			
		}else if(index == 6) { //6 Force Absorb
			player->sendExecuteConsoleCommand("/rpsetstance absorb");			
		}
		
		
		
		
		
		
		

		

	}

};

#endif /* REACTIONSTANCESUICALLBACK_H_ */