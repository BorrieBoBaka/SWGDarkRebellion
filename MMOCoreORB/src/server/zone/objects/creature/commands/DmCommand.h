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
				} else if(command == "teleport") { 
					BorUtil::NoLoadscreenTeleport(creature, arguments);
				} else if(command == "teleportto") { 
					BorUtil::NoLoadscreenTeleportTo(creature, arguments);
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
				} else if(command == "limbo") {
					BorrieRPG::teleportObject(creature, object, 7500, 0, 7500, -2);
					creature->sendSystemMessage("Target sent to 7500, 7500 on the planet (WIP Limbo)");
				} else if(command == "delete" || command == "despawn") {
					BorrieRPG::DeleteCreature(object->asCreatureObject());
				}
			}
			if (adminLevelCheck > 2) { // Assistant DM
				if (command == "msg") {
					BorDM::sendMessage(creature, target, adminLevelCheck, arguments.toString());
				} else if(command == "ooc" || command == "(" || command == "//") {
					BorDM::SendDungeonMasterOOC(creature, command, arguments.toString());
				} else if(command == "ic" || command == "--" || command == "[") {
					BorDM::SendDungeonMasterIC(creature, command, arguments.toString());
				}else if (command == "storetarget") {
					if (object != nullptr)
						BorrieRPG::SaveTarget(creature, object);
					else
						creature->sendSystemMessage("You need a target in order to save it.");
				} else if(command == "who") {
					BorrieRPG::ListOnlineCharacters(creature, true);
				} else if(command == "togglewalk") { 
					if(object != nullptr) {
						if(object->isCreatureObject()) {
							BorNPC::ToggleAIWalks(object->asCreatureObject(), creature);
						}
					}					
				} else if(command == "setposture" || command == "posture") {
					if(args.hasMoreTokens()) {
						if(object != nullptr) {
							if(object->isCreatureObject()) {
								args.getStringToken(subCommand);
								BorNPC::SetNPCPosture(object->asCreatureObject(), subCommand);
							} else {
								creature->sendSystemMessage("You need to target a creature to set its posture.");
							}
						} else {
							creature->sendSystemMessage("You need to have a target to set its posture.");
						}
					} else {
						creature->sendSystemMessage("You need to specify the posture you want to set. Ex: standing, kneeling, prone, sneaking, sitting, knockdown, dead");
					}
				} else if (command == "reward" || command == "award") { 
					if(args.hasMoreTokens()) {
						if(object != nullptr) {
							if(object->isCreatureObject()) {
								args.getStringToken(subCommand);
								if(args.hasMoreTokens()) {
									args.getStringToken(subSubCommand);
									if(subCommand == "roll" || subCommand == "exp") { //Input the last roll
										if(args.hasMoreTokens()) {
											String rollValue;
											args.getStringToken(rollValue);
											BorCharacter::RewardXPForRoll(object->asCreatureObject(), creature, subSubCommand, Integer::valueOf(rollValue));
										}										
									} else if(subCommand == "credits") { //Input a multiplier
										BorCharacter::RewardCreditsByLevel(object->asCreatureObject(), creature, Integer::valueOf(subSubCommand));
									} else if(subCommand == "genexp") { //Input an amount

									} else {
										creature->sendSystemMessage("You can reward a roll, credits, or general experience.");
									}
								} else {
									if(subCommand == "lastroll") {
										BorCharacter::RewardXPForLastRoll(object->asCreatureObject(), creature);
									} else if(subCommand == "credits") {
										BorCharacter::RewardCreditsByLevel(object->asCreatureObject(), creature);
									} else if(subCommand == "genexp") {

									} else {
										creature->sendSystemMessage("You can reward the lastroll, credits, or general experience.");
									}
								}
								
							} else {

							}
						} else {
							creature->sendSystemMessage("You need to target a creature to reward it.");
						}
					} else {
						creature->sendSystemMessage("You need to specify if you'd like to reward exp, the last roll, credits, or general roleplay experience.");
					}
				} else if(command == "togglenotify") {
					if(creature->getStoredInt("dm_alert_incoming") == 1) {
						creature->setStoredInt("dm_alert_incoming", 0);
						creature->sendSystemMessage("You will no longer be alerted to all incoming and outgoing players.");
					} else {
						creature->setStoredInt("dm_alert_incoming", 1);
						creature->sendSystemMessage("You will now be alerted to all incoming and outgoing players.");
					}
				} else if(command == "inspect") {
					if(object != nullptr) {
						if (object->isCreatureObject()) {
							BorCharacter::InspectPlayer(creature, object->asCreatureObject());
						}						
					}					
				} else if(command == "status") { 
					if(args.hasMoreTokens()) {
						args.getStringToken(subCommand);
						if(subCommand == "clear") {
							creature->deleteStoredString("rp_dm_status");
							creature->sendSystemMessage("You've cleared your DM Status.");
						}
					} else {
						BorrieRPG::SetDMStatus(creature);
					}
				} else if (command == "mood") {
					if (args.hasMoreTokens()) {
						args.getStringToken(subCommand);
						if(object != nullptr) {
							if (object->isCreatureObject()) {
							creo = object->asCreatureObject();
							Locker clock(creo);
							creo->setMoodString(subCommand, true);
						} else
							creature->sendSystemMessage("ERROR: Target must be a creature.");
						} else {
							creature->sendSystemMessage("ERROR: Must have a target to set its mood.");
						}
						
					} else {
						creature->sendSystemMessage("ERROR: Mood command requires that you specify an mood name.");
					}
				} else if (command == "anim") {
					if (args.hasMoreTokens() && object != nullptr) {
						args.getStringToken(subCommand);
						BorEffect::PlayAnim(creature, server->getZoneServer()->getObject(target, false), true, subCommand);
					} else {
						creature->sendSystemMessage("ERROR: Anim command requires that you specify an animation name.");
					}
				} else if (command == "effect") {
					if (args.hasMoreTokens() && object != nullptr) {
						args.getStringToken(subCommand);
						BorEffect::PlayCEF(creature, object, true, subCommand);
					} else
						creature->sendSystemMessage("ERROR: Effect command requires that you specify an effect name.");
				} else if(command == "createcreature") {
						if(args.hasMoreTokens()) {
							//Template
							String creatureTemplate;
							args.getStringToken(creatureTemplate);
							creatureTemplate = "object/mobile/" + creatureTemplate + ".iff"; 
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
				} else if(command == "createnpc") { 
					if(args.hasMoreTokens()) {
						//Template
						String npcTemplate;
						args.getStringToken(npcTemplate);
						CreatureObject* newNPC = BorUtil::CreateTemplatedRoleplayNPC(creature, npcTemplate);
						if(newNPC == nullptr) {
							creature->sendSystemMessage("Something went wrong creating the NPC \"" + npcTemplate + ".\" Did you use the wrong template, or one that doesn't exist?");
						}
					} else {
						creature->sendSystemMessage("ERROR: /dm createnpc [<template>]");
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
						if(object != nullptr) {
							String newName = arguments.toString().subString(1 + command.length(), arguments.toString().length());
							BorrieRPG::SetName(creature, object, newName);
						}						
					} else {
						creature->sendSystemMessage("You need to input a name!");
					}						
				} else if(command == "randomname") { 
					if(args.hasMoreTokens()) {
						String specific;
						args.getStringToken(specific);
						if(specific == "help") {
							creature->sendSystemMessage("/dm randomname <type> - Valid Types: stormtrooper, scouttrooper, darktrooper, swamptrooper, r2, r3, r4, r5, r6, r7, r8, r9, 3po, eg6, wed, le, ra7, human, rodian, trandoshan, moncal, wookiee, bothan, twilek, zabrak, ithorian, sullustan");
						} else {
							BorrieRPG::SetRandomName(creature, object, specific);
						}
					}
				} else if(command == "grantpoint") {
					if(object != nullptr) {
						if(object->isCreatureObject()) {
							if(args.hasMoreTokens()) {
								String specific;
								args.getStringToken(specific);
								if(specific == "attribute") {
									BorCharacter::ModifyFreePoints(creature, object->asCreatureObject(), "attr", 1);
								} else if(specific == "skill") {
									BorCharacter::ModifyFreePoints(creature, object->asCreatureObject(), "skill", 1);
								}
							} else {
								creature->sendSystemMessage("You need to specify 'attribute' or 'skill' when using '/dm grantpoint' ex: '/dm grantpoint skill'");
							}
						} else {
							creature->sendSystemMessage("You need a creature target to use this ability.");
						}
					} else {
						creature->sendSystemMessage("You need a creature target to use this ability.");
					}					
				} else if(command == "removepoint") {
					if(object != nullptr) {
						if(object->isCreatureObject()) {
							if(args.hasMoreTokens()) {
								String specific;
								args.getStringToken(specific);
								if(specific == "attribute") {
									BorCharacter::ModifyFreePoints(creature, object->asCreatureObject(), "attr", -1);
								} else if(specific == "skill") {
									BorCharacter::ModifyFreePoints(creature, object->asCreatureObject(), "skill", -1);
								}
							} else {
								creature->sendSystemMessage("You need to specify 'attribute' or 'skill' when using '/dm removepoint' ex: '/dm removepoint skill'");
							}
						} else {
							creature->sendSystemMessage("You need a creature target to use this ability.");
						}
					} else {
						creature->sendSystemMessage("You need a creature target to use this ability.");
					}
				} else if(command == "exp") {
					if(object != nullptr) {
						if(object->isCreatureObject()) {
							if(args.hasMoreTokens())  {
								int amount;
								amount = args.getIntToken();
								if(amount > 0) {
									BorCharacter::RewardGeneralRPExperience(object->asCreatureObject(), creature, amount);
								}
							} else {
								creature->sendSystemMessage("You need to specify an amount of experience to give.");
							}
						} else {
							creature->sendSystemMessage("You need a creature target to use this ability.");
						}
					} else {
						creature->sendSystemMessage("You need a creature target to use this ability.");
					}
				} else if(command == "setjedi") {
					if(object != nullptr) {
						if(object->isCreatureObject()) {
							BorCharacter::ToggleJedi(creature, object->asCreatureObject());
						} else {
							creature->sendSystemMessage("Target must be a creature");
						}
					} else {
						creature->sendSystemMessage("You must have a target to do that.");
					}
				} else if(command == "faction") { 
					if(object != nullptr) {
						if(object->isCreatureObject()) {
							if(object->isPlayerCreature()) {
								if(args.hasMoreTokens())  {
									String specific;
									args.getStringToken(specific);
									if(specific == "resetreport") {
										BorCharacter::ResetFactionReportCooldown(object->asCreatureObject(), creature);
									} else if(specific == "daily") {
										if(args.hasMoreTokens()) {
											int amount;
											amount = args.getIntToken();
											BorCharacter::ModifyDailyFactionContribution(object->asCreatureObject(), creature, amount);
										}
									} else if(specific == "overall") {
										if(args.hasMoreTokens()) {
											int amount;
											amount = args.getIntToken();
											BorCharacter::ModifyOverallFactionLoyalty(object->asCreatureObject(), creature, amount);
										}
									} else if(specific == "rank") {
										if(args.hasMoreTokens()) {
											int amount;
											amount = args.getIntToken();
										}
									}
								}
							}							
						}
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
			creature->sendSystemMessage("Error: " + String(e.what()) + " - " + e.getMessage());
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
