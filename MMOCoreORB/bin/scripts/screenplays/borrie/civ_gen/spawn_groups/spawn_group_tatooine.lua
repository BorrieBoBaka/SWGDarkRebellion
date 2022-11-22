local spawnGroupTag = "tatooine"

spawn_group = {
	organic = {
		{"rp_aqualish_female", 50},
		{"rp_aqualish_male", 50},
		{"rp_bith_female", 5},
		{"rp_bith_male", 6},
		{"rp_bothan_female", 12},
		{"rp_bothan_male", 12},
		{"rp_chiss_female", 1},
		{"rp_chiss_male", 1},
		{"rp_devaronian_male", 25},
		{"rp_gotal_male", 10},
		{"rp_gran_male", 50},
		{"rp_human_male", 75},
		{"rp_human_female", 75},
		{"rp_ishi_tib_male", 10},
		{"rp_moncal_female", 2},
		{"rp_moncal_male", 2},
		{"rp_nautolan_male", 1},
		{"rp_nikto_male", 45},
		{"rp_quarren_male", 5},
		{"rp_rodian_female", 35},
		{"rp_rodian_male", 40},
		{"rp_sullustan_female", 10},
		{"rp_sullustan_male", 10},
		{"rp_trandoshan_female", 20},
		{"rp_trandoshan_male", 20},
		{"rp_twilek_female", 55},
		{"rp_twilek_male", 55},
		{"rp_weequay_male", 55},
		{"rp_zabrak_female", 20},
		{"rp_zabrak_male", 20},
	},
	droid = {
		{"r5", 10},
		{"r4", 10},
	}	
}

CivSpawnGroups:addCivSpawnGroup(spawnGroupTag, spawn_group)