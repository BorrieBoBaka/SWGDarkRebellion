planet = {
	name = "Tatooine",
	zone = "rp_tatooine",
	startingFaction = "empire",
	startingFactionControl = 70,
	bases = {
		"eisley_base_main",
		"eisley_base_slum",
		"eisley_base_palace",
	},
	
	landing_points = {
		--Tag, Name, Zone, x, z, y, angle, cell, shipVisible
		{"eisley_spaceport", "Mos Eisley Spaceport", "rp_tatooine", 1110, 0, -63, -45, 0, true},
		{"jabbas_palace", "Hutt Palace", "rp_tatooine", 3399, 50, -6817, -90, 0, true},
	}	
}

BorPlanetManager:addPlanet(planet)