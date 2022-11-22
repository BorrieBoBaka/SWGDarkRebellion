local spawnGroupTag = "generic"

spawn_group = {
	organic = {
		{"rp_aqualish_female", 10},
		{"rp_aqualish_male", 10},
		{"rp_bith_female", 10},
		{"rp_bith_male", 10},
		{"rp_bothan_female", 10},
		{"rp_bothan_male", 10},
		{"rp_chiss_female", 1},
		{"rp_chiss_male", 1},
		{"rp_devaronian_male", 10},
		{"rp_gotal_male", 10},
		{"rp_gran_male", 10},
		{"rp_human_male", 15},
		{"rp_human_female", 15},
		{"rp_ishi_tib_male", 10},
		{"rp_moncal_female", 10},
		{"rp_moncal_male", 10},
		{"rp_nautolan_male", 10},
		{"rp_nikto_male", 10},
		{"rp_quarren_male", 10},
		{"rp_rodian_female", 10},
		{"rp_rodian_male", 10},
		{"rp_sullustan_female", 10},
		{"rp_sullustan_male", 10},
		{"rp_trandoshan_female", 10},
		{"rp_trandoshan_male", 10},
		{"rp_twilek_female", 10},
		{"rp_twilek_male", 10},
		{"rp_weequay_male", 10},
		{"rp_zabrak_female", 10},
		{"rp_zabrak_male", 10},
	},
	droid = {
		{"r5", 10},
		{"r4", 10},
	}	
}

CivSpawnGroups:addCivSpawnGroup(spawnGroupTag, spawn_group)