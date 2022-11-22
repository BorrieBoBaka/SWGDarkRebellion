--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_ubese_armor_ubese_boots = object_tangible_wearables_armor_ubese_shared_armor_ubese_boots:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 100,


	rating = NONE,
	rpskill = 6,


	kinetic = 2,
	energy = 2,
	electricity = 6,
	stun = -2,
	blast = -4,
	heat = 6,
	cold = 6,
	acid = 4,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_ubese_armor_ubese_boots, "object/tangible/wearables/armor/roleplay/ubese/armor_ubese_boots.iff")
