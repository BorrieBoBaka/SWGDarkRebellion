--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_marine_armor_marine_gloves = object_tangible_wearables_armor_marine_shared_armor_marine_gloves:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 100,


	rating = NONE,
	rpskill = 4,


	kinetic = 3,
	energy = 3,
	electricity = 2,
	stun = 2,
	blast = -4,
	heat = 0,
	cold = -2,
	acid = -2,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_marine_armor_marine_gloves, "object/tangible/wearables/armor/roleplay/marine/armor_marine_gloves.iff")
