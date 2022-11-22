--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_marauder_a_armor_marauder_s01_helmet = object_tangible_wearables_armor_marauder_shared_armor_marauder_s01_helmet:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 30,


	rating = LIGHT,
	rpskill = 4,


	kinetic = 6,
	energy = 0,
	electricity = 0,
	stun = 2,
	blast = -4,
	heat = 0,
	cold = 0,
	acid = -2,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_marauder_a_armor_marauder_s01_helmet, "object/tangible/wearables/armor/roleplay/marauder_a/armor_marauder_s01_helmet.iff")
