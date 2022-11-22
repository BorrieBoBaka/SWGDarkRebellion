local ObjectManager = require("managers.object.object_manager")

TeleporterMenuComponent = { }

function TeleporterMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(20, 3, "Enter Area")
end

function TeleporterMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	if (selectedID ~= 20) then
		return 0
	end

	local x = SceneObject(pObject):getStoredFloat("teleporter_x")
	local y = SceneObject(pObject):getStoredFloat("teleporter_y")
	local z = SceneObject(pObject):getStoredFloat("teleporter_z")
	local zone = SceneObject(pObject):getStoredString("teleporter_zone")
	local cell = SceneObject(pObject):getStoredLong("teleporter_cell")
	
	if (not isZoneEnabled(zone)) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:unable_to_find_dungeon") -- That area is currently unavailable. Please try again later.
		return false
	end

	-- Close open Newsnet SUIs and send the player a new one.
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	SceneObject(pPlayer):switchZone(zone, x,z,y, cell) 

	return 0
end

