--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_marauder_b_armor_marauder_s02_bracer_r = object_tangible_wearables_armor_marauder_shared_armor_marauder_s02_bracer_r:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 30,


	rating = NONE,
	rpskill = 2,


	kinetic = 4,
	energy = 2,
	electricity = 2,
	stun = 2,
	blast = -2,
	heat = 0,
	cold = 0,
	acid = -4,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_marauder_b_armor_marauder_s02_bracer_r, "object/tangible/wearables/armor/roleplay/marauder_b/armor_marauder_s02_bracer_r.iff")
