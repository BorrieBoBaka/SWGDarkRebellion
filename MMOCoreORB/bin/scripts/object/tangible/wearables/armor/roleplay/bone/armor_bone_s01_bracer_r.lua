--Armor template file for Borrie BoBaka's SWGEmu RPG System--


object_tangible_wearables_armor_roleplay_bone_armor_bone_s01_bracer_r = object_tangible_wearables_armor_bone_shared_armor_bone_s01_bracer_r:new {


	templateType = ARMOROBJECT,


	objectMenuComponent  = "ArmorObjectMenuComponent",


	healthEncumbrance = 0,
	armorEncumbrance = 0,
	mindEncumbrance = 0,


	maxCondition = 20,


	rating = NONE,
	rpskill = 0,


	kinetic = 2,
	energy = 2,
	electricity = 2,
	stun = 1,
	blast = -4,
	heat = 0,
	cold = -2,
	acid = -4,
	lightsaber = -1,


}


ObjectTemplates:addTemplate(object_tangible_wearables_armor_roleplay_bone_armor_bone_s01_bracer_r, "object/tangible/wearables/armor/roleplay/bone/armor_bone_s01_bracer_r.iff")
