--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_chitin_armor_chitin_s01_bracer_r = object_tangible_wearables_armor_chitin_shared_armor_chitin_s01_bracer_r:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 60,


	rating = LIGHT,
	rpskill = 0,


	kinetic = 6,
	energy = 2,
	electricity = 0,
	stun = 2,
	blast = 2,
	heat = 0,
	cold = 0,
	acid = -6,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_chitin_armor_chitin_s01_bracer_r, "object/tangible/wearables/armor/roleplay/chitin/armor_chitin_s01_bracer_r.iff")
