/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFPROJECTCOMMAND_H_
#define RPFPROJECTCOMMAND_H_

class RpfprojectCommand : public QueueCommand {

public: 
	RpfprojectCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFPROJECTCOMMAND_H_