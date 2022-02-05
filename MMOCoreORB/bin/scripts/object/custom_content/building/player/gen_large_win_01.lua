object_building_player_generic_large_window_s01 = object_building_player_shared_generic_large_window_s01:new {
	lotSize = 2,
	baseMaintenanceRate = 0,
    allowedZones = {"chandrila", "corellia", "dantooine", "dathomir", "endor", "lok", "naboo", "rori", "taanab", "talus", "hoth", "kaas", "mandalore", "moraband", "tatooine", "yavin4", "hutta"},
	constructionMarker = "object/building/player/construction/construction_player_house_corellia_large_style_01.iff",
	length = 1,
	width = 1,
	publicStructure = 0,
	skillMods = {
		{"private_medical_rating", 100},
		{"private_buff_mind", 100},
		{"private_med_battle_fatigue", 15}
	},
	childObjects = {
			{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = 9.24998, z = 4.435, y = -6.06134, ow = 0.707107, ox = 0, oz = 0, oy = -0.707107, cellid = 3, containmentType = -1},
			{templateFile = "object/tangible/sign/player/house_address.iff", x = -13.71, z = 3.97, y = 9.15, ox = 0, oy = 1, oz = 0, ow = 0, cellid = -1, containmentType = -1}
	},
	shopSigns = {
			{templateFile = "object/tangible/sign/player/house_address.iff", x = -13.71, z = 3.97, y = 9.15, ox = 0, oy = 1, oz = 0, ow = 0, cellid = -1, containmentType = -1, requiredSkill = "", suiItem = "@player_structure:house_address"},			
			{templateFile = "object/tangible/sign/player/shop_sign_s01.iff", x = -13.85, z = 0.49, y = 18.00, ox = 0, oy = 0, oz = 0, ow =  1, cellid = -1, containmentType = -1, requiredSkill = "", suiItem = "@player_structure:shop_sign1"},
			{templateFile = "object/tangible/sign/player/shop_sign_s02.iff", x = -13.85, z = 0.49, y = 18.00, ox = 0, oy = 0, oz = 0, ow =  1, cellid = -1, containmentType = -1, requiredSkill = "", suiItem = "@player_structure:shop_sign2"},
			{templateFile = "object/tangible/sign/player/shop_sign_s03.iff", x = -13.85, z = 0.49, y = 18.00, ox = 0, oy = 0, oz = 0, ow =  1, cellid = -1, containmentType = -1, requiredSkill = "", suiItem = "@player_structure:shop_sign3"},
			{templateFile = "object/tangible/sign/player/shop_sign_s04.iff", x = -13.85, z = 0.49, y = 18.00, ox = 0, oy = 0, oz = 0, ow =  1, cellid = -1, containmentType = -1, requiredSkill = "", suiItem = "@player_structure:shop_sign4"},			
	},	
	constructionMarker = "object/building/player/construction/construction_player_house_corellia_large_style_01.iff",
	length = 5,
	width = 7
}

ObjectTemplates:addTemplate(object_building_player_generic_large_window_s01, "object/building/player/generic_large_window_s01.iff")
