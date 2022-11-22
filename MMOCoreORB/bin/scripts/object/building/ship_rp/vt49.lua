object_building_ship_rp_vt49 = object_building_ship_rp_shared_vt49:new {
	entrancePoint = {0,0},
	entranceCell = 1,
	
	childObjects = {	
		{templateFile = "object/tangible/ship/roleplay/terminal_navicomputer.iff", x = -2.2277, z = 3.66616, y = 0.784991, cellid = 1, ow = -1, ox = 0, oy = 0, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/ship/roleplay/terminal_ship_exit.iff", x = -7.78854, z = -1.5, y = 2.07172, cellid = 2, ow = 0, ox = 0, oy = -1, oz = 0, containmentType = -1},
		{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = 3.17291, z = -1.67779, y = -4.19981, cellid = 2, ow = -1, ox = 0, oy = -5.96046e-08, oz = 0, containmentType = -1},
	},
}
ObjectTemplates:addTemplate(object_building_ship_rp_vt49, "object/building/ship_rp/vt49.iff")
