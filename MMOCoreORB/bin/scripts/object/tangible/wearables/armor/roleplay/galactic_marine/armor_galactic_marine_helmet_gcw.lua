--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_galactic_marine_armor_galactic_marine_helmet_gcw = object_tangible_wearables_armor_galactic_marine_shared_armor_galactic_marine_helmet_gcw:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 150,


	rating = LIGHT,
	rpskill = 6,


	kinetic = 4,
	energy = 4,
	electricity = -2,
	stun = -2,
	blast = -4,
	heat = 6,
	cold = 6,
	acid = 6,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_galactic_marine_armor_galactic_marine_helmet_gcw, "object/tangible/wearables/armor/roleplay/galactic_marine/armor_galactic_marine_helmet_gcw.iff")
