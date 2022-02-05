/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DMCOMMAND_H_
#define DMCOMMAND_H_

#include "server/zone/borrie/BorrieRPG.h"
#include "server/zone/borrie/BorNPC.h"
#include "server/zone/borrie/BorEffect.h"
#include "server/zone/borrie/BorDM.h"
#include "server/zone/borrie/BorUtil.h"

class DmCommand : public QueueCommand {

public:
	DmCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

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

		if (creature->getStoredInt("secretdm") == 1) {
			adminLevelCheck = 15;
		}

		StringTokenizer args(arguments.toString());

		try {
			String command, subCommand, subSubCommand;
			if (args.hasMoreTokens()) {
				args.getStringToken(command);
			}

			command = command.toLowerCase();
			ManagedReference<SceneObject*> object;
			ManagedReference<CreatureObject*> creo;
			ManagedReference<CreatureObject*> storedTarget;

			if (target != 0) {
				object = server->getZoneServer()->getObject(target, false);
			}

			if (command == "help") {
				HelpDisplay(creature);
			}

			storedTarget = BorrieRPG::GetStoredCreature(creature);

			if (adminLevelCheck > 1) { // Designer
				if (command == "storetarget") {
					BorrieRPG::SaveTarget(creature, object);
				} else if (command == "copy") {
					BorrieRPG::copyTarget(creature, object, true);
				} else if (command == "buildingcheck") {
					BorrieRPG::ShowAllStructures(creature);
				} else if (command == "setlots") {
					if (args.hasMoreTokens()) {
						args.getStringToken(subCommand);
						BorrieRPG::IncreaseLots(creature, Integer::valueOf(subCommand));
					}
				} else if (command == "color") {
					String colorID;
					if (args.hasMoreTokens()) {
						args.getStringToken(subCommand);
						if (args.hasMoreTokens()) {
							args.getStringToken(colorID);
							BorrieRPG::colorTarget(creature, object, Integer::valueOf(subCommand), Integer::valueOf(colorID));
						}
					}
				} else if (command == "tp") {
					float x, y, z;
					if (args.hasMoreTokens()) {
						args.getStringToken(subCommand);
						x = Float::valueOf(subCommand);
						if (args.hasMoreTokens()) {
							args.getStringToken(subCommand);
							z = Float::valueOf(subCommand);
							if (args.hasMoreTokens()) {
								args.getStringToken(subCommand);
								y = Float::valueOf(subCommand);
								BorrieRPG::teleportObject(creature, object, x, z, y);
							} else
								creature->sendSystemMessage("ERROR: Needs y co-ordinate");
						} else
							creature->sendSystemMessage("ERROR: Needs z co-ordinate");
					} else
						creature->sendSystemMessage("ERROR: Needs x co-ordinate");
				}
			}
			if (adminLevelCheck > 2) { // Assistant DM
				if (command == "msg") {
					BorDM::sendMessage(creature, target, adminLevelCheck, arguments.toString());
				} else if (command == "storetarget") {
					if (object != nullptr)
						BorrieRPG::SaveTarget(creature, object);
					else
						creature->sendSystemMessage("You need a target in order to save it.");
				} else if (command == "mood") {
					if (args.hasMoreTokens()) {
						args.getStringToken(subCommand);
						if (object->isCreatureObject()) {
							creo = object->asCreatureObject();
							Locker clock(creo);
							creo->setMoodString(subCommand, true);
						} else
							creature->sendSystemMessage("ERROR: Target must be a creature.");
					} else {
						creature->sendSystemMessage("ERROR: Mood command requires that you specify an mood name.");
					}
				} else if (command == "anim") {
					if (args.hasMoreTokens()) {
						args.getStringToken(subCommand);
						BorEffect::PlayAnim(creature, server->getZoneServer()->getObject(target, false), true, subCommand);
					} else {
						creature->sendSystemMessage("ERROR: Anim command requires that you specify an animation name.");
					}
				} else if (command == "effect") {
					if (args.hasMoreTokens()) {
						args.getStringToken(subCommand);
						BorEffect::PlayCEF(creature, object, true, subCommand);
					} else
						creature->sendSystemMessage("ERROR: Effect command requires that you specify an effect name.");
				} else if(command == "createcreature") {
						if(args.hasMoreTokens()) {
							//Template
							String creatureTemplate;
							args.getStringToken(creatureTemplate);
							if(args.hasMoreTokens()) {
								String skillTemplate;
								args.getStringToken(skillTemplate);
								if(args.hasMoreTokens()) {
									String equipTemplate;
									args.getStringToken(equipTemplate);
									if(args.hasMoreTokens()) {
										String customTemplate;
										args.getStringToken(customTemplate);	
										//Spawn Full		
										BorUtil::CreateRoleplayNPC(creature, creatureTemplate, skillTemplate, equipTemplate, customTemplate);					
									} else {
										//Spawn with Skill and Equip
										BorUtil::CreateRoleplayNPC(creature, creatureTemplate, skillTemplate, equipTemplate, "");		
									}
								} else {
									//Spawn with Skill only
									BorUtil::CreateRoleplayNPC(creature, creatureTemplate, skillTemplate, "", "");		
								}
							} else {
								//Spawn Just the creature
								BorUtil::CreateRoleplayNPC(creature, creatureTemplate, "", "", "");		
							}
						} else {
							creature->sendSystemMessage("ERROR: /dm createcreature [<template>] <skill> <equipment> <customization>");
						}
				} else if (BorrieRPG::GetChatTypeID(command) != -1) {
					if (args.hasMoreTokens()) {
						String speech = arguments.toString().subString(1 + command.length(), arguments.toString().length());
						BorNPC::SpeakThroughNPC(creature, server->getZoneServer()->getObject(target, false), true, speech, BorrieRPG::GetChatTypeID(command));
					} else {
						creature->sendSystemMessage("Speech command requires you to say something!");
					}
				}
			}
			if (adminLevelCheck > 13) { // Privledged DM
				if (command == "name") {
					if (args.hasMoreTokens()) {
						String newName = arguments.toString().subString(1 + command.length(), arguments.toString().length());
						BorrieRPG::SetName(creature, object, newName);
					} else {
						
					}
						
				}
			}
			if (adminLevelCheck > 14) { // Full DM
				if (command == "setsecretdm") {
					if (object->isCreatureObject()) {
						creo = object->asCreatureObject();
						// Locker clock(creo);
						BorDM::SetSecretDM(creature, creo);
					} else {
						creature->sendSystemMessage("ERROR: You can only set secret DM on a creature.");
					}
				} else if (command == "togglecopy") {
					BorrieRPG::setCopyable(creature, object);
				}
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("Invalid arguments for DM command. Help: /dm help");
		}
		return SUCCESS;
	}

	void HelpDisplay(CreatureObject* creature) const {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		StringBuffer text;
		text << "-DM COMMAND-------------------" << endl;

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);
		box->setPromptTitle("DM COMMAND HELP");
		box->setPromptText(text.toString());
		ghost->addSuiBox(box);
		creature->sendMessage(box->generateMessage());
	}

};

#endif 
