--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_mandalorian_armor_mandalorian_helmet_lite = object_tangible_wearables_armor_mandalorian_shared_armor_mandalorian_helmet:new {


	customObjectName = "Durasteel Mandalorian Helmet",

	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 100,


	rating = LIGHT,
	rpskill = 5,


	kinetic = 2,
	energy = 4,
	electricity = 0,
	stun = 1,
	blast = -4,
	heat = 1,
	cold = -2,
	acid = -1,
	lightsaber = 0,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_mandalorian_armor_mandalorian_helmet_lite, "object/tangible/wearables/armor/roleplay/mandalorian/armor_mandalorian_helmet_lite.iff")
