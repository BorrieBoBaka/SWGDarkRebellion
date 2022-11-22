local spawnGroupTag = "sulon"

spawn_group = {
	organic = {
		{"rp_aqualish_female", 10},
		{"rp_aqualish_male", 10},
		{"rp_bith_female", 10},
		{"rp_bith_male", 10},
		{"rp_bothan_female", 12},
		{"rp_bothan_male", 12},
		{"rp_devaronian_male", 5},
		{"rp_gotal_male", 10},
		{"rp_gran_male", 10},
		{"rp_human_male", 100},
		{"rp_human_female", 100},
		{"rp_ishi_tib_male", 10},
		{"rp_moncal_female", 10},
		{"rp_moncal_male", 10},
		{"rp_nautolan_male", 10},
		{"rp_nikto_male", 4},
		{"rp_quarren_male", 10},
		{"rp_rodian_female", 2},
		{"rp_rodian_male", 2},
		{"rp_sullustan_female", 100},
		{"rp_sullustan_male", 100},
		{"rp_twilek_female", 6},
		{"rp_twilek_male", 6},
		{"rp_zabrak_female", 5},
		{"rp_zabrak_male", 5},
	},
	droid = {
		{"r5", 10},
		{"r4", 10},
	}	
}

CivSpawnGroups:addCivSpawnGroup(spawnGroupTag, spawn_group)