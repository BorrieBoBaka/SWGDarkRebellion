#ifndef BORUTIL_H_
#define BORUTIL_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "templates/customization/CustomizationIdManager.h"


#include "server/db/ServerDatabase.h"

class BorUtil : public Logger {
public:

    static void SaveStructureContents(CreatureObject* creature, String name) {
        if(creature->getZoneServer() == nullptr)
			return;
        ManagedReference<SceneObject*> rootParent = creature->getRootParent();

        if(rootParent == nullptr) {
            //Inform the player they're not in a structure, the dummy.
            creature->sendSystemMessage("You are not currently in a structure.");
            return;
        }        

        if(rootParent->isBuildingObject()) {
            BuildingObject* building = cast<BuildingObject*>( rootParent.get());

            StringBuffer text;
            text << "--Prefab created by " << creature->getFirstName() << endl;
            text << "--Intended for Building Template: " << building->getObjectTemplate()->getFullTemplateString() << endl;
            text << "prefab = {" << endl;

            

            for (int i = 1; i <= building->getTotalCellNumber(); ++i) {
                ManagedReference<CellObject*> cell = building->getCell(i);

		        int containerSize = cell->getContainerObjectsSize();

                

	            for (int j = containerSize - 1; j >= 0; --j) {

                    ReadLocker rlocker(cell->getContainerLock());

	            	ManagedReference<SceneObject*> item = cell->getContainerObject(j);

                    rlocker.release();

	            	if (building->containsChildObject(item))
	            		continue;

	            	if (item->isCreatureObject())
	            		continue;

                    if (item->isVendor())
	            		continue;

	            	//Format String
                    //Template, Cell, X, Z, Y, RotationX, RotationZ, RotationY, CustomName
                    String templateFile = item->getObjectTemplate()->getFullTemplateString();

                    if(templateFile.contains("terminal_player_structure"))
                        continue;
                    
                    Vector3 cellPosition = item->getPosition();
					const Quaternion* dir = item->getDirection();

                    text << "\t{ \"" << templateFile << "\", \"" << item->getCustomObjectName() << "\", " << i << ", ";
                    text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", ";
                    text << dir->getW() << ", " << dir->getX() << ", " << dir->getY() << ", " << dir->getZ() << " }," << endl;
	            }
	        }

            text << "}" << endl;

            

            if(name.isEmpty())
			    throw Exception();     
            
            File* file = new File("custom_scripts/structure_prefabs/" + name + ".lua");
		    FileWriter* writer = new FileWriter(file, false); // true for appending new lines

            writer->writeLine(text.toString());

            writer->close();
		    delete file;
		    delete writer;

            creature->sendSystemMessage("Prefab saved to bin/custom_scripts/structure_prefabs/" + name + ".lua!");

        } else {
            //Inform the player they're not in a structure, the dummy.
            creature->sendSystemMessage("You are not currently in a structure.");
            return;
        }
	}

    static void LoadStructureContents(CreatureObject* creature, String name) {
        ManagedReference<SceneObject*> rootParent = creature->getRootParent();

        if(rootParent == nullptr) {
            //Inform the player they're not in a structure, the dummy.
            creature->sendSystemMessage("You are not currently in a structure.");
            return;
        } 

        if(rootParent->isBuildingObject()) {
            BuildingObject* building = cast<BuildingObject*>( rootParent.get());
            Lua* lua = DirectorManager::instance()->getLuaInstance();
            lua->runFile("custom_scripts/structure_prefabs/" + name + ".lua");

            LuaObject luaObject = lua->getGlobalObject("prefab");

            if(luaObject.isValidTable()) {
                for (int i = 1; i <= luaObject.getTableSize(); ++i) {
                    LuaObject objData = luaObject.getObjectAt(i);
                    if (objData.isValidTable()) {
                        String objTemplate = objData.getStringAt(1);
                        String objName = objData.getStringAt(2);
                        int objCell = objData.getIntAt(3);
                        float objPosX = objData.getFloatAt(4);
                        float objPosZ = objData.getFloatAt(5);
                        float objPosY = objData.getFloatAt(6);
                        float objDirW = objData.getFloatAt(7);
                        float objDirX = objData.getFloatAt(8);
                        float objDirY = objData.getFloatAt(9);
                        float objDirZ = objData.getFloatAt(10);
                        //creature->sendSystemMessage(objTemplate);

                        Reference<SharedObjectTemplate*> shot = TemplateManager::instance()->getTemplate(objTemplate.hashCode());

                        if (shot == nullptr) {
					        continue;
				        } else if (!shot->isSharedTangibleObjectTemplate()) {
				        	continue;
				        }

                        ManagedReference<TangibleObject*> object = (creature->getZoneServer()->createObject(shot->getServerObjectCRC(), 1)).castTo<TangibleObject*>();

                        if (object == nullptr) {
					        continue;
				        }

				        Locker locker(object);

				        object->createChildObjects();

                        object->setCustomObjectName(objName, true);

                        ManagedReference<CellObject*> cell = building->getCell(objCell);

                        if (cell->transferObject(object, -1, true)) {
                            cell->broadcastObject(object, true);
                            object->setDirection(objDirW, objDirX, objDirY, objDirZ);
                            object->teleport(objPosX, objPosZ, objPosY, object->getParent().get()->getObjectID());					        
				        } else {
					        object->destroyObjectFromDatabase(true);
					        //creature->sendSystemMessage("Error transferring object to cell.");
				        }

                    }
                    objData.pop();
                }
            } else {
                creature->sendSystemMessage("Structure prefab \"" + name + "\" not found.");
                return;
            }

            luaObject.pop();

        } else {
            //Inform the player they're not in a structure, the dummy.
            creature->sendSystemMessage("You are not currently in a structure.");
            return;
        }        
    }

    static void CreateRoleplayNPC(CreatureObject* creature, String baseTemplate, String skillTemplate, String equipmentTemplate, String customizeTemplate) {
        Zone* zone = creature->getZone();

		if (zone == nullptr)
			return;

        float posX = creature->getPositionX(), posY = creature->getPositionY(), posZ = creature->getPositionZ();
		uint64 parID = creature->getParentID();

        CreatureManager* creatureManager = zone->getCreatureManager();

		uint32 templ = baseTemplate.hashCode();

        AiAgent* npc = nullptr;
        npc = cast<AiAgent*>(creatureManager->spawnCreature(templ, 0, posX, posZ, posY, parID));
		if (npc != nullptr) {
            npc->activateLoad("");
        } else {
            creature->sendSystemMessage("could not spawn " + baseTemplate);
		    return;
        }

        Locker clocker(npc, creature);
        npc->updateDirection(Math::deg2rad(creature->getDirectionAngle()));

        if(skillTemplate != "") {
            ApplySkillTemplateToNPC(creature, npc, skillTemplate);
        }

        if(equipmentTemplate != "") {
            ApplyEquipmentTemplateToNPC(creature, npc, equipmentTemplate);
        }

        if(customizeTemplate != "") {
            ApplyCustomizationTemplateToNPC(creature, npc, customizeTemplate);
        }

    }

    static void ApplySkillTemplateToNPC(CreatureObject* creature, CreatureObject* target, String skillTemplate) {
            Lua* lua = DirectorManager::instance()->getLuaInstance();
            lua->runFile("custom_scripts/rp_npcs/skills/" + skillTemplate + ".lua");

            LuaObject luaObject = lua->getGlobalObject("skillSet");

            if(luaObject.isValidTable()) {
                for (int i = 1; i <= luaObject.getTableSize(); ++i) {
                    LuaObject objData = luaObject.getObjectAt(i);
                    if (objData.isValidTable()) {
                        String skillKey = objData.getStringAt(1);
                        int minSkill = objData.getIntAt(2);
                        int maxSkill = objData.getIntAt(3);     
                        //int finalSkill = System::random(maxSkill - minSkill) + 1 + minSkill;
                        int finalSkill = minSkill + System::random(maxSkill - minSkill);
                        target->addSkillMod(SkillModManager::PERMANENTMOD, skillKey, finalSkill);
                    }
                    objData.pop();
                }
            } else {
                creature->sendSystemMessage("Skill Template  \"" + skillTemplate + "\" not found.");
            }
            luaObject.pop();
    } 

    static void ApplyEquipmentTemplateToNPC(CreatureObject* creature, CreatureObject* target, String equipmentTemplate) {
            try {
                Lua* lua = DirectorManager::instance()->getLuaInstance();
                lua->runFile("custom_scripts/rp_npc/equipment/" + equipmentTemplate + ".lua");

                LuaObject luaObject = lua->getGlobalObject("equipment");

                if (target == nullptr || target->getZone() == nullptr || target->getZone()->getCreatureManager() == nullptr) {
                    creature->sendSystemMessage("Target creature was not the correct type; or the zone it exists in does not exist.");
                    luaObject.pop();
                    return;
                }

                if(luaObject.isValidTable()) {
                    for (int i = 1; i <= luaObject.getTableSize(); ++i) {
                        LuaObject objData = luaObject.getObjectAt(i);
                        if (objData.isValidTable()) {

                            ManagedReference<SceneObject*> inventory = target->getSlottedObject("inventory");
                            if (inventory == nullptr) {
                                objData.pop();
                                continue;
                            }

                            String objectTemplate = objData.getStringAt(1);
                            objectTemplate = objectTemplate.replaceAll("shared_", "");
                            Reference<SharedObjectTemplate*> shot = TemplateManager::instance()->getTemplate(objectTemplate.hashCode());

                            if(shot == nullptr) {
                                objData.pop();
                                continue;
                            }

                            TangibleObject* clothing = (target->getZoneServer()->createObject(shot->getServerObjectCRC(), 1)).castTo<TangibleObject*>();

                            if (clothing == nullptr) {
                                objData.pop();
                                continue;
                            }

                            Locker locker(clothing);
                            clothing->createChildObjects();

                            //Add Customization Variables       
                            int fieldSize = objData.getTableSize();
                            int index = 2;
                            
                            while(index + 1 < fieldSize) {

                                String varName = objData.getStringAt(index);

                                int16 value = objData.getIntAt(index + 1);

                                clothing->setCustomizationVariable(varName, value, true);


                                index+=2;
                            }   

                            //Transfer
                            if (inventory->transferObject(clothing, -1, true)) {
                                inventory->broadcastObject(clothing, true);
                            } else {
                                clothing->destroyObjectFromDatabase(true);
                                objData.pop();
                                continue;
                            }

                            //Equip
                            target->getZone()->getCreatureManager()->addWearableItem(target, clothing);

                            
                        }
                        objData.pop();
                    }
                } else {
                    creature->sendSystemMessage("Equipment Template  \"" + equipmentTemplate + "\" not found.");
                }
                luaObject.pop();
            } catch (Exception& e) {
			    // creature->sendSystemMessage("Invalid arguments for RP command. Help: /rp help");
                creature->sendSystemMessage("Error with Equipment: " +  e.getMessage());
		    }   
    } 

    static void SaveEquipmentToTemplate(CreatureObject* creature, const uint64& target, String name) {
        ManagedReference<SceneObject*> object = creature->getZoneServer()->getObject(target, false);

		CreatureObject* targetMob = creature;

		if (object != nullptr) {
			if (object->isCreatureObject()) {
				targetMob = cast<CreatureObject*>(object.get());
			}
		}

        const WearablesDeltaVector* wearablesVector = targetMob->getWearablesDeltaVector();
		int size = wearablesVector->size();

		//int gender = targetMob->getGender();

		StringBuffer text;
        text << "equipment = {" << endl;

        for (int i = 0; i < size; i++) {
            TangibleObject* item = wearablesVector->get(i);
			CustomizationVariables* itemCustomVars = item->getCustomizationVariables();
			String templ = item->getObjectTemplate()->getClientTemplateFileName();
            int itemVarSize = itemCustomVars->getSize();
            text << "\t{\"" << templ << "\", "; 

            for(int j = 0;j<itemVarSize; j++) {
                uint8 key = itemCustomVars->elementAt(j).getKey();
				int16 value = itemCustomVars->elementAt(j).getValue();
				String valueType = CustomizationIdManager::instance()->getCustomizationVariable(key);

                text << "\"" << valueType << "\", " << value << ", ";
            } 

            text << "}," << endl;
        }
        text << "}";

        if(name.isEmpty())
			    throw Exception();     
            
        File* file = new File("custom_scripts/rp_npcs/equipment/" + name + ".lua");
		FileWriter* writer = new FileWriter(file, false); // true for appending new lines

        writer->writeLine(text.toString());

        writer->close();
		delete file;
		delete writer;

        creature->sendSystemMessage("Equipment template saved to bin/custom_scripts/rp_npcs/equipment/" + name + ".lua!");
    }

    static void ApplyCustomizationTemplateToNPC(CreatureObject* creature, CreatureObject* target, String customizeTemplate) {

    } 

    static void SaveCustomizationToTemplate(CreatureObject* creature, const uint64& target, String name) {
        ManagedReference<SceneObject*> object = creature->getZoneServer()->getObject(target, false);

		CreatureObject* targetMob = creature;

		if (object != nullptr) {
			if (object->isCreatureObject()) {
				targetMob = cast<CreatureObject*>(object.get());
			}
		}

        StringBuffer text;
        text << "customization = {" << endl;

        CustomizationVariables* playerCustomVars = targetMob->getCustomizationVariables();

        int playerVarSize = playerCustomVars->getSize();

        for (int k = 0; k < playerVarSize; k++) {
			uint8 key = playerCustomVars->elementAt(k).getKey();
			int16 value = playerCustomVars->elementAt(k).getValue();
			String valueType = CustomizationIdManager::instance()->getCustomizationVariable(key);

            text << "\t{\"" << valueType << "\", " << value << "}," << endl; 
		}

        text << "}";

        if(name.isEmpty())
			    throw Exception();     
            
        File* file = new File("custom_scripts/rp_npcs/customization/" + name + ".lua");
		FileWriter* writer = new FileWriter(file, false); // true for appending new lines

        writer->writeLine(text.toString());

        writer->close();
		delete file;
		delete writer;

        creature->sendSystemMessage("Customization template saved to bin/custom_scripts/rp_npcs/customization/" + name + ".lua!");
    }

    static void PlaceStructureFromTemplate(CreatureObject* creature, String templateFile) {
            ManagedReference<Zone*> zone = creature->getZone();
            if (creature->getParent() != nullptr) {
			    creature->sendSystemMessage("You must be outside to do this");
			    return;
            }

            int angle = creature->getDirectionAngle();
            float x = creature->getPositionX();
	        float y = creature->getPositionY();

            StructureObject* structure = StructureManager::instance()->placeStructure(creature, templateFile, x, y, angle, 1);
            StringBuffer text;
            text << "Structure Placed. Structure ID: " << (structure->getObjectID() / 2);
            creature->sendSystemMessage(text.toString());
    }

    static void TogglePublicContainer(CreatureObject* creature, const uint64& target) {
        ManagedReference<SceneObject*> object;
		if (target != 0) {
			object = creature->getZoneServer()->getObject(target, false);
		} else {
            creature->sendSystemMessage("You must have a target.");
            return;
        }

        if(object != nullptr) {
            int status = object->getStoredInt("public_container");
            if(status != 1) {
                object->setStoredInt("public_container", 1);
                creature->sendSystemMessage("Target is now set to be a publicly accessible container.");
            } else {
                object->deleteStoredInt("public_container");
                creature->sendSystemMessage("Target is no longer set to be a publicly accessible container.");
            }
        } else {
            creature->sendSystemMessage("Invalid target.");
        }
    }

    static void ToggleDispenserContainer(CreatureObject* creature, const uint64& target) {
        ManagedReference<SceneObject*> object;
		if (target != 0) {
			object = creature->getZoneServer()->getObject(target, false);
		} else {
            creature->sendSystemMessage("You must have a target.");
            return;
        }

        if(object != nullptr) {
            int status = object->getStoredInt("dispenser_container");
            if(status != 1) {
                object->setStoredInt("dispenser_container", 1);
                creature->sendSystemMessage("Target is now set to be a dispensing container.");
            } else {
                object->deleteStoredInt("dispenser_container");
                creature->sendSystemMessage("Target is no longer set to be a dispensing container.");
            }
        } else {
            creature->sendSystemMessage("Invalid target.");
        }


    }

};

#endif 