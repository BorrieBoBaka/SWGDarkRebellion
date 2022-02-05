/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFDEFLECTCOMMAND_H_
#define RPFDEFLECTCOMMAND_H_

class RpfdeflectCommand : public QueueCommand {

public: 
	RpfdeflectCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFDEFLECTCOMMAND_H_