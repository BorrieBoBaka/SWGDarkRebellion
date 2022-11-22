--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_clone_trooper_armor_clone_trooper_neutral_s01_chest_plate = object_tangible_wearables_armor_clone_trooper_shared_armor_clone_trooper_neutral_s01_chest_plate:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 150,


	rating = LIGHT,
	rpskill = 4,


	kinetic = 4,
	energy = 4,
	electricity = 0,
	stun = 2,
	blast = -4,
	heat = -2,
	cold = -4,
	acid = -4,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_clone_trooper_armor_clone_trooper_neutral_s01_chest_plate, "object/tangible/wearables/armor/roleplay/clone_trooper/armor_clone_trooper_neutral_s01_chest_plate.iff")
