/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFPRECOGCOMMAND_H_
#define RPFPRECOGCOMMAND_H_

class RpfprecogCommand : public QueueCommand {

public: 
	RpfprecogCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFPRECOGCOMMAND_H_