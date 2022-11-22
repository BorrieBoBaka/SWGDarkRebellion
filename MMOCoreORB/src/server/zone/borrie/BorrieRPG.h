#ifndef SOVEREIGNTY_H_
#define SOVEREIGNTY_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "templates/customization/CustomizationIdManager.h"
#include "server/zone/managers/name/NameManager.h"

#include "server/zone/managers/crafting/CraftingManager.h"

#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"

#include "server/ServerCore.h"

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/player/PlayerMap.h"
#include "server/chat/ChatManager.h"

#include "server/login/account/Account.h"

#include "server/zone/objects/creature/sui/SetDMStatusSuiCallback.h"

#include "engine/engine.h"

class BorrieRPG : public Logger {
public:
	static String GetTestString() {
		return "This string confirms the class works.";
	}

	static void BroadcastMessage(CreatureObject* creature, String Message) {
		String nameToUse = creature->getFirstName();
		if(nameToUse == "a" || nameToUse == "an" || nameToUse == "The") nameToUse = creature->getDisplayedName(); 
		UnicodeString message1("[" + nameToUse + "]: " + Message);
		ChatSystemMessage* msg = new ChatSystemMessage(message1, ChatSystemMessage::DISPLAY_CHATANDSCREEN);
		creature->broadcastMessage(msg, true);
	}

	static void BroadcastHoloNetMessage(CreatureObject* creature, String Message) {
		String nameToUse = creature->getFirstName();
		if(nameToUse == "a" || nameToUse == "an" || nameToUse == "The") nameToUse = creature->getDisplayedName(); 
		UnicodeString message1("Alert: \\#00FFFFRecieving HoloNet Broadcast From [\\#FFFF00" + nameToUse + "\\#00FFFF]: \\#FFFFFF" + Message + "\\#.");
		ChatSystemMessage* msg = new ChatSystemMessage(message1, ChatSystemMessage::DISPLAY_CHATANDSCREEN);
		creature->broadcastMessage(msg, true);
	}

	static void BroadcastMessageToArea(CreatureObject* creature, String message) {
		UnicodeString message1(message);
		ChatSystemMessage* msg = new ChatSystemMessage(message1, ChatSystemMessage::DISPLAY_CHATANDSCREEN);
		creature->broadcastMessage(msg, true);
	}

	static void BroadcastRoll(CreatureObject* creature, String rollMessage) {
		String nameToUse = creature->getFirstName();
		if(nameToUse == "a" || nameToUse == "an" || nameToUse == "The") nameToUse = creature->getDisplayedName(); 
		UnicodeString message1("[" + nameToUse + "]: " + rollMessage);
		ChatSystemMessage* msg = new ChatSystemMessage(message1, ChatSystemMessage::DISPLAY_CHATANDSCREEN);
		creature->broadcastMessage(msg, true);
	}

	static void BroadcastRoll(CreatureObject* commander, CreatureObject* creature, String rollMessage) {
		String nameToUse = creature->getFirstName();
		if(nameToUse == "a" || nameToUse == "an" || nameToUse == "The") nameToUse = creature->getDisplayedName(); 
		if(commander != creature) {
			UnicodeString message1("["+commander->getFirstName()+"] for [" + nameToUse + "]: " + rollMessage);
			ChatSystemMessage* msg = new ChatSystemMessage(message1, ChatSystemMessage::DISPLAY_CHATANDSCREEN);
			creature->broadcastMessage(msg, true);
		} else {
			UnicodeString message1("[" + nameToUse + "]: " + rollMessage);
			ChatSystemMessage* msg = new ChatSystemMessage(message1, ChatSystemMessage::DISPLAY_CHATANDSCREEN);
			creature->broadcastMessage(msg, true);
		}		
	}

	static void BroadcastToAdmins(CreatureObject* creature, String msg) {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		if (msg == "") {
			creature->sendSystemMessage("Syntax: /dm call <msg>");
			return;
		}
		ChatManager* chatManager = creature->getZoneServer()->getChatManager();
		Locker chatManagerLocker(chatManager);

		PlayerMap* playerMap = chatManager->getPlayerMap();
		playerMap->resetIterator(false);

		String pName = "[\\#FF0000" + creature->getFirstName() + "\\#.] DM CALL: ";

		creature->sendSystemMessage("Sent DM Call with message: '" + msg + "'");
		creature->sendSystemMessage("\\#00FFFFNOTE: Please be sure not to spam the DM call function. If a DM is available, they will respond to you ASAP.");

		while (playerMap->hasNext(false)) {
			ManagedReference<CreatureObject*> playerCreature = playerMap->getNextValue(false);
			ManagedReference<PlayerObject*> playerObject = playerCreature->getPlayerObject();

			if (playerObject->isPrivileged()) { // TODO: Check to see if a character is a secret DM.
				playerCreature->sendSystemMessage(pName + msg);
			}
		}
	}

	static void ListOnlineCharacters(CreatureObject* creature, bool showAll) {
		ChatManager* chatManager = creature->getZoneServer()->getChatManager();
		PlayerMap* playerMap = chatManager->getPlayerMap();
		int playerCount = chatManager->getPlayerCount();

		String result;

		playerMap->resetIterator(false);

		while (playerMap->hasNext(false)) {
			ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);

			Account* account = playerObject->getPlayerObject()->getAccount();

			String name = playerObject->getFirstName();
			name += playerObject->getLastName() == "" ? "" : " " + playerObject->getLastName();

			if(showAll) {
				result += "\\#FFFF00" + name + "\\#FFFFFF (" + account->getUsername() +") ";
				if(account->getAdminLevel() > 0) {
					result += " Admin: " + String::valueOf(account->getAdminLevel());
				} 
			} else {
				if(playerObject->getFirstName() == "Discord") {
					playerCount--;
					continue;
				}
				if(account->getAdminLevel() > 1) {
					if(playerObject->getStoredString("rp_dm_status") != "")
						result += "\\#FFFF00DM " + name + "\\#FFFFFF Status: " + playerObject->getStoredString("rp_dm_status");
					else 
						playerCount--;
				} else {
					if(!playerObject->getPlayerObject()->isAnonymous() || account->getAdminLevel() < 1 ) {
						result += "\\#FFFF00" + name + "\\#FFFFFF";
					}
				}
			}
			

			result += "\n";
		}

		result = "There are " + String::valueOf(playerCount) + " characters online.\n" + result;

		creature->sendSystemMessage(result);		
	}

	static void ReportPlayerCountToDiscord(CreatureObject* discordBot) {
		Account* account = discordBot->getPlayerObject()->getAccount();
		if(account->getUsername() != "discord" && account->getUsername() != "discord2") return;
		ChatManager* chatManager = discordBot->getZoneServer()->getChatManager();
		PlayerMap* playerMap = chatManager->getPlayerMap();
		int playerCount = chatManager->getPlayerCount() - 1;
		
		int dmCount = 0;

		playerMap->resetIterator(false);

		while (playerMap->hasNext(false)) {
			ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);
			ManagedReference<PlayerObject*> ghost = playerObject->getPlayerObject();
			if(ghost->getAdminLevel() > 1) {
				playerCount--;
				if(playerObject->getStoredString("rp_dm_status") != "") {
					dmCount++;
				}
			}
			
		}

		if(playerCount < 0) playerCount = 0;

		discordBot->sendSystemMessage("who:" + String::valueOf(playerCount) + ":" + String::valueOf(dmCount));
	}

	static void NotifyAdminsAboutPlayerStatus(String name, bool isOnline) {
		ChatManager* chatManager = ServerCore::getZoneServer()->getChatManager();
		PlayerMap* playerMap = chatManager->getPlayerMap();

		playerMap->resetIterator(false);
		while (playerMap->hasNext(false)) {
			ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);
			
			if(playerObject->getStoredInt("dm_alert_incoming") == 1) {
				playerObject->sendSystemMessage("!\\#FFFF00***" + name + (isOnline ? " is now online." : " has gone offline."));
			}
		}
	}

	static void SetDMStatus(CreatureObject* creature) {
		ManagedReference<SuiInputBox*> sui = new SuiInputBox(creature);
		sui->setCallback(new SetDMStatusSuiCallback(creature->getZoneServer()));
		sui->setUsingObject(creature);
		sui->setPromptTitle("Set DM Status"); //Confirm Structure Deletion
		sui->setPromptText("Set your DM Status!");
		sui->setCancelButton(true, "@cancel");
		sui->setMaxInputSize(9999);

		creature->getPlayerObject()->addSuiBox(sui);
		creature->sendMessage(sui->generateMessage());
	}

	/*
	static void ReportOnlineCount(CreatureObject* creature) {
		StringBuffer fetchStatement;
		fetchStatement << "SELECT COUNT(*) FROM rp_characters WHERE isonline = '1'";
		UniqueReference<ResultSet*> fetchedResults(ServerDatabase::instance()->executeQuery(fetchStatement.toString()));
		if (fetchedResults == nullptr) {
			creature->sendSystemMessage("An error occured. Could not get online count. (ERROR:1)");
		} else {
			if (fetchedResults->next()) {
				String count = fetchedResults->getString(0);
				creature->sendSystemMessage("Current Online Players: " + count + ".");
				// TODO: Want to retrieve more information and inform them of statuses.
			} else {
				creature->sendSystemMessage("An error occured. Could not get online count. (ERROR:2)");
			}
		}
	} 
	*/

	static int GetChatTypeID(String chatType) {
		if (chatType == "say")
			return 0;
		else if (chatType == ".")
			return 0;
		else if (chatType == "add")
			return 2;
		else if (chatType == "admit")
			return 3;
		else if (chatType == "announce")
			return 4;
		else if (chatType == "answer")
			return 5;
		else if (chatType == "argue")
			return 6;
		else if (chatType == "assert")
			return 7;
		else if (chatType == "avow")
			return 8;
		else if (chatType == "babble")
			return 9;
		else if (chatType == "beg")
			return 10;
		else if (chatType == "bellow")
			return 11;
		else if (chatType == "blab")
			return 12;
		else if (chatType == "bleat")
			return 13;
		else if (chatType == "blurt")
			return 14;
		else if (chatType == "boast")
			return 15;
		else if (chatType == "brag")
			return 16;
		else if (chatType == "carol")
			return 17;
		else if (chatType == "chant")
			return 18;
		else if (chatType == "chat")
			return 19;
		else if (chatType == "chatter")
			return 20;
		else if (chatType == "command")
			return 21;
		else if (chatType == "complain")
			return 22;
		else if (chatType == "concede")
			return 23;
		else if (chatType == "conclude")
			return 24;
		else if (chatType == "confess")
			return 25;
		else if (chatType == "confide")
			return 26;
		else if (chatType == "coo")
			return 27;
		else if (chatType == "debate")
			return 28;
		else if (chatType == "declare")
			return 29;
		else if (chatType == "decree")
			return 30;
		else if (chatType == "demand")
			return 31;
		else if (chatType == "describe")
			return 32;
		else if (chatType == "disclose")
			return 33;
		else if (chatType == "divulge")
			return 34;
		else if (chatType == "drawl")
			return 35;
		else if (chatType == "drivel")
			return 36;
		else if (chatType == "drone")
			return 37;
		else if (chatType == "emote")
			return 38;
		else if (chatType == ":")
			return 38;
		else if (chatType == "eulogize")
			return 39;
		else if (chatType == "exclaim")
			return 40;
		else if (chatType == "explain")
			return 41;
		else if (chatType == "fortell")
			return 42;
		else if (chatType == "gab")
			return 43;
		else if (chatType == "gossip")
			return 44;
		else if (chatType == "howl")
			return 45;
		else if (chatType == "huff")
			return 46;
		else if (chatType == "hypothesize")
			return 47;
		else if (chatType == "indicate")
			return 48;
		else if (chatType == "inquire")
			return 49;
		else if (chatType == "interject")
			return 50;
		else if (chatType == "interrupt")
			return 51;
		else if (chatType == "intone")
			return 52;
		else if (chatType == "jabber")
			return 53;
		else if (chatType == "jaw")
			return 54;
		else if (chatType == "jest")
			return 55;
		else if (chatType == "lecture")
			return 56;
		else if (chatType == "lisp")
			return 57;
		else if (chatType == "moan")
			return 58;
		else if (chatType == "mouth")
			return 59;
		else if (chatType == "mumble")
			return 60;
		else if (chatType == "muse")
			return 61;
		else if (chatType == "note")
			return 62;
		else if (chatType == "parrot")
			return 63;
		else if (chatType == "plead")
			return 64;
		else if (chatType == "prattle")
			return 65;
		else if (chatType == "preach")
			return 66;
		else if (chatType == "proclaim")
			return 67;
		else if (chatType == "promise")
			return 68;
		else if (chatType == "pronounce")
			return 69;
		else if (chatType == "prophesize")
			return 70;
		else if (chatType == "propose")
			return 71;
		else if (chatType == "quote")
			return 72;
		else if (chatType == "ramble")
			return 73;
		else if (chatType == "rap")
			return 74;
		else if (chatType == "recite")
			return 75;
		else if (chatType == "respond")
			return 76;
		else if (chatType == "retort")
			return 77;
		else if (chatType == "riddle")
			return 78;
		else if (chatType == "scream")
			return 79;
		else if (chatType == "shout")
			return 80;
		else if (chatType == "shrill")
			return 81;
		else if (chatType == "sing")
			return 82;
		else if (chatType == "slur")
			return 83;
		else if (chatType == "social")
			return 84;
		else if (chatType == "state")
			return 85;
		else if (chatType == "stutter")
			return 86;
		else if (chatType == "suppose")
			return 87;
		else if (chatType == "surmise")
			return 88;
		else if (chatType == "swear")
			return 89;
		else if (chatType == "tattle")
			return 90;
		else if (chatType == "theorize")
			return 91;
		else if (chatType == "think")
			return 92;
		else if (chatType == "threaten")
			return 93;
		else if (chatType == "utter")
			return 94;
		else if (chatType == "vent")
			return 95;
		else if (chatType == "vow")
			return 96;
		else if (chatType == "wail")
			return 97;
		else if (chatType == "whine")
			return 98;
		else if (chatType == "whisper")
			return 99;
		else if (chatType == "yack")
			return 100;
		else if (chatType == "yell")
			return 101;
		else if (chatType == "yelp")
			return 102;
		else
			return -1;
	}

	static void copyTarget(CreatureObject* creature, SceneObject* target, bool overrideFlag = false) {
		if(target == nullptr) return;
		ManagedReference<TangibleObject*> tanoTarget = target->asTangibleObject();
		String objectTemplate = target->getObjectTemplate()->getFullTemplateString();
		objectTemplate = objectTemplate.replaceAll("shared_", "");
		creature->sendSystemMessage("Cloning Object: " + objectTemplate);
		ManagedReference<CraftingManager*> craftingManager = creature->getZoneServer()->getCraftingManager();
		if (!objectTemplate.contains("object/tangible") && !objectTemplate.contains("object/weapon")) {
			creature->sendSystemMessage("Templates must be a tangible or weapon object.");
			return;
		}
		if (craftingManager == nullptr) {
			return;
		}
		Reference<SharedObjectTemplate*> shot = TemplateManager::instance()->getTemplate(objectTemplate.hashCode());
		if (shot == nullptr || !shot->isSharedTangibleObjectTemplate()) {
			creature->sendSystemMessage("Templates must be tangible objects, or descendants of tangible objects, only.");
			return;
		}
		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");
		if (inventory == nullptr || inventory->isContainerFullRecursive()) {
			creature->sendSystemMessage("Your inventory is full, so the item could not be created.");
			return;
		}
		ManagedReference<TangibleObject*> object = (creature->getZoneServer()->createObject(shot->getServerObjectCRC(), 1)).castTo<TangibleObject*>();
		if (object == nullptr) {
			creature->sendSystemMessage("The object '" + objectTemplate + "' could not be created because the template could not be found.");
			return;
		}

		if (!object->isCopyable()) {
			if (!overrideFlag) {
				creature->sendSystemMessage("You are not able to copy this object.");
				return;
			}
		}
		Locker locker(object);
		object->createChildObjects();

		// Set Crafter name and generate serial number
		String name = "Unknown";
		object->setCraftersName(name);
		String serial = craftingManager->generateSerial();
		object->setSerialNumber(serial);

		//Copy Customization Values
		if(tanoTarget != nullptr) {
			CustomizationVariables* itemCustomVars = tanoTarget->getCustomizationVariables();
        	int itemVarSize = itemCustomVars->getSize();

        	for(int j = 0;j<itemVarSize; j++) {
            	uint8 key = itemCustomVars->elementAt(j).getKey();
		    	int16 value = itemCustomVars->elementAt(j).getValue();
		    	String valueType = CustomizationIdManager::instance()->getCustomizationVariable(key);
				object->setCustomizationVariable(valueType, value, true);
        	} 
		}
		

		if (inventory->transferObject(object, -1, true)) {
			inventory->broadcastObject(object, true);
		} else {
			object->destroyObjectFromDatabase(true);
			creature->sendSystemMessage("Error transferring object to inventory.");
		}
	}

	static void DeleteCreature(CreatureObject* creature) {
		if(creature != nullptr) {
			if(creature->isAiAgent()) {
				ManagedReference<AiAgent*> agent = creature->asAiAgent();
				Locker locker(agent);
				agent->scheduleDespawn(1);
			}
		}
	}

	static void setCopyable(CreatureObject* creature, SceneObject* target) {
		ManagedReference<TangibleObject*> tano = target->asTangibleObject();
		if (tano != nullptr) {
			bool wasCopyable = tano->isCopyable();
			tano->setCopyable(!wasCopyable);
			if (wasCopyable)
				creature->sendSystemMessage("Target no longer copyable");
			else
				creature->sendSystemMessage("Target is now copyable.");
		} else {
			creature->sendSystemMessage("Error: Target is not tangible.");
		}
	}

	static void IncreaseLots(CreatureObject* creature, int num) {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		ghost->setMaximumLots(num + 10);
	}

	static void teleportObject(CreatureObject* creature, SceneObject* object, float x, float z, float y, long parent = -1) {
		if (object == nullptr) {
			creature->sendSystemMessage("You need an object targeted in order to teleport it.");
			throw Exception();
		}
		ManagedReference<SceneObject*> objParent = object->getParent().get();
		if(parent == -1) {
			if (objParent != nullptr)
				object->teleport(x, z, y, objParent->getObjectID());
			else
				object->teleport(x, z, y);
		} else if(parent == -2) {
			object->teleport(x, z, y);
		} else {
			object->teleport(x, z, y, parent);
		}
		
	}

	static void colorTarget(CreatureObject* creature, SceneObject* object, int paletteType, int index) {
		String appearanceFilename = object->getObjectTemplate()->getAppearanceFilename();
		VectorMap<String, Reference<CustomizationVariable*>> variables;
		AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);

		String palette;

		if (paletteType == 1) {
			palette = variables.elementAt(0).getKey();
		} else if (paletteType == 2) {
			palette = variables.elementAt(1).getKey();
		} else if (paletteType == 3) {
			palette = variables.elementAt(2).getKey();
		} else
			palette = variables.elementAt(0).getKey();

		ManagedReference<TangibleObject*> armorRehueTano = object->asTangibleObject();
		if (armorRehueTano != nullptr) {
			Locker locker(armorRehueTano, creature);

			armorRehueTano->setCustomizationVariable(palette, index, true);
		}
	}

	static void SaveTarget(CreatureObject* creature, SceneObject* target) {
		creature->setLocalData("storedtarget", String::valueOf(target->getObjectID()));
		creature->sendSystemMessage("Stored Target: " + target->getDisplayedName() + ". This target will attack whoever you have targeted.");
	}

	static void SetName(CreatureObject* creature, SceneObject* object, String newName) {
		if (object->isPlayerObject()) {
			creature->sendSystemMessage("ERROR: Cannot name players.");
			throw Exception();
		}
		object->setCustomObjectName(newName, true);
	}

	static void ToggleJediState(CreatureObject* dm, CreatureObject* target) {

	}

	static void SetRandomName(CreatureObject* creature, SceneObject* object, String nameType) {
		if (object->isPlayerObject()) {
			if(creature != nullptr)
				creature->sendSystemMessage("ERROR: Cannot name players.");
			throw Exception();
		}

		NameManager* nm = creature->getZoneProcessServer()->getNameManager();

		String result = "a Stranger";

		if(nameType == "stormtrooper") {
			result = nm->makeCreatureName(NameManagerType::STORMTROOPER, CreatureObject::HUMAN);
		} else if (nameType == "scouttrooper") {
			result = nm->makeCreatureName(NameManagerType::SCOUTTROOPER, CreatureObject::HUMAN);
		} else if (nameType == "darktrooper") {
			result = nm->makeCreatureName(NameManagerType::DARKTROOPER, CreatureObject::HUMAN);
		} else if (nameType == "swamptrooper") {
			result = nm->makeCreatureName(NameManagerType::SWAMPTROOPER, CreatureObject::HUMAN);
		} else if(nameType == "r2") {
			result = nm->makeCreatureName(NameManagerType::R2, CreatureObject::HUMAN);
		} else if(nameType == "r3") {
			result = nm->makeCreatureName(NameManagerType::R3, CreatureObject::HUMAN);
		} else if(nameType == "r4") {
			result = nm->makeCreatureName(NameManagerType::R4, CreatureObject::HUMAN);
		} else if(nameType == "r5") {
			result = nm->makeCreatureName(NameManagerType::R5, CreatureObject::HUMAN);
		} else if(nameType == "r6") {
			result = "R6-A1";
		} else if(nameType == "r7") {
			result = "R7-A1";
		} else if(nameType == "r8") {
			result = "R8-A1";
		} else if(nameType == "r9") {
			result = "R9-A1";
		} else if(nameType == "3po" || nameType == "3p0") {
			result = nm->makeCreatureName(NameManagerType::DROID_3P0, CreatureObject::HUMAN);
		} else if(nameType == "eg6") {
			result = nm->makeCreatureName(NameManagerType::DROID_EG6, CreatureObject::HUMAN);
		} else if(nameType == "wed") {
			result = nm->makeCreatureName(NameManagerType::DROID_WED, CreatureObject::HUMAN);
		} else if(nameType == "le") {
			result = nm->makeCreatureName(NameManagerType::DROID_LE, CreatureObject::HUMAN);
		} else if(nameType == "ra7") {
			result = nm->makeCreatureName(NameManagerType::DROID_RA7, CreatureObject::HUMAN);
		} else if(nameType == "human") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::HUMAN);
		} else if(nameType == "rodian") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::RODIAN);
		} else if(nameType == "trandoshan" || nameType == "doshan") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::TRANDOSHAN);
		} else if(nameType == "moncal") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::MONCAL);
		} else if(nameType == "wookiee") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::WOOKIE);
		} else if(nameType == "bothan") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::BOTHAN);
		} else if(nameType == "twilek" || nameType == "twi'lek") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::TWILEK);
		} else if(nameType == "zabrak") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::ZABRAK);
		} else if(nameType == "ithorian") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::ITHORIAN);
		} else if(nameType == "sullustan") {
			result = nm->makeCreatureName(NameManagerType::GENERIC, CreatureObject::SULLUSTAN);
		} else {
			if(creature != nullptr)
				creature->sendSystemMessage("No valid name group type for: " + nameType);
			throw Exception();
		}

		object->setCustomObjectName(result, true);
	}

	static void ShowAllStructures(CreatureObject* creature) {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		StringBuffer body;
		body << "Structures:" << endl;

		for (int i = 0; i < ghost->getTotalOwnedStructureCount(); i++) {
			ManagedReference<StructureObject*> structure = creature->getZoneServer()->getObject(ghost->getOwnedStructure(i)).castTo<StructureObject*>();

			int num = i + 1;
			body << endl << String::valueOf(num) << ". ";

			if (structure == nullptr) {
				body << "NULL Structure" << endl;
				continue;
			}

			body << "Name: " << structure->getCustomObjectName().toString() << endl;
			body << "ID: " << String::valueOf(structure->getObjectID()) << endl;
			body << "    Type: " << structure->getObjectNameStringIdName() << endl;
			body << "    Lots: " << String::valueOf(structure->getLotSize()) << endl;
			body << "    Maintenance Pool: " << String::valueOf(structure->getSurplusMaintenance()) << " credits" << endl;
			body << "    Maintenance Rate: " << String::valueOf(structure->getMaintenanceRate()) << " credits/hr" << endl;

			if (structure->getBasePowerRate() > 0) {
				body << "    Power Reserves: " << String::valueOf(structure->getSurplusPower()) << " units" << endl;
				body << "    Power Consumption: " << String::valueOf(structure->getBasePowerRate()) << " units/hr" << endl;
			}

			body << "    Planet: ";
			Zone* zone = structure->getZone();
			if (zone == nullptr) {
				body << "NULL" << endl;
			} else {
				body << zone->getZoneName() << endl;
				body << "    World Position: " << structure->getWorldPositionX() << ", " << structure->getWorldPositionY() << endl;
			}
			body << endl;
			// if(structure->getObjectID() == 562949976002063) {
			//    structure->destroyObjectFromDatabase(true);
			//}
		}

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);
		box->setPromptTitle("Structures");
		box->setPromptText(body.toString());
		ghost->addSuiBox(box);
		creature->sendMessage(box->generateMessage());
	}

	static SceneObject* GetStoredObject(CreatureObject* creature) {
		String data = creature->getLocalData("storedtarget");
		if (data != "XXERRORXX") {
			return creature->getZoneServer()->getObject(Long::unsignedvalueOf(data));
		} else
			return nullptr;
	}

	static CreatureObject* GetStoredCreature(CreatureObject* dm) {
		ManagedReference<SceneObject*> object = GetStoredObject(dm);
		if (object != nullptr) {
			if (object->isCreatureObject()) {
				return object->asCreatureObject();
			} else
				return dm;
		} else
			return dm;
	}

	static void ModifyLocalVariable(CreatureObject* modder, CreatureObject* target, String var, int mod) {
		String rawVar = target->getLocalData(var);
		int defaultValue = rawVar == "XXERRORXX" ? 0 : Integer::valueOf(rawVar);
		target->setLocalData(var, String::valueOf(defaultValue + mod));
		modder->sendSystemMessage("Edited " + var + " variable on target to " + String::valueOf(defaultValue + mod) + " (Changing by: " + String::valueOf(mod) +
								  ")");
	}

	
	static String GetPosNegSymbol(int Num) {
		if (Num > -1)
			return "+";
		else
			return "";
	}

	static String Capitalize(String input) {
		return input.subString(0, 1).toUpperCase() + input.subString(1, input.length());
	}

};

#endif /*SOVEREIGNTY_H_*/