planet = {
	name = "Sulon",
	zone = "rp_sulon",
	startingFaction = "empire",
	startingFactionControl = 25,
	bases = {

	},
	
	landing_points = {
		--Tag, Name, Zone, x, z, y, angle, cell, shipVisible
		{"saltalo_station_outskirts_a", "Saltalo Station A", "rp_sulon", 4478, 13.3, -5402, -90, 0, true},
		{"akarlo_fueling_station", "Akarlo Fueling Station", "rp_sulon", 5367, 8, -5743, 0, 0, true},
	}	
}

BorPlanetManager:addPlanet(planet)