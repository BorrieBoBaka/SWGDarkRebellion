planet = {
	name = "Xovros VI",
	zone = "rp_xovros6",
	startingFaction = "empire",
	startingFactionControl = 40,
	bases = {

	},
	
	landing_points = {
		--Tag, Name, Zone, x, z, y, angle, cell, shipVisible
		{"xovros_reiden_starport", "Reiden Outpost Starport", "rp_xovros6", -5306, 28, -2829, -90, 0, true},
	}	
}

BorPlanetManager:addPlanet(planet)