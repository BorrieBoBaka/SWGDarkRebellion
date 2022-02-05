/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFDOMINATECOMMAND_H_
#define RPFDOMINATECOMMAND_H_

class RpfdominateCommand : public QueueCommand {

public: 
	RpfdominateCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFDOMINATECOMMAND_H_