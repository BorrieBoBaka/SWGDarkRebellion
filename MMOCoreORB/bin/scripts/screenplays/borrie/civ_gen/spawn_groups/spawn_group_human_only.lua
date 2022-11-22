local spawnGroupTag = "human_only"

spawn_group = {
	organic = {
		{"rp_human_male", 10},
		{"rp_human_female", 10},
	},
	droid = {
		{"r5", 10},
		{"r4", 10},
	}	
}

CivSpawnGroups:addCivSpawnGroup(spawnGroupTag, spawn_group)