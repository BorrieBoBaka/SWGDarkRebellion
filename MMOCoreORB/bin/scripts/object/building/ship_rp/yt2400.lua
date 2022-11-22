object_building_ship_rp_yt2400 = object_building_ship_rp_shared_yt2400:new {
	entrancePoint = {23.7,5.9},
	entranceCell = 1,
	
	childObjects = {
		{templateFile = "object/tangible/ship/roleplay/terminal_ship_exit.iff", x = 13.231, z = 0.00637531, y = 3.00586, cellid = 5, ow = -0.707107, ox = 0, oy = 0.707107, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = 26.8363, z = -1.11831, y = 8.02536, cellid = 1, ow = 0.707107, ox = 0, oy = -0.707107, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/ship/roleplay/terminal_navicomputer.iff", x = 25.0029, z = 0.331691, y = 14.5164, cellid = 1, ow = 0, ox = 0, oy = 1, oz = 0, containmentType = -1},
	},
}
ObjectTemplates:addTemplate(object_building_ship_rp_yt2400, "object/building/ship_rp/yt2400.iff")
