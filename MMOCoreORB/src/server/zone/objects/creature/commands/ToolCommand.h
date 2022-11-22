#ifndef TOOLCOMMAND_H_
#define TOOLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/borrie/BorUtil.h"

class ToolCommand : public QueueCommand {
public:
	ToolCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		int adminLevelCheck = ghost->getAdminLevel();

		ResourceManager* resMan = creature->getZoneServer()->getResourceManager();

		Locker locker(resMan);

		StringTokenizer args(arguments.toString());

		try {
			String command, Result, secondCommand;

			if (args.hasMoreTokens()) {
				args.getStringToken(command);

				command = command.toLowerCase();
				ManagedReference<SceneObject*> object;
				if (target != 0) {
					object = server->getZoneServer()->getObject(target, false);
				}

				if (command == "help") {
					creature->sendSystemMessage("/tool rotate <left right yaw pitch roll reset yxx pxx rxx> <value>");
					creature->sendSystemMessage("/tool move <forward back up down> <value>");
					creature->sendSystemMessage("/tool tjt <x> <y> <z> <rW> <rX> <rY> <rZ> (To be used with The Jawa Toolset)");
					creature->sendSystemMessage("/tool face <n nw ne e s sw se w up down left right me>");
					creature->sendSystemMessage("/tool tp <x y z> <coordinate>");
					creature->sendSystemMessage("/tool align");
				} else if (command == "rotate") {
					rotate(creature, target, adminLevelCheck, &args);
				} else if (command == "move") {
					move(creature, target, adminLevelCheck, &args);
				} else if (command == "tjt") {
					tjtMove(creature, target, adminLevelCheck, &args);
				} else if (command == "face") {
					faceDir(creature, target, adminLevelCheck, &args);
				} else if (command == "tp" && adminLevelCheck > 0) {
					teleportItem(creature, target, adminLevelCheck, &args);
				} else if (command == "align" && adminLevelCheck > 0) {
					alignToObject(creature, target, adminLevelCheck, &args);
				} else if(command == "createstructure" && adminLevelCheck > 0) {
					if(args.hasMoreTokens()) {
						String prefabName;
						args.getStringToken(prefabName);
						String structureName = "";
						
						if(args.hasMoreTokens())
							args.getStringToken(structureName);

						BorUtil::PlaceStructureFromTemplate(creature, prefabName, structureName);
					} else {
						creature->sendSystemMessage("You need to specify a template to spawn.");
					}
				} else if(command == "saveprefab" && adminLevelCheck > 0) {
					if(args.hasMoreTokens()) {
						String prefabName;
						args.getStringToken(prefabName);
						BorUtil::SaveStructureContents(creature, prefabName);
					} else {
						creature->sendSystemMessage("You need to specify a name for the prefab to save.");
					}
				}else if(command == "loadprefab" && adminLevelCheck > 0) {
					if(args.hasMoreTokens()) {
						String prefabName;
						args.getStringToken(prefabName);
						BorUtil::LoadStructureContents(creature, prefabName);
					} else {
						creature->sendSystemMessage("You need to specify a name for the prefab to load.");
					}
				} else if(command == "savenpcequipment" && adminLevelCheck > 0) {
					if(args.hasMoreTokens()) {
						String prefabName;
						args.getStringToken(prefabName);
						BorUtil::SaveEquipmentToTemplate(creature, target, prefabName);
					} else {
						creature->sendSystemMessage("You need to specify a name for the equipment template to save as.");
					}
				} else if(command == "savenpccustomization" && adminLevelCheck > 0) {
					if(args.hasMoreTokens()) {
						String prefabName;
						args.getStringToken(prefabName);
						BorUtil::SaveCustomizationToTemplate(creature, target, prefabName);
					} else {
						creature->sendSystemMessage("You need to specify a name for the customization template to save as.");
					}
				} else if(command == "saverandomtemplate" && adminLevelCheck > 0) { 
					if(args.hasMoreTokens()) {
						String prefabName;
						args.getStringToken(prefabName);
						BorUtil::SaveRandomizationTemplate(creature, target, prefabName);
					} else {
						creature->sendSystemMessage("You need to specify a name for the raw randomization template to save as.");
					}
				} else if(command=="spoutmob" && adminLevelCheck > 0) {
					if(args.hasMoreTokens()) {
						if(object != nullptr) {
							String fileName;
							args.getStringToken(fileName);
							BorUtil::ScreenplaySpoutCreature(creature, object, fileName);
						} else {
							creature->sendSystemMessage("ERROR: To use Spout Mob, you need to target a creature and specify a file name.");
						}
					} else {
						creature->sendSystemMessage("ERROR: To use Spout Mob, you need to target a creature and specify a file name.");
					}
				} else if(command =="spoutrpmob" && adminLevelCheck > 0) { 
					if(args.hasMoreTokens()) {
						if(object != nullptr) {
							String fileName;
							args.getStringToken(fileName);
							BorUtil::ScreenplaySpoutRoleplayMobile(creature, object, fileName);
						} else {
							creature->sendSystemMessage("ERROR: To use Spout Rp Mob, you need to target a creature and specify a file name.");
						}
					} else {
						creature->sendSystemMessage("ERROR: To use Spout Rp Mob, you need to target a creature and specify a file name.");
					}
				} else if(command == "spoutciv" && adminLevelCheck > 0) {
					if(args.hasMoreTokens()) {
						String civTag;
						args.getStringToken(civTag);
						if(args.hasMoreTokens()) {
							String fileName;
							args.getStringToken(fileName);
							BorUtil::ScreenplaySpoutCivPoint(creature, object, civTag, fileName);
						} else {
							creature->sendSystemMessage("ERROR: To use Spout Civ, you need to target a creature and specify a file name and a tag.");
						}
					} else {
						creature->sendSystemMessage("ERROR: To use Spout Civ, you need to target a creature and specify a file name and a tag.");
					}
				} else if(command == "spoutcivwithdummy" && adminLevelCheck > 0) {
					if(args.hasMoreTokens()) {
						String civTag;
						args.getStringToken(civTag);
						if(args.hasMoreTokens()) {
							String fileName;
							args.getStringToken(fileName);
							BorUtil::ScreenplaySpoutCivPointWithMarker(creature, civTag, fileName);
						} else {
							creature->sendSystemMessage("ERROR: To use Spout Civ With Dummy, you need to specify a file name and a tag.");
						}
					} else {
						creature->sendSystemMessage("ERROR: To use Spout Civ With Dummy, you need to specify a file name and a tag.");
					}
				} else if(command == "spoutpatrolpoint" && adminLevelCheck > 0) { 
					if(args.hasMoreTokens()) {
						String fileName;
						args.getStringToken(fileName);
						if(args.hasMoreTokens()) {
							String delayAnimGroup;
							args.getStringToken(delayAnimGroup);
							BorUtil::ScreenplaySpoutCivPatrolPoint(creature, true, delayAnimGroup, fileName);
						} else {
							BorUtil::ScreenplaySpoutCivPatrolPoint(creature, false, "none", fileName);
						}
					} else {
						creature->sendSystemMessage("ERROR: To use Spout Patrol Point, you must do: /spoutpatrolpoint <filename> <animGroup>");
					}
				}else if(command=="spoutobj" && adminLevelCheck > 0) {
					if(args.hasMoreTokens()) {
						if(object != nullptr) {
							String fileName;
							args.getStringToken(fileName);
							BorUtil::ScreenplaySpoutObject(creature, object, fileName);
						} else {
							creature->sendSystemMessage("ERROR: To use Spout Obj, you need to target an object and specify a file name.");
						}
					} else {
						creature->sendSystemMessage("ERROR: To use Spout Obj, you need to target an object and specify a file name.");
					}
				} else if(command == "togglepublic" && adminLevelCheck > 0) {
					BorUtil::TogglePublicContainer(creature, target);	
				} else if(command == "toggledispenser" && adminLevelCheck > 0) {
					BorUtil::ToggleDispenserContainer(creature, target);	
				} else if(command =="discordusercheck") { 
					BorrieRPG::ReportPlayerCountToDiscord(creature);
				} else if(command == "populate"&& adminLevelCheck > 0) { 
					if(args.hasMoreTokens()) {
						String prefabName;
						args.getStringToken(prefabName);
						BorUtil::PopulateObjectContents(creature, object, prefabName);
					} else {
						creature->sendSystemMessage("You need to specify which content list you'd like to use to populate this item with.");
					}
				} else if(command == "savecontents"&& adminLevelCheck > 0) { 
					if(args.hasMoreTokens()) {
						String prefabName;
						args.getStringToken(prefabName);
						BorUtil::CreateContentListFromInventory(creature, object, prefabName);
					} else {
						creature->sendSystemMessage("You need to specify a file name to save this content list as.");
					}
				} else if(command == "dupe" || command == "duplication" || command == "duplicate") {
					
				} else {
					throw Exception();
					creature->sendSystemMessage("Invalid arguments for Tool command. Help: /tool help");
				}
			} else {
				throw Exception();
			}
		} catch (Exception& e) {
			// creature->sendSystemMessage("Invalid arguments for RP command. Help: /rp help");
		}

		return SUCCESS;
	}

	void faceDir(CreatureObject* creature, const uint64& target, int adminLevelCheck, StringTokenizer* args) const {
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target, false);
		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /tool face");
			throw Exception();
		}

		if (adminLevelCheck < 1) {
			playerMoveRotateRules(creature, object);
		}

		String possibleDirections = "n nw ne e s sw se w up down left right me";
		String dir = "";

		if (args->hasMoreTokens()) {
			args->getStringToken(dir);
		}

		dir = dir.toLowerCase();

		if (!possibleDirections.contains(dir))
			throw Exception();

		// Setup rotation
		if (dir == "n") {
			object->setDirection(1.0, 0.0, 0.0, 0.0);
		} else if (dir == "s") {
			object->setDirection(0.0, 0.0, 1.0, 0.0);
		} else if (dir == "w") {
			object->setDirection(0.707, 0.0, -0.707, 0.0);
		} else if (dir == "e") {
			object->setDirection(0.707, 0.0, 0.707, 0.0);
		} else if (dir == "nw") {
			object->setDirection(0.924, 0.0, -0.383, 0.0);
		} else if (dir == "ne") {
			object->setDirection(0.924, 0.0, 0.383, 0.0);
		} else if (dir == "sw") {
			object->setDirection(0.383, 0.0, -0.924, 0.0);
		} else if (dir == "se") {
			object->setDirection(0.383, 0.0, 0.924, 0.0);
		} else if (dir == "up") {
			object->setDirection(0.707, 0.0, 0.0, 0.707);
		} else if (dir == "down") {
			object->setDirection(0.707, 0.0, 0.0, -0.707);
		} else if (dir == "right") {
			object->setDirection(0.707, -0.707, 0.0, 0.0);
		} else if (dir == "left") {
			object->setDirection(0.707, 0.707, 0.0, 0.0);
		} else if(dir == "me") {
			object->faceObject(creature, true);
		}

		// Apply rotation
		object->incrementMovementCounter();
		if (object->getParent() != nullptr)
			object->teleport(object->getPositionX(), object->getPositionZ(), object->getPositionY(), object->getParent().get()->getObjectID());
		else
			object->teleport(object->getPositionX(), object->getPositionZ(), object->getPositionY());
	}

	// Rotate objects with Yaw, Pitch, Roll. Also allows admin to rotate most objects and players to rotate LoH decor outside in Mos Espa.
	void rotate(CreatureObject* creature, const uint64& target, int adminLevelCheck, StringTokenizer* args) const {
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target, false);

		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /tool rotate");
			throw Exception();
		}

		if (object->isCreatureObject()) {
			creature->sendSystemMessage("Error: Invalid Target. Must not be a creature.");
			throw Exception();
		}

		if (adminLevelCheck < 1) {
			playerMoveRotateRules(creature, object);
		}

		String possibleDirections = "left right yaw pitch roll reset yxx pxx rxx";
		String dir = "";
		String deg = "";
		int degrees = 0;

		if (args->hasMoreTokens()) {
			args->getStringToken(dir);
			args->getStringToken(deg);
		}

		dir = dir.toLowerCase();

		if (!possibleDirections.contains(dir))
			throw Exception();

		if (deg.isEmpty())
			throw Exception();

		try {
			degrees = Integer::valueOf(deg);
		} catch (const Exception& e) {
			creature->sendSystemMessage("Error: /tool rotate <direction> [number] was not provided a numerical value.");
		}

		// Setup rotation
		if (dir == "right") {
			object->rotate(-degrees);
		} else if (dir == "left") {
			object->rotate(degrees);
		} else if (dir == "yaw" || dir == "yxx") {
			object->rotate(degrees);
		} else if (dir == "pitch" || dir == "pxx") {
			object->rotateYaxis(degrees);
		} else if (dir == "roll" || dir == "rxx") {
			object->rotateXaxis(degrees);
		} else if (dir == "reset" || dir == "xresetx") {
			object->setDirection(1, 0, 0, 0);
		} else {
			creature->sendSystemMessage("Error: /tool rotate command requires using the whole direction word.");
			throw Exception();
		}

		// Apply rotation
		object->incrementMovementCounter();
		if (object->getParent() != nullptr)
			object->teleport(object->getPositionX(), object->getPositionZ(), object->getPositionY(), object->getParent().get()->getObjectID());
		else
			object->teleport(object->getPositionX(), object->getPositionZ(), object->getPositionY());
	}

	// Allows admin to move most objects and players to move LoH decor outside in Mos Espa.
	void move(CreatureObject* creature, const uint64& target, int adminLevelCheck, StringTokenizer* args) const {
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target, false);

		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /tool move");
			throw Exception();
		}

		if (object->isCreatureObject()) {
			creature->sendSystemMessage("Error: Invalid Target. Must not be a creature.");
			throw Exception();
		}

		if (adminLevelCheck < 1) {
			playerMoveRotateRules(creature, object);
		}

		String possibleDirections = "forward back up down";
		String dir = "";
		String dist = "";
		float distance = 0.0;

		if (args->hasMoreTokens()) {
			args->getStringToken(dir);
			args->getStringToken(dist);
		}

		dir = dir.toLowerCase();

		if (!possibleDirections.contains(dir))
			throw Exception();

		if (dist.isEmpty())
			throw Exception();

		try {
			distance = Float::valueOf(dist);
		} catch (const Exception& e) {
			creature->sendSystemMessage("Error: /tool move <direction> [number] was not provided a numerical value.");
		}

		// if (distance < 1.f || distance > 500.f){
		//	creature->sendSystemMessage("@player_structure:movefurniture_params"); //The amount to move must be between 1 and 500.
		//	throw Exception();
		//}

		float degrees = creature->getDirectionAngle();
		float radians = Math::deg2rad(degrees);

		distance /= 100.0f;

		float offsetX = distance * sin(radians);
		float offsetY = distance * cos(radians);

		float x = object->getPositionX();
		float y = object->getPositionY();
		float z = object->getPositionZ();

		if (dir == "forward") {
			x += (offsetX);
			y += (offsetY);
		} else if (dir == "back") {
			x -= (offsetX);
			y -= (offsetY);
		} else if (dir == "up") {
			z += distance;
		} else if (dir == "down") {
			z -= distance;
		} else {
			creature->sendSystemMessage("Error: /tool move command requires using the whole direction word.");
			throw Exception();
		}

		object->incrementMovementCounter();

		if (object->getParent() != nullptr)
			object->teleport(x, z, y, object->getParent().get()->getObjectID());
		else
			object->teleport(x, z, y);
	}

	void teleportItem(CreatureObject* creature, const uint64& target, int adminLevelCheck, StringTokenizer* args) const {
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target, false);

		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /tool tp");
			throw Exception();
		}

		if (object->isCreatureObject()) {
			creature->sendSystemMessage("Error: Invalid Target. Must not be a creature.");
			throw Exception();
		}

		if (adminLevelCheck < 1) {
			// playerMoveRotateRules(creature, object);
			throw Exception();
		}

		String possibleDirections = "x y z";
		String axis = "";
		String coord = "";
		float coordinate = 0;

		if (args->hasMoreTokens()) {
			args->getStringToken(axis);
			args->getStringToken(coord);
		}

		axis = axis.toLowerCase();

		if (!possibleDirections.contains(axis))
			throw Exception();

		if (coord.isEmpty())
			throw Exception();

		try {
			coordinate = Float::valueOf(coord);
		} catch (const Exception& e) {
			creature->sendSystemMessage("Error: /tool tp <axis> [coordinate] was not provided a numerical value.");
		}

		float x = object->getPositionX();
		float y = object->getPositionY();
		float z = object->getPositionZ();

		if (axis == "x") {
			x = coordinate;
		} else if (axis == "y") {
			y = coordinate;
		} else if (axis == "z") {
			z = coordinate;
		} else {
			creature->sendSystemMessage("Error: /tool tp command requires x, y, or z for an axis.");
			throw Exception();
		}

		object->incrementMovementCounter();

		if (object->getParent() != nullptr)
			object->teleport(x, z, y, object->getParent().get()->getObjectID());
		else
			object->teleport(x, z, y);
	}

	void alignToObject(CreatureObject* creature, const uint64& target, int adminLevelCheck, StringTokenizer* args) const {
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target, false);

		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /tool tp");
			throw Exception();
		}

		if (object->isCreatureObject()) {
			creature->sendSystemMessage("Error: Invalid Target. Must not be a creature.");
			throw Exception();
		}

		if (adminLevelCheck < 1) {
			// playerMoveRotateRules(creature, object);
			throw Exception();
		}

		creature->setDirection(object->getDirection()->getX(), object->getDirection()->getY(), object->getDirection()->getZ(), object->getDirection()->getW());
		// Apply rotation
		creature->incrementMovementCounter();
		if (object->getParent() != nullptr)
			creature->teleport(object->getPositionX(), object->getPositionZ(), object->getPositionY(), object->getParent().get()->getObjectID());
		else
			creature->teleport(object->getPositionX(), object->getPositionZ(), object->getPositionY());
	}

	// Rules for player use of rotate and move
	// Allow Inside: rotate any non-creature object, if on admin list.
	// Allow Outside: rotate only LoH specific decor and only when it's in Mos Espa.
	void playerMoveRotateRules(CreatureObject* creature, SceneObject* object) const {
		ManagedReference<SceneObject*> objParent = object->getParent().get(); // Should be a CellObject or nullptr if outside

		if (objParent) { // Inside
			ManagedReference<SceneObject*> objParentParent = objParent->getParent().get();

			if (objParentParent->isBuildingObject()) {
				ManagedReference<BuildingObject*> building = cast<BuildingObject*>(objParentParent.get());

				// Is this player on the permission list?
				if (!building->isOnAdminList(creature)) {
					creature->sendSystemMessage("@player_structure:must_be_admin"); // You must be a building admin to do that.
					throw Exception();
				}
			} else if (!objParentParent->isBuildingObject()) {
				creature->sendSystemMessage("Error: Invalid location."); // Player is in a cell that is not inside a building - should not happen
				throw Exception();
			}
		} 
	}

	void tjtMove(CreatureObject* creature, const uint64& target, int adminLevelCheck, StringTokenizer* args) const {
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target, false);

		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /tool tjt");
			throw Exception();
		}

		if (object->isCreatureObject()) {
			creature->sendSystemMessage("Error: Invalid Target. Must not be a creature.");
			throw Exception();
		}

		if (adminLevelCheck < 1) {
			playerMoveRotateRules(creature, object);
		}

		float x = 0, y = 0, z = 0, rW = 0, rX = 0, rY = 0, rZ = 0;

		if (args->hasMoreTokens()) {
			x = args->getFloatToken();
			y = args->getFloatToken();
			z = args->getFloatToken();
			rW = args->getFloatToken();
			rX = args->getFloatToken();
			rY = args->getFloatToken();
			rZ = args->getFloatToken();
		} else {
			return;
		}

		object->setDirection(rW, rX, rY, rZ);

		if (object->getParent() != nullptr)
			object->teleport(x, y, z, object->getParent().get()->getObjectID());
		else
			object->teleport(x, y, z);
	}
};

#endif // TOOLCOMMAND_H_
