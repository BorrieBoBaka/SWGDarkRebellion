/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ENTERTICKETPURCHASEMODEROLEPLAYMESSAGE_H_
#define ENTERTICKETPURCHASEMODEROLEPLAYMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"

class EnterTicketPurchaseModeRoleplayMessage : public BaseMessage {
public:
    EnterTicketPurchaseModeRoleplayMessage() {
		insertShort(0x04);
		insertInt(0x904DAE1A);  // CRC
        insertAscii("corellia");
        insertAscii("Coronet Starport");
        insertByte(0);
    }
};

#endif /*ENTERTICKETPURCHASEMODEROLEPLAYMESSAGE_H_*/
