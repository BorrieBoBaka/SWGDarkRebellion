#ifndef BORCHAT_H_
#define BORCHAT_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/chat/ChatRoomMessage.h"

//#include "templates/roleplay/RoleplayManager.h"

#include "server/chat/ChatManager.h"
#include "server/zone/borrie/BorrieRPG.h"
#include "server/chat/room/ChatRoom.h"



class BorChat : public Logger {
public:
    static void RateOutgoingMessage(CreatureObject* target, const UnicodeString& message) {
        if(target->isPlayerCreature()) {
            int messageLength = 0;
            int score = 0;
            if(messageLength >= 3 && messageLength < 10) {
                score = 1;
            } else if(messageLength >= 10 && messageLength < 25) {
                score = 2;
            } else if(messageLength >= 25 && messageLength < 50) {
                score = 3;
            } else if(messageLength >= 100 && messageLength < 150) {
                score = 4;
            } else if(messageLength >= 150) {
                score = 5;
            }

            int existingScore = target->getStoredInt("exp_chat_score");
            int finalScore = 0;
            if(existingScore + score >= 50) {
                finalScore = 50;
            } else {
                finalScore = existingScore + score;
            }

            target->setStoredInt("exp_chat_score", finalScore);
        } 
    }

    static void PrintSpatialChatToDMs(CreatureObject* target, const UnicodeString& message) {
        ChatManager* chatManager = target->getZoneServer()->getChatManager();
        ChatRoom* obsvRoom = chatManager->getChatRoomByFullPath("SWG.Dark Rebellion.Chat.observer");
	    if(obsvRoom != nullptr) {
		    obsvRoom->broadcastMessage(new ChatRoomMessage(target->getFirstName(), target->getZoneServer()->getGalaxyName(), message, obsvRoom->getRoomID()));
	    }	
    }

    static void PrintSpatialChatToDiscord(CreatureObject* target, const UnicodeString& message, String spatialChatType, short range) {
        ChatManager* chatManager = target->getZoneServer()->getChatManager();
        ChatRoom* obsvRoom = chatManager->getChatRoomByFullPath("SWG.Dark Rebellion.Chat.global");
        if(range < 30)
            return;

        bool anonymous = false;
        if(target->isPlayerCreature()) {
            anonymous = target->getPlayerObject()->isAnonymous();
        }

        String name = target->getFirstName();
        String lastName = target->getLastName();
        if(lastName != "") {
            name += " " + lastName;
        }

        if(!anonymous) {
            obsvRoom->broadcastMessage(new ChatRoomMessage(name, target->getZoneServer()->getGalaxyName(), UnicodeString(spatialChatType + "|") + message, obsvRoom->getRoomID(), false));
        }
    }

    static void PrintDMMessageToDiscord(CreatureObject* target, const UnicodeString& message) {
        ChatManager* chatManager = target->getZoneServer()->getChatManager();
        ChatRoom* obsvRoom = chatManager->getChatRoomByFullPath("SWG.Dark Rebellion.Chat.global");

        obsvRoom->broadcastMessage(new ChatRoomMessage("DM " + target->getFirstName(), target->getZoneServer()->getGalaxyName(), "DM|" + message, obsvRoom->getRoomID(), false));
    }
};

#endif /*BORCHAT_H_*/