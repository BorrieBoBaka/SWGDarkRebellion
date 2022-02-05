/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFMEDITATECOMMAND_H_
#define RPFMEDITATECOMMAND_H_

class RpfmeditateCommand : public QueueCommand {

public: 
	RpfmeditateCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFMEDITATECOMMAND_H_