object_building_ship_rp_ykl37r = object_building_ship_rp_shared_ykl37r:new {
	entrancePoint = {0,0},
	entranceCell = 1,
	
	publicStructure = 0,
	baseMaintenanceRate = 0,
	
	childObjects = {
		{templateFile = "object/tangible/ship/roleplay/terminal_navicomputer.iff", x = -18.8275, z = -1.17445, y = 1.23132, cellid = 1, ow = 0.707107, ox = 0, oy = 0.707107, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = -17.7158, z = -2.24382, y = -8.85196, cellid = 2, ow = -1, ox = 0, oy = 0, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/ship/roleplay/terminal_ship_exit.iff", x = 5.20379, z = -1.47289, y = -5.11104, cellid = 4, ow = 1, ox = 0, oy = 0, oz = 0, containmentType = -1},
	},
}
ObjectTemplates:addTemplate(object_building_ship_rp_ykl37r, "object/building/ship_rp/ykl37r.iff")
