--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_scout_trooper_armor_scout_trooper_boots_camo = object_tangible_wearables_armor_scout_trooper_shared_armor_scout_trooper_boots_camo:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 100,


	rating = NONE,
	rpskill = 3,


	kinetic = 2,
	energy = 2,
	electricity = 0,
	stun = 2,
	blast = -4,
	heat = 2,
	cold = 2,
	acid = -4,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_scout_trooper_armor_scout_trooper_boots_camo, "object/tangible/wearables/armor/roleplay/scout_trooper/armor_scout_trooper_boots_camo.iff")
