/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFSTORMCOMMAND_H_
#define RPFSTORMCOMMAND_H_

class RpfstormCommand : public QueueCommand {

public: 
	RpfstormCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFSTORMCOMMAND_H_