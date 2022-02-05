#ifndef BORSKILL_H_
#define BORSKILL_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "engine/util/u3d/Coordinate.h"

//#include "templates/roleplay/RoleplayManager.h"

#include "server/db/ServerDatabase.h"

class BorSkill : public Logger {
public:
	static bool GetStringIsAttribute(String input) {
		if (input == "strength")
			return true;
		else if (input == "precision")
			return true;
		else if (input == "dexterity")
			return true;
		else if (input == "awareness")
			return true;
		else if (input == "intelligence")
			return true;
		else if (input == "charisma")
			return true;
		else if (input == "constitution")
			return true;
		else if (input == "mindfulness")
			return true;
		else
			return false;
	}

	static String GetSkillParent(String skill) {
		if (skill == "melee")
			return "strength";
		else if (skill == "intimidation")
			return "strength";
		else if (skill == "unarmed")
			return "strength";
		else if (skill == "lightsaber")
			return "strength";
		else if (skill == "ranged")
			return "precision";
		else if (skill == "mechanics")
			return "precision";
		else if (skill == "demolitions")
			return "precision";
		else if (skill == "engineering")
			return "precision";
		else if (skill == "larceny")
			return "dexterity";
		else if (skill == "stealth")
			return "dexterity";
		else if (skill == "maneuverability")
			return "dexterity";
		else if (skill == "throwing")
			return "dexterity";
		else if (skill == "investigation")
			return "awareness";
		else if (skill == "piloting")
			return "awareness";
		else if (skill == "survival")
			return "awareness";
		else if (skill == "sense")
			return "awareness";
		else if (skill == "slicing")
			return "intelligence";
		else if (skill == "computers")
			return "intelligence";
		else if (skill == "medicine")
			return "intelligence";
		else if (skill == "science")
			return "intelligence";
		else if (skill == "persuasion")
			return "charisma";
		else if (skill == "bluff")
			return "charisma";
		else if (skill == "composure")
			return "charisma";
		else if (skill == "resolve")
			return "charisma";
		else if (skill == "athletics")
			return "constitution";
		else if (skill == "lightning")
			return "constitution";
		else if (skill == "armor")
			return "constitution";
		else if (skill == "defending")
			return "constitution";
		else if (skill == "telekinesis")
			return "mindfulness";
		else if (skill == "control")
			return "mindfulness";
		else if (skill == "alter")
			return "mindfulness";
		else if (skill == "inward")
			return "mindfulness";
		else
			return "";
	}

	static bool GetStringIsSkill(String skill) {
		if (skill == "strength")
			return true;
		else if (skill == "precision")
			return true;
		else if (skill == "dexterity")
			return true;
		else if (skill == "awareness")
			return true;
		else if (skill == "intelligence")
			return true;
		else if (skill == "charisma")
			return true;
		else if (skill == "constitution")
			return true;
		else if (skill == "mindfulness")
			return true;
		else if (skill == "melee")
			return true;
		else if (skill == "intimidation")
			return true;
		else if (skill == "unarmed")
			return true;
		else if (skill == "lightsaber")
			return true;
		else if (skill == "ranged")
			return true;
		else if (skill == "mechanics")
			return true;
		else if (skill == "demolitions")
			return true;
		else if (skill == "engineering")
			return true;
		else if (skill == "larceny")
			return true;
		else if (skill == "stealth")
			return true;
		else if (skill == "maneuverability")
			return true;
		else if (skill == "throwing")
			return true;
		else if (skill == "investigation")
			return true;
		else if (skill == "piloting")
			return true;
		else if (skill == "survival")
			return true;
		else if (skill == "sense")
			return true;
		else if (skill == "slicing")
			return true;
		else if (skill == "computers")
			return true;
		else if (skill == "medicine")
			return true;
		else if (skill == "science")
			return true;
		else if (skill == "persuasion")
			return true;
		else if (skill == "bluff")
			return true;
		else if (skill == "composure")
			return true;
		else if (skill == "resolve")
			return true;
		else if (skill == "athletics")
			return true;
		else if (skill == "lightning")
			return true;
		else if (skill == "armor")
			return true;
		else if (skill == "defending")
			return true;
		else if (skill == "telekinesis")
			return true;
		else if (skill == "control")
			return true;
		else if (skill == "alter")
			return true;
		else if (skill == "inward")
			return true;
		else
			return false;
	}

	static String GetSkillRealName(String input) {
		StringTokenizer args(input);
		String output;
		args.setDelimeter("_");
		if (!args.hasMoreTokens())
			return "invalid";
		else {
			if(args.hasMoreTokens()) {
				args.getStringToken(output);
				return output;
			}
			else return "invalid";
		}
	}

	static int GetSkillLevelFromString(String input) {
		StringTokenizer args(input);
		String value;
		args.setDelimeter("_");
		if (!args.hasMoreTokens())
			return -1;
		else {
			if (args.hasMoreTokens()) { //skill name
				if (args.hasMoreTokens()) { //Skill Value
					args.getStringToken(value);
					if (value == "novice")
						return 1;
					else if (value == "a01")
						return 2;
					else if (value == "a02")
						return 3;
					else if (value == "a03")
						return 4;
					else if (value == "a04")
						return 5;
					else if (value == "b01")
						return 6;
					else if (value == "b02")
						return 7;
					else if (value == "b03")
						return 8;
					else if (value == "b04")
						return 9;
					else if (value == "master")
						return 10;
					else
						return 0;
				} else {
					return -1;
				}
			} else
				return -1;
		}
	}

	static bool GetQualifiedForSkill(CreatureObject* creature, String skill) {
		if (GetStringIsSkill(skill)) {
			int desiredLevel = GetSkillLevelFromString(skill);
			if (desiredLevel == -1)
				return false;
			String parent = GetSkillParent(skill);
			return creature->getSkillMod("rp_" + parent) >= desiredLevel;
		} else {
			return true;
		}
	}
};

#endif /*BORSKILL_H_*/