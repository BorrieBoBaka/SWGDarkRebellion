--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_bounty_hunter_armor_bounty_hunter_bicep_l = object_tangible_wearables_armor_bounty_hunter_shared_armor_bounty_hunter_bicep_l:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 200,


	rating = LIGHT,
	rpskill = 6,


	kinetic = 2,
	energy = 6,
	electricity = -4,
	stun = 6,
	blast = -4,
	heat = 2,
	cold = 2,
	acid = 2,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_bounty_hunter_armor_bounty_hunter_bicep_l, "object/tangible/wearables/armor/roleplay/bounty_hunter/armor_bounty_hunter_bicep_l.iff")
