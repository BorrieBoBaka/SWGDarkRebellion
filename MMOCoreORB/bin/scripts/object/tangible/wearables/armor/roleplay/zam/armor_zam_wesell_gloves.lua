--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_zam_armor_zam_wesell_gloves = object_tangible_wearables_armor_zam_shared_armor_zam_wesell_gloves:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 65,


	rating = NONE,
	rpskill = 0,


	kinetic = 0,
	energy = 4,
	electricity = 4,
	stun = 2,
	blast = -8,
	heat = 1,
	cold = 1,
	acid = -4,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_zam_armor_zam_wesell_gloves, "object/tangible/wearables/armor/roleplay/zam/armor_zam_wesell_gloves.iff")
