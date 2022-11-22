--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_ris_armor_ris_chest_plate = object_tangible_wearables_armor_ris_shared_armor_ris_chest_plate:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 500,


	rating = MEDIUM,
	rpskill = 10,


	kinetic = 8,
	energy = 6,
	electricity = -4,
	stun = 6,
	blast = -4,
	heat = 0,
	cold = 2,
	acid = 2,
	lightsaber = 1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_ris_armor_ris_chest_plate, "object/tangible/wearables/armor/roleplay/ris/armor_ris_chest_plate.iff")
