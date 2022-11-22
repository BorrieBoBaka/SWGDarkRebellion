CivillianGenerator = ScreenPlay:new{
	screenplayName = "CivillianGenerator",
}

registerScreenPlay("CivillianGenerator", true)

function CivillianGenerator:spawnCivillians(screenplayName, zoneName, waypointList, walkpointList, spawnGroupTag, outfitGroupTag) 
	local spawnGroup = CivSpawnGroups:getCivSpawnGroup(spawnGroupTag)
	for i = 1, #waypointList, 1 do
	
		local template
		local ignoreOutfit = false
		if(waypointList[i][7] ~= "" and waypointList[i][7] ~= nil) then --Check for mob template override
			template = waypointList[i][7]
			ignoreOutfit = true
		else
			template = self:getRandomTemplate(spawnGroup.organic)
		end
			
		local x = waypointList[i][1]
		local z = waypointList[i][2]
		local y = waypointList[i][3]
		local angle = waypointList[i][4]
		local parent = waypointList[i][5]
		local tags = waypointList[i][6]
		local isFemale = string.find(template, "_female")
		
		local outfit 
		
		if(ignoreOutfit) then
			outfit = "default"
		else 
			outfit = self:getRandomOutfit(outfitGroupTag, isFemale)
		end
		
		local pNpc = spawnRoleplayMobile(zoneName, "rp_base_npc", 1, x, z, y, angle, parent, template, outfit, "default", "random")
		
		local nameType = civNameTypeList[template]
		if(nameType ~= nil) then
			setRandomCreatureName(pNpc, nameType)
		end
		
		--Parse Tags
		for j = 1, #tags, 1 do
			if(tags[j] == "sit") then
				self:setMoodString(pNpc, "npc_sitting_ground")
			elseif(tags[j] == "sitchair") then
				self:setMoodString(pNpc, "npc_sitting_chair")
			elseif(tags[j] == "sittable") then
				local sitRoll = getRandomNumber(0, 4)
				if(sitRoll == 0) then
					self:setMoodString(pNpc, "npc_sitting_table")
				elseif(sitRoll == 1) then
					self:setMoodString(pNpc, "npc_sitting_table_eating")
				else 
					self:setMoodString(pNpc, "npc_sitting_chair")
				end		
			elseif(tags[j] == "drinker") then
				--npc_standing_drinking
				if(getRandomNumber(0,5) > 1) then
					self:setMoodString(pNpc, "npc_standing_drinking")
				end
			elseif(tags[j] == "social") then
				self:setupSocialCiv(pNpc)
			elseif(tags[j] == "tech") then
				self:setMoodString(pNpc, "npc_use_terminal_high")
			elseif(string.find(tags[j], "walker")) then 
				--Check to see if we're a walker.
				local walkpointTag = string.sub(tags[j], 8, string.len(tags[j]))
				--printf("WalkPoint: " .. walkpointTag .. "\n")
				self:setupWalkerCiv(pNpc, screenplayName, walkpointTag)
			end
		end		
	end
end

function CivillianGenerator:setupSocialCiv(pNpc)
	local socialMoods = {
		"sad", 
		"calm", 
		"worried", 
		"bored", 
		"angry",
		"conversation",
		"npc_accusing",
		"happy",
		"scared",
		"npc_consoling",
		"conversation",
		"conversation",
		"conversation",
		"conversation",		
	}
	
	local roll = getRandomNumber(1,#socialMoods)
	self:setMoodString(pNpc, socialMoods[roll])	
end

function CivillianGenerator:setMoodString(pNpc, mood) 
	CreatureObject(pNpc):setMoodString(mood)
end

function CivillianGenerator:getRandomTemplate(subSpawnGroup) 
	local templateRandomMax = 0
	for i = 1, #subSpawnGroup, 1 do 
		templateRandomMax = templateRandomMax + subSpawnGroup[i][2]
	end
	
	local roll = getRandomNumber(0, templateRandomMax)
	
	local lastCheck = 0
	for j = 1, #subSpawnGroup, 1 do 
		lastCheck = lastCheck + subSpawnGroup[j][2]
		if(roll <= lastCheck) then
			return subSpawnGroup[j][1]
		end
	end
	
	--If we didn't find anything, we just return the first entry.
	return subSpawnGroup[1][1]
	
end

function CivillianGenerator:getRandomOutfit(outfitGroupTag, isFemale) 
	local spawnGroup = CivOutfitGroups:getCivOutfitGroup(outfitGroupTag)
	
	local unisexRoll = getRandomNumber(1, 6)
	
	local genderGroup = spawnGroup.unisex
	
	--If greater than 1, don't use unisex. If there are no unisex outfits, do this anyway
	if(unisexRoll > 1 or #spawnGroup.unisex == 0) then
		if(isFemale) then
			genderGroup = spawnGroup.female
		else 
			genderGroup = spawnGroup.male
		end		
	end
	
	if(spawnGroup == nil) then
		return ""
	end
	
	if(genderGroup == nil or #genderGroup == 0) then
		return ""
	end
	
	local randomTemplate = getRandomNumber(1, #genderGroup)
	
	return genderGroup[randomTemplate]
end

function CivillianGenerator:getRandomName(template) 


end


--WALKING FUNCTIONS--

function CivillianGenerator:setupWalkerCiv(pNpc, targetScreenplayName, walkpointTag)
	if (pNpc == nil) then
		return
	end
	
	local pOid = SceneObject(pNpc):getObjectID()
	
	--printf("Walkpoint Count: " .. #walkpoints)
	
	createEvent(3000, "CivillianGenerator", "setupMobilePatrol", pNpc, "")
	writeStringData(pOid .. ":patrolPoints", walkpointTag)
	writeStringData(pOid .. ":patrolPointsScreenplay", targetScreenplayName)
	writeData(pOid .. ":currentLoc", 1)	
end

function CivillianGenerator:setupMobilePatrol(pMobile)
	if (pMobile == nil) then
		return
	end
	
	AiAgent(pMobile):setAiTemplate("citypatrol")
	createObserver(CREATUREDESPAWNED, "CivillianGenerator", "onDespawnPatrol", pMobile)
	CreatureObject(pMobile):setPvpStatusBitmask(0)
	CreatureObject(pMobile):setOptionsBitmask(0)
	
	AiAgent(pMobile):setFollowState(4)
	createEvent(getRandomNumber(20, 40) * 1000, "CivillianGenerator", "mobilePatrol", pMobile, '')
	createObserver(DESTINATIONREACHED, "CivillianGenerator", "mobileDestinationReached", pMobile)
end

function CivillianGenerator:onDespawnPatrol(pMobile)
	if pMobile == nil or not SceneObject(pMobile):isAiAgent() then
		printf("Civilian Patrol pMobile is nil or not an AiAgent" .. "\n")
		return
	end

	local pOid = SceneObject(pMobile):getObjectID()

	dropObserver(DESTINATIONREACHED, "CivillianGenerator", "mobileDestinationReached", pMobile)
	deleteData(pOid .. ":patrolNumber")
	deleteData(pOid .. ":currentLoc")
	deleteStringData(pOid .. ":patrolPoints")
	deleteStringData(pOid .. ":patrolPointsScreenplay")

	return 1
end

function CivillianGenerator:mobileDestinationReached(pMobile)
	if (pMobile == nil) then
		return 0
	end
	
	local pOid = SceneObject(pMobile):getObjectID()
	local currentLoc = readData(pOid .. ":currentLoc")
	local screenplayTag = readStringData(pOid .. ":patrolPointsScreenplay")
	local walkpointTag = readStringData(pOid .. ":patrolPoints")
	
	local cityScreenplay = _G[screenplayTag]
	
	local walkpoints = cityScreenplay.walkpointList
	
	local pointSets = walkpoints[walkpointTag]
	
	local patrolPointCount = #pointSets
	
	local currentSet
	
	if (currentLoc >= patrolPointCount) then
		writeData(pOid .. ":currentLoc", 1)
		currentSet = pointSets[1]
	else
		writeData(pOid .. ":currentLoc", currentLoc + 1)
		currentSet = pointSets[currentLoc + 1]
	end
	
	--local currentSet = pointSets[currentLoc]
	local delay = currentSet[6]
	
	--printf("DELAY?: " .. delay .. "\n")
	
	if (delay) then
		local delayTime = getRandomNumber(30, 60)
		
		--TODO: Animate based on animation table.
		
		--Set Facing

		createEvent(delayTime * 1000, "CivillianGenerator", "mobilePatrol", pMobile, "")
		AiAgent(pMobile):setWait(delayTime)
	else
		createEvent(100, "CivillianGenerator", "mobilePatrol", pMobile, "")
	end

	return 0
end

function CivillianGenerator:mobilePatrol(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end
	
	--TODO: Add interrupt if I want to take over the NPC as a DM.
	local pOid = SceneObject(pMobile):getObjectID()

	if (AiAgent(pMobile):isInCombat()) then
		createEvent(25 * 1000, "CivillianGenerator", "mobilePatrol", pMobile, "")
	end
	
	local currentLoc = readData(pOid .. ":currentLoc")
	
	local screenplayTag = readStringData(pOid .. ":patrolPointsScreenplay")
	local walkpointTag = readStringData(pOid .. ":patrolPoints")
	
	local cityScreenplay = _G[screenplayTag]
	
	local walkpoints = cityScreenplay.walkpointList
	
	local pointSet = walkpoints[walkpointTag]
	
	local patrolPointCount = #pointSet
	local nextPoint
	
	--printf("[CIV GEN DEBUG] Walkpoint Count: " .. #pointSet .. "Current Loc: " .. currentLoc .. "\n")
	
	if (currentLoc >= patrolPointCount) then
		nextPoint = pointSet[1]
	else
		nextPoint = pointSet[currentLoc + 1]
	end
	
	--printf("[CIV GEN DEBUG] Current Loc: " .. currentLoc .. ", Next X: " .. nextPoint[1] .. "Y: " .. nextPoint[3] .. "Anim Tag: " .. nextPoint[7] .. "\n")
	
	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):setNextPosition(nextPoint[1], nextPoint[2], nextPoint[3], nextPoint[5])
	AiAgent(pMobile):executeBehavior()

end

return CivillianGenerator