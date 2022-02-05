/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFLIGHTNINGCOMMAND_H_
#define RPFLIGHTNINGCOMMAND_H_

class RpflightningCommand : public QueueCommand {

public: 
	RpflightningCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFLIGHTNINGCOMMAND_H_