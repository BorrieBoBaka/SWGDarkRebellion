--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_ithorian_guardian_ith_armor_s02_gloves = object_tangible_wearables_armor_ithorian_guardian_shared_ith_armor_s02_gloves:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 200,


	rating = NONE,
	rpskill = 0,


	kinetic = 2,
	energy = 2,
	electricity = 0,
	stun = 0,
	blast = 0,
	heat = 0,
	cold = 0,
	acid = 0,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_ithorian_guardian_ith_armor_s02_gloves, "object/tangible/wearables/armor/roleplay/ithorian_guardian/ith_armor_s02_gloves.iff")
