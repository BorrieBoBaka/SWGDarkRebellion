--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_mandalorian_rebel_armor_mandalorian_rebel_gloves = object_tangible_wearables_armor_mandalorian_rebel_shared_armor_mandalorian_rebel_gloves:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 400,


	rating = LIGHT,
	rpskill = 7,


	kinetic = 6,
	energy = 8,
	electricity = 0,
	stun = 2,
	blast = -4,
	heat = 0,
	cold = -2,
	acid = 0,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_mandalorian_rebel_armor_mandalorian_rebel_gloves, "object/tangible/wearables/armor/roleplay/mandalorian_rebel/armor_mandalorian_rebel_gloves.iff")
