--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_snow_trooper_armor_snowtrooper_helmet = object_tangible_wearables_armor_snowtrooper_shared_armor_snowtrooper_helmet:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 150,


	rating = LIGHT,
	rpskill = 5,


	kinetic = 4,
	energy = 4,
	electricity = 0,
	stun = 0,
	blast = -4,
	heat = -4,
	cold = 8,
	acid = 0,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_snow_trooper_armor_snowtrooper_helmet, "object/tangible/wearables/armor/roleplay/snow_trooper/armor_snowtrooper_helmet.iff")
