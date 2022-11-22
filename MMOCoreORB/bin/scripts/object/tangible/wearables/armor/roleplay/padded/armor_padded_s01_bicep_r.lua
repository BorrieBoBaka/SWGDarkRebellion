--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_padded_armor_padded_s01_bicep_r = object_tangible_wearables_armor_padded_shared_armor_padded_s01_bicep_r:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 80,


	rating = NONE,
	rpskill = 0,


	kinetic = 4,
	energy = 2,
	electricity = 4,
	stun = 0,
	blast = 0,
	heat = -2,
	cold = 4,
	acid = -4,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_padded_armor_padded_s01_bicep_r, "object/tangible/wearables/armor/roleplay/padded/armor_padded_s01_bicep_r.iff")
