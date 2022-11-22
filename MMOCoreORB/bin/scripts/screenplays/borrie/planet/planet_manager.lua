local Logger = require("utils.logger")

BorPlanetManager = CityScreenPlay:new {

	numberOfActs = 1,

	screenplayName = "BorPlanetManager",
	
	planets = {},
	planets_index = {},
	bases = {},
	landing_points = {},
}

registerScreenPlay("BorPlanetManager",  true)

function BorPlanetManager:start()
	Logger:log("Starting Borrie's Planet Manager", LT_INFO)
	self:initializePlanets()
end

function BorPlanetManager:initializePlanets() 
	Logger:log("Initializing Roleplay Data for " .. #self.planets_index .. " planets.", LT_INFO)
	for i = 1, #self.planets_index, 1 do
		local planet = self.planets[self.planets_index[i][2]]
		if(isZoneEnabled(planet.zone)) then
			Logger:log("Loading Roleplay Planet Data for "..planet.name, LT_INFO)
			--Do special planet stuff
			--Loop through bases
			for j = 1, #planet.bases, 1 do
				local base = self.bases[planet.bases[j]]
				if(base ~= nil) then
					self:spawnBaseContents(planet, base)
				else 
					Logger:log("Tried to load base " .. planet.bases[j] .. " on "..planet.name.." but no base information available.", LT_ERROR)
				end
			end
		else
			Logger:log("Could not load Roleplay Planet Data for \""..planet.name .."\" because zone \""..planet.zone.."\"is not loaded.", LT_INFO)
		end
	end
end

function BorPlanetManager:spawnBaseContents(planet, base)
	local questOwnerVar = "borPlanetManager:" .. planet.zone .. ":base:" .. base.tag .. ":owner"
	--Get base's controlling faction. If it is currently empty, initialize with vanilla.
	local controllingFaction = getQuestStatus(questOwnerVar)
	if(controllingFaction == "" or controllingFaction == nil) then
		setQuestStatus(questOwnerVar, base.defaultOwner)
		controllingFaction = base.defaultOwner
	end
	
	local factionData = BorFactionManager.factions[controllingFaction]
	
	if(factionData ~= nil) then
		--Spawn Flags
		--Spawn Mobs
		local unitGroup = BorFactionManager.unit_groups[factionData.unitGroup].units
		
		if(unitGroup == nil) then
			Logger:log("ERROR: Tried to access Factional Unit Group " .. factionData.unitGroup .. ", but it seemingly doesn't exist.", LT_ERROR)
			return 0
		end
		
		for i = 1, #base.spawns, 1 do
			local mobTemplate = unitGroup[base.spawns[i][1]]
			if(mobTemplate ~= nil and mobTemplate ~= "") then
				if(base.spawns[i][1] == "recruiter") then
					--Spawn NPC that can do conversation
					local pNPC = createTemplatedRoleplayNPC(mobTemplate, base.spawns[i][3], base.spawns[i][4], base.spawns[i][5], base.spawns[i][6], base.spawns[i][7], base.spawns[i][2], "rp_convo_recruiter")
					if(pNPC ~= nil) then
						SceneObject(pNPC):setStoredString("rp_fac_recruiter_theme", factionData.recruiter_theme)
						SceneObject(pNPC):setStoredString("rp_faction", factionData.tag)
					else 
						Logger:log("ERROR: [BorPlanetManager] could not spawn recruiter mob for unknown reason.", LT_ERROR)
					end
				else
					--Spawn normal NPC
					createTemplatedRoleplayNPC(mobTemplate, base.spawns[i][3], base.spawns[i][4], base.spawns[i][5], base.spawns[i][6], base.spawns[i][7], base.spawns[i][2])
				end
			else 
				Logger:log("ERROR: Could not spawn unit from unit group", LT_ERROR)
			end
		end
	else 
		Logger:log("ERROR: Tried to access Faction Data for \"" .. controllingFaction .. "\", but it seemingly doesn't exist.", LT_ERROR)
	end
end

function BorPlanetManager:addPlanet(planet) 
	self.planets[planet.zone] = planet
	table.insert(self.planets_index, {planet.name, planet.zone})
	--Load the landing points for easy reference.
	for i = 1, #planet.landing_points, 1 do
		self.landing_points[planet.landing_points[i][1]] = planet.landing_points[i]
	end
end

function BorPlanetManager:addBase(base)
	self.bases[base.tag] = base
end