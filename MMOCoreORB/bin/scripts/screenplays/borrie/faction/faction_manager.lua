BorFactionManager = {
	factions = {},
	recruiterThemes = {},
	unit_groups = {},
}

function BorFactionManager:getFactionIsEnemy(rootFactionTag, targetFactionTag) 
	local faction = self.factions[rootFactionTag]
	if(faction == nil) then
		return false
	end
	
	for i = 1, #faction.enemies, 1 do
		if(faction.enemies[i] == targetFactionTag) then
			return true
		end
	end
	
	--No matches found, return false. Not an enemy.
	return false
end

function BorFactionManager:getFactionIsAlly(rootFactionTag, targetFactionTag) 
	local faction = self.factions[rootFactionTag]
	if(faction == nil) then
		return false
	end
	
	for i = 1, #faction.allies, 1 do
		if(faction.allies[i] == targetFactionTag) then
			return true
		end
	end
	
	--No matches found, return false. Not an ally.
	return false
end



function BorFactionManager:modifyFactionInfluence(factionTag, mod) 
	--Use QuestData to modify this global aspect
end

function BorFactionManager:modifyFactionPlayerCount(factionTag, mod)
	--Use QuestData to modify this global aspect
	local factionMemberCount = tonumber(getQuestStatus(factionTag .. ":memberCount"))
	if(factionMemberCount == nil) then
		factionMemberCount = 0
	end
	factionMemberCount = factionMemberCount + mod
	setQuestStatus(factionTag .. ":memberCount", factionMemberCount)
	
end

function BorFactionManager:playerPromptJoinFaction(pPlayer, factionTag)
	local faction = self.factions[factionTag]
	local sui = SuiMessageBox.new("BorFactionManager", "promptJoinFactionCallback")
	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())
	sui.setTitle("Join Faction")
	sui.setPrompt("Do you wish to join the " .. faction.name .. "?")
	sui.setOkButtonText("Yes")
	sui.setCancelButtonText("No")
	SceneObject(pPlayer):setStoredString("faction_join_prompt", factionTag)
	local pageId = sui.sendTo(pPlayer)
end

function BorFactionManager:promptJoinFactionCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		SceneObject(pPlayer):deleteStoredString("faction_join_prompt")
		return
	end
	
	
	--If so, then they said yes. Let's join.
	local factionTag = SceneObject(pPlayer):getStoredString("faction_join_prompt")
	self:playerJoinFaction(pPlayer, factionTag)
	SceneObject(pPlayer):deleteStoredString("faction_join_prompt")
end

function BorFactionManager:playerPromptLeaveFaction(pPlayer, factionTag)
	local faction = self.factions[factionTag]
	local sui = SuiMessageBox.new("BorFactionManager", "promptLeaveFactionCallback")
	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())
	sui.setTitle("Leave Faction")
	sui.setPrompt("Do you wish to leave the " .. faction.name .. "? Your rank may not be preserved, and if you join an opposing faction you will be branded a traitor.")
	sui.setOkButtonText("Yes")
	sui.setCancelButtonText("No")
	local pageId = sui.sendTo(pPlayer)
end

function BorFactionManager:promptLeaveFactionCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end
	
	--If so, then they said yes. Let's leave.
	self:playerLeaveFaction(pPlayer)
end

function BorFactionManager:playerJoinFaction(pPlayer, factionTag) 
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return 0
	end
	
	local faction = self.factions[factionTag]
	if(faction == nil) then
		CreatureObject(pPlayer):sendSystemMessage("The faction you're trying to join seemingly doesn't exist.")
		return 0
	end
	
	local startingRank = 1
	local lastRank = SceneObject(pPlayer):getStoredInt("rank_" .. factionTag)
	local lastFaction = SceneObject(pPlayer):getStoredString("lastFaction")
	
	if(lastFaction == factionTag) then
		startingRank = lastRank - 1
		
	elseif(lastRank > 0) then
		if(self:getFactionIsAlly(factionTag, lastFaction)) then
			startingRank = lastRank - 2
		elseif(self:getFactionIsEnemy(factionTag, lastFaction)) then
			startingRank = lastRank / 2
		end
	end
	
	if(startingRank <= 0) then
		startingRank = 1
	end
	
	--Traitor Update
	if(self:getFactionIsEnemy(lastFaction, factionTag)) then
		local otherFaction = self.factions[lastFaction]
		local traitorLevel = SceneObject(pPlayer):getStoredInt("faction_traitor_" .. lastFaction)
		if(traitorLevel < 2) then
			SceneObject(pPlayer):setStoredInt("faction_traitor_" .. lastFaction, traitorLevel + 1)
		end
		
		if(traitorLevel == 0) then
			CreatureObject(pPlayer):sendSystemMessage("By joining their enemy, you are now considered a traitor to " .. otherFaction.name .. ".")
		elseif(traitorLevel == 1) then
			CreatureObject(pPlayer):sendSystemMessage("By once again joining their enemy, you are now considered a heinous traitor to " .. otherFaction.name .. ", and you will never be welcomed back.")
		end
	end
	
	--Set Player's Faction to the faction tag
	SceneObject(pPlayer):setStoredString("lastFaction", factionTag)
	SceneObject(pPlayer):setStoredString("faction_current", factionTag)
	SceneObject(pPlayer):setStoredInt("rank_" .. factionTag, startingRank)
	
	--Reset their loyalty and contribution
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	PlayerObject(pGhost):setFoodFilling(0)
	PlayerObject(pGhost):setDrinkFilling(0)
	
	CreatureObject(pPlayer):sendSystemMessage("You have joined the " .. faction.name .. "! You have been granted the rank of " .. faction.ranks[startingRank] .. " and issued an ID.")
	
	--Generate the ID Badge
	local pBadge = giveItem(pInventory, "object/tangible/borrp/item/id_badge.iff", -1, true)
	if(pBadge ~= nil) then
		SceneObject(pBadge):setStoredString("true_name", CreatureObject(pPlayer):getFirstName())
		SceneObject(pBadge):setStoredString("first_name", CreatureObject(pPlayer):getFirstName())
		SceneObject(pBadge):setStoredString("last_name", CreatureObject(pPlayer):getLastName())
		SceneObject(pBadge):setStoredInt("rank", startingRank)
		SceneObject(pBadge):setStoredString("faction", factionTag)
		SceneObject(pBadge):setCustomObjectName(faction.adjective .. " ID: " .. faction.ranks[startingRank] .. " " .. CreatureObject(pPlayer):getFirstName() .. " " .. CreatureObject(pPlayer):getLastName())
	
		setStoredObject(pPlayer, pBadge, "current_badge")
	else 
		CreatureObject(pPlayer):sendSystemMessage("There was an error in generating your ID Badge. Check in again later to recieve an ID Badge.")
	end
	
	--Add To the Faction Player Count
	self:modifyFactionPlayerCount(factionTag, 1)
end

function BorFactionManager:getTraitorLevel(pPlayer, factionTag) 
	return SceneObject(pPlayer):getStoredInt("faction_traitor_" .. factionTag)
end

function BorFactionManager:playerLeaveFaction(pPlayer)
	--Set Player's Faction to none
	local factionTag = SceneObject(pPlayer):getStoredString("faction_current")
	local faction = self.factions[factionTag]
	
	SceneObject(pPlayer):deleteStoredString("faction_current")
	
	local pBadge = getStoredObject(pPlayer, "current_badge")
	SceneObject(pBadge):setStoredInt("expired", 1)
	
	--Delete the badge if you have it
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return false
	end
	
	local badgeParentID = SceneObject(SceneObject(pBadge):getParent()):getObjectID()
	local inventoryID = SceneObject(pInventory):getObjectID()
	if(badgeParentID == inventoryID) then
		SceneObject(pBadge):destroyObjectFromWorld()
	end
	
	--Inform the player. 
	CreatureObject(pPlayer):sendSystemMessage("You have left the " .. faction.name .. ".")
	
	--Remove from the Faction Player Count
	self:modifyFactionPlayerCount(factionTag, -1)
	
end

function BorFactionManager:addFaction(faction) 
	self.factions[faction.tag] = faction
	--If we don't have existing metadata for this faction's influence, add it's starting value.
	
end

function BorFactionManager:addRecruiterTheme(themeTag, theme) 
	self.recruiterThemes[themeTag] = theme
end

function BorFactionManager:addUnitGroup(group) 
	self.unit_groups[group.tag] = group
end

function BorFactionManager:getRequisitionUniform(pPlayer) 
	local factionTag = SceneObject(pPlayer):getStoredString("faction_current")
	local factionRank = SceneObject(pPlayer):getStoredInt("rank_" .. factionTag)
	
	--DEBUG
	--factionTag = "empire"
	--factionRank = 1
	
	local factionData = self.factions[factionTag]
	
	local uniformType = factionData.uniforms[factionRank][1]
	
	if(uniformType == "") then
		CreatureObject(pPlayer):sendSystemMessage("There are no specified uniforms for you at this rank.")
		return
	end
	
	local pBox = createLootBox(pPlayer, "object/tangible/item/roleplay/loot_box_s01.iff", uniformType, true)
	
	if(pBox == nil) then
		CreatureObject(pPlayer):sendSystemMessage("There was an unknown error trying to get your requisition fulfilled. Please check in with your superior officers.")
		return
	end
	local boxName = factionData.adjective .. " " .. factionData.ranks[factionRank] .. " Uniform Container"
	SceneObject(pBox):setCustomObjectName(boxName)
	CreatureObject(pPlayer):sendSystemMessage("You've recieved \"" .. boxName .. ".\"")
	
end

function BorFactionManager:getRequisitionLoadout(pPlayer) 
	local factionTag = SceneObject(pPlayer):getStoredString("faction_current")
	local factionRank = SceneObject(pPlayer):getStoredInt("rank_" .. factionTag)
	
	--DEBUG
	--factionTag = "empire"
	--factionRank = 1
	
	local factionData = self.factions[factionTag]
	
	local loadoutType = factionData.loadouts[factionRank][1]
	
	if(loadoutType == "") then
		CreatureObject(pPlayer):sendSystemMessage("There are no specified loadouts for you at this rank.")
		return
	end
	
	local pBox = createLootBox(pPlayer, "object/tangible/item/roleplay/loot_box_s01.iff", loadoutType, true)
	
	if(pBox == nil) then
		CreatureObject(pPlayer):sendSystemMessage("There was an unknown error trying to get your requisition fulfilled. Please check in with your superior officers.")
		return
	end
	
	local boxName = factionData.adjective .. " " .. factionData.ranks[factionRank] .. " Loadout Container"
	SceneObject(pBox):setCustomObjectName(boxName)
	CreatureObject(pPlayer):sendSystemMessage("You've recieved \"" .. boxName .. ".\"")
	
end

function BorFactionManager:canReportIn(pPlayer)
	local reportDelay = tonumber(readScreenPlayData(pPlayer, "BorFactionManager", "ReportDelay"))
	
	if (reportDelay == nil or reportDelay == 0) then
		return true
	end

	return os.time() >= reportDelay
end

function BorFactionManager:reportIn(pPlayer)
	local reportDelay = 129600 --24 Hours
	writeScreenPlayData(pPlayer, "BorFactionManager", "ReportDelay", reportDelay + os.time())
	
	local factionTag = SceneObject(pPlayer):getStoredString("faction_current")
	local factionRank = tonumber(SceneObject(pPlayer):getStoredInt("rank_" .. factionTag))
	local factionData = self.factions[factionTag]
	
	local amount = factionData.basePay * factionRank
	
	CreatureObject(pPlayer):addCashCredits(amount, true)
	CreatureObject(pPlayer):sendSystemMessageWithDI("@theme_park/messages:theme_park_credits_pp", amount)
	CreatureObject(pPlayer):sendSystemMessage("You've successfully reported in for today. You can do so again in 24 hours.")
	CreatureObject(pPlayer):awardExperience("rp_general", 250 * factionRank, true)
	
	--Convert Food to Drink
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local dailyFactionContribution = PlayerObject(pGhost):getFoodFilling()
	local maxTotalFaction = PlayerObject(pGhost):getDrinkFillingMax()
	local currentTotalFaction = PlayerObject(pGhost):getDrinkFilling()
	local newTotal = currentTotalFaction + (dailyFactionContribution / 10)
	if(newTotal > maxTotalFaction) then
		newTotal = maxTotalFaction
	end
	PlayerObject(pGhost):setFoodFilling(0)
	PlayerObject(pGhost):setDrinkFilling(newTotal)
end

function BorFactionManager:promptPromotion(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local maxTotalFaction = PlayerObject(pGhost):getDrinkFillingMax()
	local currentTotalFaction = PlayerObject(pGhost):getDrinkFilling()
	
	local factionTag = SceneObject(pPlayer):getStoredString("faction_current")
	local factionRank = tonumber(SceneObject(pPlayer):getStoredInt("rank_" .. factionTag))
	local faction = self.factions[factionTag]
	
	if(#faction.ranks == factionRank) then
		CreatureObject(pPlayer):sendSystemMessage("You are already the highest rank for this faction.")
		return
	end
	
	if(currentTotalFaction == maxTotalFaction) then
		local sui = SuiMessageBox.new("BorFactionManager", "acceptPromotionCallback")
		sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())
		sui.setTitle("Accept Promotion")
		sui.setPrompt("Do you wish to accept the new rank of " .. faction.ranks[factionRank + 1] .. "? This will cost the full amount of your overall faction loyalty to do so.")
		sui.setOkButtonText("Yes")
		sui.setCancelButtonText("No")
	local pageId = sui.sendTo(pPlayer)
	else 
		CreatureObject(pPlayer):sendSystemMessage("You are not yet eligible for promotion.")
	end
end

function BorFactionManager:acceptPromotionCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end
	
	--If so, then they said yes. Let's promote them!.
	local factionTag = SceneObject(pPlayer):getStoredString("faction_current")
	local factionRank = tonumber(SceneObject(pPlayer):getStoredInt("rank_" .. factionTag))
	local faction = self.factions[factionTag]
	
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local maxTotalFaction = PlayerObject(pGhost):getDrinkFillingMax()
	local currentTotalFaction = PlayerObject(pGhost):getDrinkFilling()
	if(currentTotalFaction == maxTotalFaction) then
		PlayerObject(pGhost):setDrinkFilling(0)
		SceneObject(pPlayer):setStoredInt("rank_" .. factionTag, factionRank + 1)
		CreatureObject(pPlayer):sendSystemMessage("You have been promoted to the rank of " .. faction.ranks[factionRank+1] .. "!")
		local pBadge = getStoredObject(pPlayer, "current_badge")
		SceneObject(pBadge):setCustomObjectName(faction.adjective .. " ID: " .. faction.ranks[factionRank+1] .. " " .. CreatureObject(pPlayer):getFirstName() .. " " .. CreatureObject(pPlayer):getLastName())
		SceneObject(pBadge):setLocalInt("rank", factionRank + 1)
	else 
		CreatureObject(pPlayer):sendSystemMessage("You are not yet eligible for promotion anymore.")
	end
end


function BorFactionManager:promptAskOrders(pPlayer)
	local factionTag = SceneObject(pPlayer):getStoredString("faction_current")
	local factionRank = tonumber(SceneObject(pPlayer):getStoredInt("rank_" .. factionTag))
	local faction = self.factions[factionTag]
end

function BorFactionManager:promptAskStatus(pPlayer)
	local factionTag = SceneObject(pPlayer):getStoredString("faction_current")
	local factionRank = tonumber(SceneObject(pPlayer):getStoredInt("rank_" .. factionTag))
	local faction = self.factions[factionTag]
end

function BorFactionManager:getCurrentTrainingLevel(pPlayer, trainingType)
	trainingType = "rp_training_" .. trainingType .. "_"
	
	if(CreatureObject(pPlayer):hasSkill(trainingType.. "master")) then
		return 12
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_10")) then
		return 11
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_09")) then
		return 10
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_08")) then
		return 9
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_07")) then
		return 8
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_06")) then
		return 7
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_05")) then
		return 6
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_04")) then
		return 5
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_03")) then
		return 4
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_02")) then
		return 3
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_01")) then
		return 2
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "novice")) then
		return 1
	else 
		return 0
	end
	
end

function BorFactionManager:getNextTrainingSkillName(trainingType) 
	trainingType = "rp_training_" .. trainingType .. "_"
	
	if(CreatureObject(pPlayer):hasSkill(trainingType.. "master")) then
		return trainingType.. "master"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_10")) then
		return trainingType.. "master"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_09")) then
		return trainingType.. "rank_10"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_08")) then
		return trainingType.. "rank_09"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_07")) then
		return trainingType.. "rank_08"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_06")) then
		return trainingType.. "rank_07"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_05")) then
		return trainingType.. "rank_06"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_04")) then
		return trainingType.. "rank_05"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_03")) then
		return trainingType.. "rank_04"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_02")) then
		return trainingType.. "rank_03"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "rank_01")) then
		return trainingType.. "rank_02"
	elseif(CreatureObject(pPlayer):hasSkill(trainingType .. "novice")) then
		return trainingType.. "rank_01"
	else 
		return trainingType.. "novice"
	end
end

function BorFactionManager:getTrainingBoxForLevel(trainingType, level)
	trainingType = "rp_training_" .. trainingType .. "_"
	if(level == 0) then
		return trainingType .. "novice"
	elseif(level == 1) then
		return trainingType .. "novice"
	elseif(level == 2) then
		return trainingType .. "rank_01"
	elseif(level == 3) then
		return trainingType .. "rank_02"
	elseif(level == 4) then
		return trainingType .. "rank_03"
	elseif(level == 5) then
		return trainingType .. "rank_04"
	elseif(level == 6) then
		return trainingType .. "rank_05"	
	elseif(level == 7) then
		return trainingType .. "rank_06"
	elseif(level == 8) then
		return trainingType .. "rank_07"
	elseif(level == 9) then
		return trainingType .. "rank_08"
	elseif(level == 10) then
		return trainingType .. "rank_09"
	elseif(level == 11) then
		return trainingType .. "rank_10"
	elseif(level == 12) then
		return trainingType .. "master"
	else 
		return trainingType .. "novice"
	end
end

function BorFactionManager:promptGainTraining(pPlayer, trainingID)
	local factionTag = SceneObject(pPlayer):getStoredString("faction_current")
	local faction = self.factions[factionTag]
	
	local trainingType = faction.training[trainingID]
	
	local hasBox = CreatureObject(pPlayer):hasSkill("rp_training_" .. trainingType .. "_novice")
	
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local foodMax = PlayerObject(pGhost):getFoodFillingMax() 
	local currentFood = PlayerObject(pGhost):getFoodFilling() 
	
	if(foodMax > currentFood) then
		CreatureObject(pPlayer):sendSystemMessage("You must be at max overall loyalty to qualify for continued training.")		
		return
	end
	
	if(hasBox) then
		local currentLevel = self:getCurrentTrainingLevel(pPlayer, trainingType)
		local nextBox = self:getTrainingBoxForLevel(pPlayer, trainingType, currentLevel + 1)
		awardSkill(pPlayer, nextBox)
		PlayerObject(pGhost):setFoodFilling(0)
		CreatureObject(pPlayer):sendSystemMessage("Through dedication and loyalty to your faction, you have recieved special training to improve your abilities.")		
	else 
		local trainingCount = CreatureObject(pPlayer):getTrainingSkillCount()
		if(trainingCount < 2) then
			awardSkill(pPlayer, "rp_training_" .. trainingType .. "_novice")
			PlayerObject(pGhost):setFoodFilling(0)
			CreatureObject(pPlayer):sendSystemMessage("You have begun to undertake special training, provided by your faction in exchange for your loyalty. You can only have two special training skills at one time.")		
		else 
			CreatureObject(pPlayer):sendSystemMessage("You may only have two diciplines of training at one time. Please surrender one before trying to take on a new one.")
		end
	end
	
end