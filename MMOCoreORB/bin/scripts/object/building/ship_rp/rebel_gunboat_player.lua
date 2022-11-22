object_building_ship_rp_rebel_gunboat_player = object_building_ship_rp_shared_rebel_gunboat_player:new {
	entrancePoint = {0,36.8},
	entranceCell = 1,
	
	childObjects = {
		{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = -2.53253, z = 1.49877,  y = 11.5558, cellid = 1, ow = -1, ox = 0, oy = -5.96046e-08, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/ship/roleplay/terminal_ship_exit.iff", x = 0.0155094, z = 1.79857,  y = 7.43202, cellid = 2, ow = -1, ox = 0, oy = -5.96046e-08, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/ship/roleplay/terminal_navicomputer.iff", x = -0.54544, z = 3.11315,  y = 24.6716, cellid = 1, ow = 0.707107, ox = 0, oy = -0.707107, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/terminal/terminal_elevator.iff", x = 0.0372262, z = -3.50143,  y = -20.3572, cellid = 9, ow = 1, ox = 0, oy = 0, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/terminal/terminal_elevator.iff", x = 0.00347227, z = 1.49857,  y = -20.3089, cellid = 9, ow = 1, ox = 0, oy = 0, oz = 0, containmentType = -1},
	},
}
ObjectTemplates:addTemplate(object_building_ship_rp_rebel_gunboat_player, "object/building/ship_rp/rebel_gunboat_player.iff")
