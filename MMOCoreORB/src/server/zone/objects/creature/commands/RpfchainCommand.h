/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFCHAINCOMMAND_H_
#define RPFCHAINCOMMAND_H_

class RpfchainCommand : public QueueCommand {

public: 
	RpfchainCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFCHAINCOMMAND_H_