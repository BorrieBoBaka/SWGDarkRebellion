--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_rebel_snow_armor_rebel_snow_bicep_r = object_tangible_wearables_armor_rebel_snow_shared_armor_rebel_snow_bicep_r:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 100,


	rating = NONE,
	rpskill = 3,


	kinetic = 1,
	energy = 1,
	electricity = 0,
	stun = 4,
	blast = -4,
	heat = -2,
	cold = 8,
	acid = 0,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_rebel_snow_armor_rebel_snow_bicep_r, "object/tangible/wearables/armor/roleplay/rebel_snow/armor_rebel_snow_bicep_r.iff")
