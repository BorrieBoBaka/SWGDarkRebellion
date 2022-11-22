DevSpawnScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DevSpawn",

	planet = "rp_testing",	
}

function DevSpawnScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
		self:spawnSceneObjects()
		self:generateCivilians()
	end
end

registerScreenPlay("DevSpawnScreenPlay",  true)

function DevSpawnScreenPlay:generateCivilians() 
	local waypointList = {
		--{x,z,y,cell,angle,{tags}}
		{0,0,0,0,0,{"social"}},
		{2,0,2,0,0,{"social"}},
		{-2,0,-2,0,0,{"social"}},
		{-2,0,2,0,0,{"drinker"}},
		{2,0,-2,0,0,{"sit"}},
		{3,0,-3,0,0,{"sitchair"}},
		{6,0,-6,0,0,{"sittable"}},
	}
	
	--(tag,x,z,y,cell)
	local walkpointList = {
		
	}
	
	CivillianGenerator:spawnCivillians("rp_testing", waypointList, walkpointList, "generic", "sulon")
end

function DevSpawnScreenPlay:spawnSceneObjects()
	local sObj = spawnTeleporterTerminal("Debug Dev Teleporter", "object/tangible/terminal/teleport/terminal_teleporter_s01.iff", 10, 0, 10, 0, "rp_testing", 0,0,0,0,100,0,100,0,"rp_testing")
	SceneObject(sObj):setCustomObjectName("Debug Teleport Terminal!")
	
end

function DevSpawnScreenPlay:spawnMobiles() 
	pNpc = spawnRoleplayMobile("rp_testing", "rp_base_npc", 1, 15, 0, 15, 0, 0, "rp_rodian_male", "xovros_mechanic", "default", "xovros_rotto") --Rotto Mechanic
	SceneObject(pNpc):setCustomObjectName("Rotto Dimok")
end
