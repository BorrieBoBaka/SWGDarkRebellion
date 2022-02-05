/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ATTACKNPCCOMMAND_H_
#define ATTACKNPCCOMMAND_H_

class AttackNpcCommand : public QueueCommand {

public:
	AttackNpcCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		return SUCCESS;
	}

};

#endif 
