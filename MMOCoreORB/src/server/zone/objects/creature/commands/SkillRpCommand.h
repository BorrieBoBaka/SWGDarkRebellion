/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SKILLRPCOMMAND_H_
#define SKILLRPCOMMAND_H_

class SkillRpCommand : public QueueCommand {

public:
	SkillRpCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		return SUCCESS;
	}

};

#endif 
