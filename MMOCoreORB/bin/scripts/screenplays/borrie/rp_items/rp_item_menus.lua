--ID Card
BorRpItemIDCardMenuComponent = {}

function BorRpItemIDCardMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(20, 3, "Show")
end

function BorRpItemIDCardMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end
	
	if (selectedID == 20) then 
		local isReal = tonumber(SceneObject(pObject):getStoredInt("badge_cloned"))
		if(isReal == 0 or isReal == -1 or isReal == nil) then
			local trueName = SceneObject(pObject):getStoredString("true_name")
			local firstName = SceneObject(pObject):getStoredString("first_name")
			local lastName = SceneObject(pObject):getStoredString("last_name")
			local rank = tonumber(SceneObject(pObject):getStoredInt("rank"))
			local factionTag = SceneObject(pObject):getStoredString("faction")		
			local faction = BorFactionManager.factions[factionTag]
			
			local message = faction.ranks[rank] .. " " .. CreatureObject(pPlayer):getFirstName() .. " " .. CreatureObject(pPlayer):getLastName() .. " shows their ID Badge. They are part of the " .. faction.name .. "."
			message = message .. " This ID Card looks genuine to you."
			
			broadcastMessageToArea(pPlayer, message)
			
		else 
			--TODO: Dice rolls and such fun when a badge is cloned and trying to be bluffed.
			CreatureObject(pPlayer):sendSystemMessage("This card is not valid to show off. Yet.")
		end
	end
	
	return 0
end