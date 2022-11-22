object_building_ship_rp_imperial_gunboat_player = object_building_ship_rp_shared_imperial_gunboat_player:new {
	entrancePoint = {0,0},
	entranceCell = 1,
	
	childObjects = {
		{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = 3.43967, z = 2.52505, y = 37.2039, cellid = 1, ow = 1, ox = 0, oy = 0, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/ship/roleplay/terminal_navicomputer.iff", x = -3.60997, z = 3.03505, y = 37.2066, cellid = 1, ow = -1, ox = 0, oy = 0, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/ship/roleplay/terminal_ship_exit.iff", x = 0.00068176, z = 1.35005, y = 45.4198, cellid = 1, ow = -4.37114e-08, ox = 0, oy = 1, oz = 0, containmentType = -1},
	},
}
ObjectTemplates:addTemplate(object_building_ship_rp_imperial_gunboat_player, "object/building/ship_rp/imperial_gunboat_player.iff")
