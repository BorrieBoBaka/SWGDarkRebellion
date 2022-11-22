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

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "templates/customization/CustomizationIdManager.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "templates/manager/TemplateManager.h"

#include "server/db/ServerDatabase.h"

#include "server/zone/borrie/BorrieRPG.h"

#include "server/zone/managers/director/DirectorManager.h"

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

    static CreatureObject* CreateTemplatedRoleplayNPC(CreatureObject* creature, String rtemplate, String conversationTemplate = "") {
        float posX = creature->getPositionX(), posY = creature->getPositionY(), posZ = creature->getPositionZ();
		uint64 parID = creature->getParentID();
        return CreateTemplatedRoleplayNPC(rtemplate, posX, posZ, posY, parID, creature->getZone()->getZoneName(), conversationTemplate);
    }

    static CreatureObject* CreateTemplatedRoleplayNPC(String rtemplate, float x, float z, float y, long parentID, String zoneID, String conversationTemplate = "") {
        Lua* lua = DirectorManager::instance()->getLuaInstance();

        if(!lua->runFile("custom_scripts/rp_npcs/templates/" + rtemplate + ".lua")) {
            return nullptr;
        }

        //Read Template
        LuaObject templateData = lua->getGlobalObject("npc_template");

        lua_State* L = templateData.getLuaState();

        if (!templateData.isValidTable())
		    return nullptr;

        int i = 0;

        //Variables to set
        Vector<String>* baseTemplate = new Vector<String>();
        Vector<String>* skillTemplate = new Vector<String>();
        VectorMap<String, Vector<String>*> equipmentTemplate;
        VectorMap<String, Vector<String>*> customizationTemplate;

        String name;
        String randomName;
        String title;

        Vector<String>* customizationOverrideNames = new Vector<String>();
        Vector<int>* customizationOverrideValues = new Vector<int>();

        equipmentTemplate.setNoDuplicateInsertPlan();
	    equipmentTemplate.setNullValue(0);

        customizationTemplate.setNoDuplicateInsertPlan();
	    customizationTemplate.setNullValue(0);

        auto logger = StackTrace::getLogger();

        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
		    int type = lua_type(L, -2);

		    if (type == LUA_TSTRING) {
		    	size_t len = 0;
		    	const char* rawVarName = lua_tolstring(L, -2, &len);

                const String& varName = rawVarName;

		    	//parseVariableData(varName, templateData);
                //Parse Data
                lua_State* state = templateData.getLuaState();
                if(varName == "name") {
                    name = Lua::getStringParameter(state);
                } else if(varName == "title") {
                    title = Lua::getStringParameter(state);
                } else if(varName == "randomName") {
                    randomName = Lua::getStringParameter(state);
                } else if(varName == "baseTemplates") {
                    LuaObject baseTemplatesList(state);
                    for (int x = 1; x <= baseTemplatesList.getTableSize(); ++x) {
			            baseTemplate->add(baseTemplatesList.getStringAt(x));
		            }
		            baseTemplatesList.pop();
                } else if(varName == "skillTemplates") {
                    LuaObject skillTemplatesList(state);
                    for (int x = 1; x <= skillTemplatesList.getTableSize(); ++x) {
			            skillTemplate->add(skillTemplatesList.getStringAt(x));
		            }
		            skillTemplatesList.pop();
                } else if(varName == "equipmentTemplates") {
                    LuaObject etemp(state);
                    for(int x = 1;x<=etemp.getTableSize();++x) {
			            LuaObject rootTemp = etemp.getObjectAt(x);
                        String baseTemp = rootTemp.getStringAt(1);
                        LuaObject templateList = rootTemp.getObjectAt(2);
                        Vector<String>* tmpVector = new Vector<String>();
                        for(int y = 1;y<=templateList.getTableSize();++y) {
                            String v = templateList.getStringAt(y);
                            tmpVector->add(v);
                            //logger->info(true) << "Equipment for: " << baseTemp << ", " << v;
                        }

                        equipmentTemplate.put(baseTemp, tmpVector);
                        rootTemp.pop();
                        templateList.pop();
                    }
                    etemp.pop();
                } else if(varName == "customizationTemplates") {
                    LuaObject etemp(state);
                    for(int x = 1;x<=etemp.getTableSize();++x) {
			            LuaObject rootTemp = etemp.getObjectAt(x);
                        String baseTemp = rootTemp.getStringAt(1);
                        LuaObject templateList = rootTemp.getObjectAt(2);
                        Vector<String>* tmpVector = new Vector<String>();
                        for(int y = 1;y<=templateList.getTableSize();++y) {
                            String v = templateList.getStringAt(y);
                            tmpVector->add(v);
                            //logger->info(true) << "Customization for: " << baseTemp << ", " << v;
                        }
                        
                        customizationTemplate.put(baseTemp, tmpVector);
                        rootTemp.pop();
                        templateList.pop();
                    }
                    etemp.pop();
                } else if(varName == "customVarOverrides") {
                    LuaObject cvaro(state);
                    for (int x = 1; x <= cvaro.getTableSize(); ++x) {
                        lua_rawgeti(state, -1, x);
			            LuaObject var(state);
                        String cvarName = var.getStringAt(1);
			            int cvarValue = var.getIntAt(2);

                        //customizationOverrides.put(cvarName, cvarValue);
                        customizationOverrideNames->add(cvarName);
                        customizationOverrideValues->add(cvarValue);

                        var.pop();
                    }
                    cvaro.pop();
                } else {
                    templateData.pop();
                }
		    } else
		    	lua_pop(L, 1);
		    ++i;
	    }


        int roll = 0;
        String finalBaseTemplate = "rp_bothan_male";
        String finalSkillTemplate = "default";
        String finalEquipmentTemplate = "default";
        String finalCustomizationTemplate = "random";

        //Create NPC
        if(baseTemplate != nullptr) {
            if(baseTemplate->size() > 0) {
                roll = System::random(baseTemplate->size() - 1);
                if(baseTemplate->size() > roll)
                    finalBaseTemplate = baseTemplate->get(roll);
            }
        }

        
        //logger->info(true) << finalBaseTemplate;
        
        if(skillTemplate != nullptr) {
            if(skillTemplate->size() > 0) {
                roll = System::random(skillTemplate->size() - 1);
                if(skillTemplate->size() > roll)
                    finalSkillTemplate = skillTemplate->get(roll);
            } 
        }

        //logger->info(true) << finalSkillTemplate;
               
        if(equipmentTemplate.size() > 0) {
            if(equipmentTemplate.contains(finalBaseTemplate)) {
                if(equipmentTemplate.get(finalBaseTemplate)->size() > 0) {
                    roll = System::random(equipmentTemplate.get(finalBaseTemplate)->size() - 1);
                    if(equipmentTemplate.get(finalBaseTemplate)->size() > roll)
                        finalEquipmentTemplate = equipmentTemplate.get(finalBaseTemplate)->get(roll);
                }
            }            
        }

        //logger->info(true) << finalEquipmentTemplate;
        
        if(customizationTemplate.size() > 0) {
            if(customizationTemplate.contains(finalBaseTemplate)) {
                if(customizationTemplate.get(finalBaseTemplate)->size() > 0) {
                    roll = System::random(customizationTemplate.get(finalBaseTemplate)->size() - 1);
                    if(customizationTemplate.get(finalBaseTemplate)->size() > roll)
                        finalCustomizationTemplate = customizationTemplate.get(finalBaseTemplate)->get(roll);
                }            
            }  
        }
              
        //logger->info(true) << finalCustomizationTemplate;

        finalBaseTemplate = "object/mobile/" + finalBaseTemplate + ".iff"; 

        String rootTemplateForSpawn = "rp_base_npc";

        if(conversationTemplate != "") {
            rootTemplateForSpawn = "rp_convo_npc";
        }

        AiAgent* npc = nullptr;
        npc = cast<AiAgent*>(CreateRoleplayNPC(rootTemplateForSpawn, finalBaseTemplate, x, z, y, parentID, zoneID, finalSkillTemplate, finalEquipmentTemplate, finalCustomizationTemplate));

        if(npc == nullptr)
            return nullptr;

        Locker clocker(npc);

        String finalName = name;

        if(randomName != "") {
            BorrieRPG::SetRandomName(npc, npc, randomName);
            finalName = npc->getCustomObjectName().toString();
        }

        if(title != "") {
            finalName += " (" + title + ")";
        }
        
        npc->setCustomObjectName(finalName, true);

        //Set Overrides
        for(int c = 0;c<customizationOverrideNames->size();c++) {
            String cvarName = customizationOverrideNames->get(c);
            int cvarValue = customizationOverrideValues->get(c);
            if(cvarName == "height") {
                //float height = objData.getFloatAt(2);
                npc->setHeight((float)cvarValue, true);
            } else {
                //int16 value = objData.getIntAt(2);
                npc->setCustomizationVariable(cvarName, cvarValue, true);
            } 
        }

        if(conversationTemplate != "") {
            npc->setConvoTemplate(conversationTemplate);
            npc->setStoredString("rp_convo_template", conversationTemplate);
        } 

        return npc;
    }

    static CreatureObject* CreateRoleplayNPC(CreatureObject* creature, String baseTemplate, String skillTemplate, String equipmentTemplate, String customizeTemplate, String conversationTemplate = "") {
        float posX = creature->getPositionX(), posY = creature->getPositionY(), posZ = creature->getPositionZ();
		uint64 parID = creature->getParentID();

        /*
        //Null Checks for Modifiers
        if(skillTemplate != "") {
            if(skillTemplate != "random_low" || skillTemplate != "random_mid" || skillTemplate != "random_high") {
                File* file = new File("custom_scripts/rp_npcs/skills/" + skillTemplate + ".lua");
                if(!file->exists()) {
                    creature->sendSystemMessage("ERROR: The provided skill template of \"" + skillTemplate + "\" does not exist.");
                    delete file;
                    return nullptr;
                }
                delete file;
            }
        }

        if(equipmentTemplate != "") {
            if(equipmentTemplate != "random") {
                File* file = new File("custom_scripts/rp_npcs/equipment/" + equipmentTemplate + ".lua");
                if(!file->exists()) {
                    creature->sendSystemMessage("ERROR: The provided equipment template of \"" + equipmentTemplate + "\" does not exist.");
                    delete file;
                    return nullptr;
                }
                delete file;
            }
        }

        if(customizeTemplate != "") {
            if(customizeTemplate != "random") {
                File* file = new File("custom_scripts/rp_npcs/customization/" + customizeTemplate + ".lua");
                if(!file->exists()) {
                    creature->sendSystemMessage("ERROR: The provided customization template of \"" + customizeTemplate + "\" does not exist.");
                    delete file;
                    return nullptr;
                }
                delete file;
            }
        }
        */
        return CreateRoleplayNPC("rp_base_npc", baseTemplate, posX, posZ, posY, parID, creature->getZone()->getZoneName(), skillTemplate, equipmentTemplate, customizeTemplate, conversationTemplate);

    }

    static CreatureObject* CreateRoleplayNPC(String baseTemplate, String appearanceTemplate, float x, float z, float y, long parentID, String zoneid, String skillTemplate, String equipmentTemplate, String customizeTemplate, String conversationTemplate = "") {
        ZoneServer* zoneServer = ServerCore::getZoneServer();

	    Zone* zone = zoneServer->getZone(zoneid);

        CreatureManager* creatureManager = zone->getCreatureManager();

        uint32 templ = baseTemplate.hashCode();
        uint32 appr = appearanceTemplate.hashCode();

        AiAgent* npc = nullptr;
        npc = cast<AiAgent*>(creatureManager->spawnCreature(templ, appr, x, z, y, parentID));
		if (npc != nullptr) {
            npc->activateLoad("");
        } else {
            //creature->sendSystemMessage("could not spawn " + baseTemplate);
		    return nullptr;
        }

        Locker clocker(npc);
        //npc->updateDirection(Math::deg2rad(creature->getDirectionAngle()));

        if(conversationTemplate != "") {
            npc->setConvoTemplate(conversationTemplate);
            npc->setStoredString("rp_convo_template", conversationTemplate);
        }        

        if(skillTemplate != "") {
            ApplySkillTemplateToNPC(npc, npc, skillTemplate);
            npc->setStoredString("rp_skill_template", skillTemplate);
        }

        if(equipmentTemplate != "") {
            ApplyEquipmentTemplateToNPC(npc, npc, equipmentTemplate);
            npc->setStoredString("rp_equip_template", equipmentTemplate);
        }

        if(customizeTemplate != "" && customizeTemplate != "random") {
            ApplyCustomizationTemplateToNPC(npc, npc, customizeTemplate);
            npc->setStoredString("rp_custom_template", customizeTemplate);
        } else if(customizeTemplate == "random") {
            ApplyRandomCustomizationToNPC(npc,npc);
            npc->setStoredString("rp_custom_template", "random");
        }

        return npc;
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
                        if(skillKey == "rp_health") {
                            target->setMaxHAM(0, finalSkill);
                            target->setBaseHAM(0, finalSkill);
                            target->setHAM(0, finalSkill);
                        } else if(skillKey == "rp_action") {
                            target->setMaxHAM(3, finalSkill);
                            target->setBaseHAM(3, finalSkill);
                            target->setHAM(3, finalSkill);
                        } else if(skillKey == "rp_will") {
                            target->setMaxHAM(6, finalSkill);
                            target->setBaseHAM(6, finalSkill);
                            target->setHAM(6, finalSkill);
                        }
                    }
                    objData.pop();
                }
            } else {
                if(creature != target)
                    creature->sendSystemMessage("Skill Template  \"" + skillTemplate + "\" not found.");
            }
            luaObject.pop();
    } 

    static void ApplyEquipmentTemplateToNPC(CreatureObject* creature, CreatureObject* target, String equipmentTemplate) {
            try {
                Lua* lua = DirectorManager::instance()->getLuaInstance();
                lua->runFile("custom_scripts/rp_npcs/equipment/" + equipmentTemplate + ".lua");

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
                            
                            while(index + 1 <= fieldSize) {

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
            if(templ.contains("hair") || templ.contains("datapad") || templ.contains("inventory")) {
                continue;
            }
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
        Lua* lua = DirectorManager::instance()->getLuaInstance();

        if(!lua->runFile("custom_scripts/rp_npcs/customization/" + customizeTemplate + ".lua")) {
            return;
        }

        LuaObject luaObject = lua->getGlobalObject("customization");

        if (target == nullptr || target->getZone() == nullptr || target->getZone()->getCreatureManager() == nullptr) {
            creature->sendSystemMessage("Target creature was not the correct type; or the zone it exists in does not exist.");
            luaObject.pop();
            return;
        }

        if(luaObject.isValidTable()) {
            for (int i = 1; i <= luaObject.getTableSize(); ++i) {
                LuaObject objData = luaObject.getObjectAt(i);
                if (objData.isValidTable()) {
                    String varName = objData.getStringAt(1);
                    
                    if(varName == "height") {
                        float height = objData.getFloatAt(2);
                        target->setHeight(height, true);
                    } else {
                        int16 value = objData.getIntAt(2);
                        target->setCustomizationVariable(varName, value, true);
                    }                   
                }
                objData.pop();
            }
        } else {
            if(creature != target) {
                creature->sendSystemMessage("Customization Template  \"" + customizeTemplate + "\" not found.");
            }
        }
        luaObject.pop();
    } 

    static void ApplyRandomCustomizationToNPC(CreatureObject* creature, CreatureObject* target) {
        Lua* lua = DirectorManager::instance()->getLuaInstance();
        String customizeTemplate = creature->getObjectTemplate()->getTemplateFileName();
        lua->runFile("custom_scripts/rp_npcs/random/" + customizeTemplate + ".lua");
        auto logger = StackTrace::getLogger();
        //logger->info(true) << "Loading Customization Template: " << customizeTemplate;
        if(!lua->runFile("custom_scripts/rp_npcs/random/" + customizeTemplate + ".lua")) {
            return;
        }

        LuaObject luaObject = lua->getGlobalObject("random_ranges");

        if (target == nullptr || target->getZone() == nullptr || target->getZone()->getCreatureManager() == nullptr) {
            creature->sendSystemMessage("Target creature was not the correct type; or the zone it exists in does not exist.");
            logger->info(true) << "Target creature was not the correct type; or the zone it exists in does not exist. " << customizeTemplate;
            luaObject.pop();
            return;
        }

        int hairColor = -1;
        if(luaObject.isValidTable()) {
            for (int i = 1; i <= luaObject.getTableSize(); ++i) {
                LuaObject objData = luaObject.getObjectAt(i);
                if (objData.isValidTable()) {
                    String varName = objData.getStringAt(1);
                    
                    if(varName == "height") {
                        float min = objData.getFloatAt(2);
                        float max = objData.getFloatAt(3);
                        int result = System::random(((max * 100) - (min * 100))) + (min * 100);
                        float height = ((float)result) / 100.0f;
                        target->setHeight(height, true);
                    } else if(varName == "hair") { 
                        //auto logger = StackTrace::getLogger();
                        String objectTemplate = objData.getStringAt(2);
                        int min = objData.getIntAt(3);
                        int max = objData.getIntAt(4);
                        int result = System::random((max - min)) + min;
                        //logger->info("Loaded Hair Values", true);
                        ManagedReference<SceneObject*> inventory = target->getSlottedObject("inventory");
                        if (inventory == nullptr) {
                            objData.pop();
                                continue;
                        }

                        objectTemplate = objectTemplate.replaceAll("shared_", "");    

                        if(result < 10)
                            objectTemplate = objectTemplate + "_s0" + String::valueOf(result) + ".iff";
                        else 
                            objectTemplate = objectTemplate + "_s" + String::valueOf(result) + ".iff";

                        //logger->info("Hair Object Template: " + objectTemplate, true);
                            
                        Reference<SharedObjectTemplate*> shot = TemplateManager::instance()->getTemplate(objectTemplate.hashCode());

                        if(shot == nullptr) {
                            objData.pop();
                            continue;
                        }

                        TangibleObject* hair = (target->getZoneServer()->createObject(shot->getServerObjectCRC(), 1)).castTo<TangibleObject*>();

                        if (hair == nullptr) {
                            objData.pop();
                            continue;
                        }

                        Locker locker(hair);
                        hair->createChildObjects();

                        String hairColorName = objData.getStringAt(5);
                        int hairMin = objData.getIntAt(6);
                        int hairMax = objData.getIntAt(7);
                        int hairResult = System::random((hairMax - hairMin)) + hairMin;
                        if(hairResult > 255) hairResult = 255;
                        else if(hairResult < 0) hairResult = 0;
                        //logger->info("Loaded custom hair colors", true);
                        if(hairColor == -1)
                            hairColor = hairResult;
                        else 
                            hairResult = hairColor;

                        hair->setCustomizationVariable(hairColorName, hairResult, true);

                        //Transfer
                        if (inventory->transferObject(hair, -1, true)) {
                            inventory->broadcastObject(hair, true);
                        } else {
                            hair->destroyObjectFromDatabase(true);
                            objData.pop();
                            continue;
                        }

                        //Equip
                        target->getZone()->getCreatureManager()->addWearableItem(target, hair);
                    } else {
                        
                        int16 min = objData.getIntAt(2);
                        int16 max = objData.getIntAt(3);
                        int result = System::random((max - min)) + min;
                        if(result > 255) result = 255;
                        else if(result < 0) result = 0;
                        if(varName == "/private/index_color_facial_hair") {
                            if(hairColor == -1)
                                hairColor = result;
                            else 
                                result = hairColor;
                        }
                        //auto logger = StackTrace::getLogger();
                        //logger->info("Set Random Value: " + varName + " = " + String::valueOf(result), true);
                        target->setCustomizationVariable(varName, result, true);
                    }                   
                }
                objData.pop();
            }
        } else {
            if(creature != target) {
                creature->sendSystemMessage("Customization Randomization Template  \"" + customizeTemplate + "\" not found.");
                
            } else {
                logger->info(true) << "Could not find customization randomization template: " << customizeTemplate;
            }
        }
        luaObject.pop();
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

        float height = targetMob->getHeight();
        text << "\t{\"height\", " << height << "}," << endl; 

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

    static void SaveRandomizationTemplate(CreatureObject* creature, const uint64& target, String name) {
        ManagedReference<SceneObject*> object = creature->getZoneServer()->getObject(target, false);

		CreatureObject* targetMob = creature;

		if (object != nullptr) {
			if (object->isCreatureObject()) {
				targetMob = cast<CreatureObject*>(object.get());
			}
		}

        StringBuffer text;
        text << "random_ranges = {" << endl;

        CustomizationVariables* playerCustomVars = targetMob->getCustomizationVariables();

        int playerVarSize = playerCustomVars->getSize();

        for (int k = 0; k < playerVarSize; k++) {
			uint8 key = playerCustomVars->elementAt(k).getKey();
			int16 value = playerCustomVars->elementAt(k).getValue();
			String valueType = CustomizationIdManager::instance()->getCustomizationVariable(key);

            text << "\t{\"" << valueType << "\", 0, 255}," << endl; 
		}

        text << "\t{\"height\", 1,1}," << endl; 

        text << "}";

        if(name.isEmpty())
			    throw Exception();     
            
        File* file = new File("custom_scripts/rp_npcs/random_raw/" + name + ".lua");
		FileWriter* writer = new FileWriter(file, false); // true for appending new lines

        writer->writeLine(text.toString());

        writer->close();
		delete file;
		delete writer;

        creature->sendSystemMessage("Randomization template saved to bin/custom_scripts/rp_npcs/random_raw/" + name + ".lua!");
    }

    static void PlaceStructureFromTemplate(CreatureObject* creature, String templateFile, String structureName = "") {
            ManagedReference<Zone*> zone = creature->getZone();
            if (creature->getParent() != nullptr) {
			    creature->sendSystemMessage("You must be outside to do this");
			    return;
            }

            int angle = creature->getDirectionAngle();
            float x = creature->getPositionX();
	        float y = creature->getPositionY();

            StructureObject* structure = StructureManager::instance()->placeStructure(creature, templateFile, x, y, angle, 1);
            if(structure == nullptr) {
                creature->sendSystemMessage("Invalid structure template.");
                return;
            }
            StringBuffer text;
            text << "Structure Placed. Structure ID: " << (structure->getObjectID() / 2);
            creature->sendSystemMessage(text.toString());
            structure->setCustomObjectName(structureName, true);
    }

    static void CallScreenplayFunction(CreatureObject* creature, String screenPlay, String function) {
        Lua* lua = DirectorManager::instance()->getLuaInstance();
        LuaFunction startScreenPlay(lua->getLuaState(), screenPlay, function, 0);
        startScreenPlay << creature;
        startScreenPlay.callFunction();
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

    static void SetDispenserContainer(SceneObject* object, bool isDispenser) {
        if(object != nullptr) {
            if(isDispenser) {
                object->setStoredInt("dispenser_container", 1);
            } else {
                object->deleteStoredInt("dispenser_container");
            }            
        }
    }

    static void SetPublicContainer(SceneObject* object, bool isPublic) {
        if(object != nullptr) {
            if(isPublic) {
                object->setStoredInt("public_container", 1);
            } else {
                object->deleteStoredInt("public_container");
            }
        }
    }

    static void ScreenplaySpoutCreature(CreatureObject* creature, SceneObject* target, String fileName) {
        int angle = target->getDirectionAngle();

        if(target->isCreatureObject()) {
            if(!target->asCreatureObject()->isAiAgent())
                return;
        } else return;            

        CreatureObject* mob = target->asCreatureObject();
		const CreatureTemplate* creatureTemplate = mob->asAiAgent()->getCreatureTemplate();
		String mobileName = creatureTemplate->getTemplateName();

        StringBuffer text;

        String planetName = target->getZone()->getZoneName();

		text << "spawnMobile(\"" << planetName << "\", " <<  "\"" << mobileName << "\", 1, ";

		if (mob->getParent() != nullptr && mob->getParent().get()->isCellObject()) {
				// Inside
			ManagedReference<CellObject*> cell = cast<CellObject*>( mob->getParent().get().get());
			Vector3 cellPosition = mob->getPosition();

			text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", " << angle << ", " << cell->getObjectID() << ")";
		}else {
			// Outside
			Vector3 worldPosition = mob->getWorldPosition();

			text << worldPosition.getX() << ", " << worldPosition.getZ() << ", " << worldPosition.getY() << ", " << angle << ", " << "0" << ")";
		}
			// Returning: spawnMobile("planet", "mobileTemplate", 1, x, z, y, heading, cellid)

		if(fileName.isEmpty())
			return;

		File* file = new File("custom_scripts/spout/" + fileName + ".lua");
		FileWriter* writer = new FileWriter(file, true); // true for appending new lines

		writer->writeLine(text.toString());

		writer->close();
		delete file;
		delete writer;

		creature->sendSystemMessage("Data written to bin/custom_scripts/spout/" + fileName + ".lua!");
    }

    static void ScreenplaySpoutRoleplayMobile(CreatureObject* creature, SceneObject* target, String fileName) {
        int angle = target->getDirectionAngle();

        if(target->isCreatureObject()) {
            if(!target->asCreatureObject()->isAiAgent())
                return;
        } else return;            

        CreatureObject* mob = target->asCreatureObject();
		const CreatureTemplate* creatureTemplate = mob->asAiAgent()->getCreatureTemplate();
		String mobileName = creatureTemplate->getTemplateName();
        String appName = target->getObjectTemplate()->getFullTemplateString(); //"REPLACE";//target->getAppearanceTemplate();

        StringBuffer text;

        String planetName = target->getZone()->getZoneName();

        text << "spawnRoleplayMobile(\"" << planetName << "\", " <<  "\"" << mobileName << "\", 1, ";

        if (mob->getParent() != nullptr && mob->getParent().get()->isCellObject()) {
				// Inside
			ManagedReference<CellObject*> cell = cast<CellObject*>( mob->getParent().get().get());
			Vector3 cellPosition = mob->getPosition();

			text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", " << angle << ", " << cell->getObjectID() << ", ";
		}else {
			// Outside
			Vector3 worldPosition = mob->getWorldPosition();

			text << worldPosition.getX() << ", " << worldPosition.getZ() << ", " << worldPosition.getY() << ", " << angle << ", " << "0" << ", ";
		}

        text << "\"" << appName << "\"" << ", \"default\", \"default\", \"default\") --Equip, Skill, Customization";

        if(fileName.isEmpty())
			return;

		File* file = new File("custom_scripts/spout/" + fileName + ".lua");
		FileWriter* writer = new FileWriter(file, true); // true for appending new lines

		writer->writeLine(text.toString());

		writer->close();
		delete file;
		delete writer;

		creature->sendSystemMessage("Data for \"spawnRoleplayMobile\" written to bin/custom_scripts/spout/" + fileName + ".lua!");
    }

    static void ScreenplaySpoutCivPoint(CreatureObject* creature, SceneObject* target, String tag, String fileName) {
        int angle = target->getDirectionAngle();

        if(target->isCreatureObject()) {
            if(!target->asCreatureObject()->isAiAgent())
                return;
        } else return;            

        CreatureObject* mob = target->asCreatureObject();
		const CreatureTemplate* creatureTemplate = mob->asAiAgent()->getCreatureTemplate();
		String mobileName = creatureTemplate->getTemplateName();

        StringBuffer text;

        text << "{";

        if (mob->getParent() != nullptr && mob->getParent().get()->isCellObject()) {
				// Inside
			ManagedReference<CellObject*> cell = cast<CellObject*>( mob->getParent().get().get());
			Vector3 cellPosition = mob->getPosition();

			text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", " << angle << ", " << cell->getObjectID() << ",";
		}else {
			// Outside
			Vector3 worldPosition = mob->getWorldPosition();

			text << worldPosition.getX() << ", " << worldPosition.getZ() << ", " << worldPosition.getY() << ", " << angle << ", " << "0" << ",";
		}

        text << "{" << tag << "}},";

        if(fileName.isEmpty())
			return;

		File* file = new File("custom_scripts/spout/" + fileName + ".lua");
		FileWriter* writer = new FileWriter(file, true); // true for appending new lines

		writer->writeLine(text.toString());

		writer->close();
		delete file;
		delete writer;

		creature->sendSystemMessage("Data written to bin/custom_scripts/spout/" + fileName + ".lua!");
    }

    static void ScreenplaySpoutCivPointWithMarker(CreatureObject* creature, String tag, String fileName) {
        CreatureObject* target = CreateRoleplayNPC(creature, "object/mobile/rp_human_male.iff", "default", "default", "default");
        if(target == nullptr){
            creature->sendSystemMessage("Internal error. Could not find template for some reason");
            return;
        }
        target->updateDirection(Math::deg2rad(creature->getDirectionAngle()));
        target->setCustomObjectName("Civilian Stand-in (" + tag + ")", true);
        ScreenplaySpoutCivPoint(creature, target, tag, fileName);        
    }

    static void ScreenplaySpoutCivPatrolPoint(CreatureObject* creature, bool delay, String animGroup, String fileName) {
        int angle = creature->getDirectionAngle();

        StringBuffer text;

        String delayText = delay ? "true" : "false";

        text << "{";

        if (creature->getParent() != nullptr && creature->getParent().get()->isCellObject()) {
				// Inside
			ManagedReference<CellObject*> cell = cast<CellObject*>( creature->getParent().get().get());
			Vector3 cellPosition = creature->getPosition();

			text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", " << angle << ", " << cell->getObjectID() << ", " << delayText << ", ";
		}else {
			// Outside
			Vector3 worldPosition = creature->getWorldPosition();

			text << worldPosition.getX() << ", " << worldPosition.getZ() << ", " << worldPosition.getY() << ", " << angle << ", " << "0" << "," << delayText << ", ";
		}

        text <<  "\"" << animGroup << "\"},";

        if(fileName.isEmpty())
			return;

        File* file = new File("custom_scripts/spout/" + fileName + ".lua");
		FileWriter* writer = new FileWriter(file, true); // true for appending new lines

		writer->writeLine(text.toString());

		writer->close();
		delete file;
		delete writer;

		creature->sendSystemMessage("Data written to bin/custom_scripts/spout/" + fileName + ".lua!");
    }

    static void ScreenplaySpoutObject(CreatureObject* creature, SceneObject* object, String fileName) {
        if(object == nullptr) return;
        int angle = object->getDirectionAngle();

        const String templateFile = object->getObjectTemplate()->getFullTemplateString();
        

        StringBuffer text;
        String planetName = object->getZone()->getZoneName();

        text << "spawnSceneObject(\"" << planetName << "\", \"" << templateFile << "\", ";

        if (object->getParent() != nullptr && object->getParent().get()->isCellObject()) {
			// Inside
			ManagedReference<CellObject*> cell = cast<CellObject*>( object->getParent().get().get());
			Vector3 cellPosition = object->getPosition();

			text << cellPosition.getX() << ", " << cellPosition.getZ() << ", " << cellPosition.getY() << ", " << cell->getObjectID() << ", ";
		}else {
			// Outside
			Vector3 worldPosition = object->getWorldPosition();
			text << worldPosition.getX() << ", " << worldPosition.getZ() << ", " << worldPosition.getY() << ", " << "0" << ", ";
		}

		const Quaternion* dir = object->getDirection();
		text << dir->getW() << ", " << dir->getX() << ", " << dir->getY() << ", " << dir->getZ() << ")";

        if(fileName.isEmpty())
			return;

		File* file = new File("custom_scripts/spout/" + fileName + ".lua");
		FileWriter* writer = new FileWriter(file, true); // true for appending new lines

		writer->writeLine(text.toString());

		writer->close();
		delete file;
		delete writer;

		creature->sendSystemMessage("Data written to bin/custom_scripts/spout/" + fileName + ".lua!");
    }

    static void NoLoadscreenTeleport(CreatureObject* creature, const UnicodeString& arguments) {
        float x, y;
		float z = 0;

		Zone* zone = creature->getZone();

		if (zone == nullptr)
			return;

		String zoneName = zone->getZoneName();
		uint64 parentID = 0;

        try {
			UnicodeTokenizer tokenizer(arguments);
            Zone* newZone = nullptr;

			x = tokenizer.getFloatToken();
			y = tokenizer.getFloatToken();

			if (tokenizer.hasMoreTokens())
				tokenizer.getStringToken(zoneName);

			if (tokenizer.hasMoreTokens()) {
				z = tokenizer.getFloatToken();
				parentID = tokenizer.getLongToken();
			} else {
				newZone = creature->getZoneServer()->getZone(zoneName);

				if (newZone != nullptr)
					z = CollisionManager::getWorldFloorCollision(x, y, newZone, false);
			}

			creature->setDirection(0);

            if(newZone != zone) {
                creature->switchZone(zoneName, x, z, y, parentID);
            } else {
                creature->teleport(x, z, y, parentID);
            }
			
		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /dm teleport <x> <y> [<planet>] [<z> <parentID>]");
		}
    }

    static void NoLoadscreenTeleportTo(CreatureObject* creature, const UnicodeString& arguments) {
        String targetName;

		try {
			UnicodeTokenizer args(arguments);
			args.getStringToken(targetName);

		} catch (Exception& e) {
			creature->sendSystemMessage("SYNTAX: /dm teleportTo <targetName>");
			return;
		}

		ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();
		ManagedReference<CreatureObject*> targetCreature = playerManager->getPlayer(targetName);

		if (targetCreature == nullptr) {
			creature->sendSystemMessage("The specified player does not exist.");
			return;
		}

		if (targetCreature->getZone() == nullptr) {
			creature->sendSystemMessage("The specified player is not in a zone that is currently loaded.");
			return;
		}

		String zoneName = targetCreature->getZone()->getZoneName();
		float x = targetCreature->getPositionX();
		float y = targetCreature->getPositionY();
		float z = targetCreature->getPositionZ();
		uint64 parentid = targetCreature->getParentID();

        if(zoneName == creature->getZone()->getZoneName()) {
            creature->teleport(x, z, y, parentid);
        } else {
            creature->switchZone(zoneName, x, z, y, parentid);
        }		
    }

    static void PopulateObjectContents(CreatureObject* creature, SceneObject* target, String contentListTemplate) {
        try {
            Lua* lua = DirectorManager::instance()->getLuaInstance();
            lua->runFile("custom_scripts/rp_objects/content_lists/" + contentListTemplate + ".lua"); 
            LuaObject luaObject = lua->getGlobalObject("content");    
            if (target == nullptr) {
                if(creature != nullptr) {
                    creature->sendSystemMessage("Target was not the correct type; or the zone it exists in does not exist.");
                }
                    
                luaObject.pop();
                return;
            }   
            if(luaObject.isValidTable()) {
                for (int i = 1; i <= luaObject.getTableSize(); ++i) {
                    LuaObject objData = luaObject.getObjectAt(i);
                    if (objData.isValidTable()) {   
                        ManagedReference<SceneObject*> inventory = target;
                        if (inventory == nullptr) {
                            objData.pop();
                            break;
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

                        while(index + 1 <= fieldSize) { 
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
                    }
                    objData.pop();
                }
            } else {
                if(creature != nullptr) {
                    creature->sendSystemMessage("Content List Template  \"" + contentListTemplate + "\" not found.");
                }                    
            }
            luaObject.pop();
        } catch (Exception& e) {
    	    // creature->sendSystemMessage("Invalid arguments for RP command. Help: /rp help");
            if(creature != nullptr) {
                creature->sendSystemMessage("Error with Content Population: " +  e.getMessage());
            }
                
        }   
    }

    static void CreateContentListFromInventory(CreatureObject* creature, SceneObject* target, String contentListTemplate) {
        if(target == nullptr){
            return;
        }

        StringBuffer text;
        text << "content = {" << endl;

        int itemCount = target->getContainerObjectsSize();

        for(int i = 0;i<itemCount;i++) {
            ManagedReference<SceneObject*> object = target->getContainerObject(i);
            if(object->isTangibleObject()) {

                TangibleObject* item = object->asTangibleObject();
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
            } else {
                continue;
            }
        }

        text << "}";

        if(contentListTemplate.isEmpty())
			    throw Exception();     
            
        File* file = new File("custom_scripts/rp_objects/content_lists/" + contentListTemplate + ".lua");
		FileWriter* writer = new FileWriter(file, false); // true for appending new lines

        writer->writeLine(text.toString());

        writer->close();
		delete file;
		delete writer;

        creature->sendSystemMessage("Inventory content manifest saved to bin/custom_scripts/rp_objects/content_lists/" + contentListTemplate + ".lua!");
    }

    static TangibleObject* CreateLootbox(CreatureObject* creature, String objectTemplate, String contentList, bool noResell = true) {
        if(creature == nullptr){
            return nullptr;
        }

        objectTemplate = objectTemplate.replaceAll("shared_", "");
        Reference<SharedObjectTemplate*> shot = TemplateManager::instance()->getTemplate(objectTemplate.hashCode());    
        if(shot == nullptr) {
            return nullptr;
        }   

        TangibleObject* box = (creature->getZoneServer()->createObject(shot->getServerObjectCRC(), 1)).castTo<TangibleObject*>();    
        if (box == nullptr) {
            return nullptr;
        }   

        Locker locker(box);
        box->createChildObjects(); 

        try {
            Lua* lua = DirectorManager::instance()->getLuaInstance();
            lua->runFile("custom_scripts/rp_objects/container/" + contentList + ".lua"); 
            LuaObject luaObject = lua->getGlobalObject("containerManifest");  
            int itemCount = 0;
            if(luaObject.isValidTable()) {
                for (int i = 1; i <= luaObject.getTableSize(); ++i) {
                    LuaObject objData = luaObject.getObjectAt(i);
                    if (objData.isValidTable()) {  
                        String contentObjTemplate = objData.getStringAt(1);
                        String indexStr = String::valueOf(i);
                        //Add Customization Variables       
                        int fieldSize = objData.getTableSize();
                        int index = 2;
                        int varIndex = 1;
                        while(index + 1 <= fieldSize) { 
                            String varName = objData.getStringAt(index);    
                            int16 value = objData.getIntAt(index + 1);  
                            box->setStoredString("content_customVar" + String::valueOf(varIndex) + "_" + indexStr, varName);
                            box->setStoredInt("content_customVar" + String::valueOf(varIndex) + "Value_" + indexStr, value);
                            index+=2;
                            varIndex++;
                        }

                        box->setStoredString("content"+indexStr,contentObjTemplate);
                        itemCount++;
                        if(noResell)
                            box->setStoredInt("content_nosell_"+indexStr,1);
                    }

                    objData.pop();
                }
            } else {
                if(creature != nullptr) {
                    creature->sendSystemMessage("Container Template  \"" + contentList + "\" not found.");
                }                    
            }
            luaObject.pop();
            
            box->setStoredInt("content_count",itemCount);
            ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

            if(inventory == nullptr) {
                box->destroyObjectFromDatabase(true);
                return nullptr;
            }

            //Transfer
            if (inventory->transferObject(box, -1, true)) {
                inventory->broadcastObject(box, true);
            } else {
                box->destroyObjectFromDatabase(true);
                return nullptr;
            }  
        } catch (Exception& e) {
            if(creature != nullptr) {
                creature->sendSystemMessage("Error with Container Creation: " +  e.getMessage());
            }
            return nullptr;
        } 

        return box;
    }

};

#endif 