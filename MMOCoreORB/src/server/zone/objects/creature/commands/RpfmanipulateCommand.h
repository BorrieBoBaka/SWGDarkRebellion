/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFMANIPULATECOMMAND_H_
#define RPFMANIPULATECOMMAND_H_

class RpfmanipulateCommand : public QueueCommand {

public: 
	RpfmanipulateCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFMANIPULATECOMMAND_H_