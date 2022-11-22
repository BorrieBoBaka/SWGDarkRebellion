object_building_ship_rp_yt1300 = object_building_ship_rp_shared_yt1300:new {
	entrancePoint = {0,0},
	entranceCell = 1,
	
	childObjects = {
		{templateFile = "object/tangible/ship/roleplay/terminal_navicomputer.iff", x = 11.803, z = 1.28999, y = 9.71386, cellid = 2, ow = 1, ox = 0, oy = 0, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = 3.4646, z = -1.69578, y = -1.97321, cellid = 6, ow = -4.37114e-08, ox = 0, oy = 1, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/ship/roleplay/terminal_ship_exit.iff", x = 13.7035, z = -1.6, y = -0.00259528, cellid = 1, ow = -0.707107, ox = 0, oy = 0.707107, oz = 0, containmentType = -1},
	},
}
ObjectTemplates:addTemplate(object_building_ship_rp_yt1300, "object/building/ship_rp/yt1300.iff")
