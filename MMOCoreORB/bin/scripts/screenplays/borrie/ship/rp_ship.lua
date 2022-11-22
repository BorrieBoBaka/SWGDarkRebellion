BorRpShip = {}

function BorRpShip:exitShip(pPlayer)
	--Get Ship
	local pCell = SceneObject(pPlayer):getParent()
	
	if(pCell == nil) then
		return 0
	end
	
	local pShip = SceneObject(pCell):getParent()
	
	if(pShip == nil) then
		return 0
	end	
	
	local shipID = SceneObject(pShip):getObjectID()
	local currentLandingSpot = getStoredObject(pShip, "landing_point_object")
	local eventID = readData(shipID .. ":landShip:shipStatus")
	
	if(currentLandingSpot ~= nil and eventID == 3) then
		local lPosX = SceneObject(currentLandingSpot):getWorldPositionX()
		local lPosY = SceneObject(currentLandingSpot):getWorldPositionY()
		local lPosZ = SceneObject(currentLandingSpot):getWorldPositionZ()
		local lCell = SceneObject(currentLandingSpot):getParentID()
		local lZone = SceneObject(currentLandingSpot):getZoneName()
				
		SceneObject(pPlayer):switchZone(lZone, lPosX, lPosZ, lPosY, lCell) 
		return 0
	end	
	
	--Get Ship's last known landing spot
	local shipLandingSpot = SceneObject(pShip):getStoredString("landing_spot")
	if(shipLandingSpot == "") then
		shipLandingSpot = "eisley_spaceport"
	end
	--Teleport them there. 
	local point = BorPlanetManager.landing_points[shipLandingSpot]
	if(point ~= nil) then
		--------------------------------ZONE--------X------Z------Y-------CELL---
		SceneObject(pPlayer):switchZone(point[3], point[4],point[5],point[6], point[8]) 
	else 
		CreatureObject(pPlayer):sendSystemMessage("Something horrible has occured. Could not locate landing point for this ship. Contact administration to get you out.")
	end	
end

function BorRpShip:broadcastToPassengers(pShip, message)
	--If it is not a building ship, no one to alert.
	if(SceneObject(pShip):isBuildingObject() == false) then
		return 0
	end
	
	local totalCells = BuildingObject(pShip):getTotalCellNumber()
	for i = 1, totalCells, 1 do
		local pCell = BuildingObject(pShip):getCell(i)
		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if SceneObject(pObject):isPlayerCreature() then
					CreatureObject(pObject):sendSystemMessage(message)
				end
			end
		end
	end
end

function BorRpShip:promptCourseChangeMenu(pPlayer, pObject)
	--Get Ship
	local pCell = SceneObject(pPlayer):getParent()
	
	if(pCell == nil) then
		return 0
	end
	
	local pShip = SceneObject(pCell):getParent()
	
	if(pShip == nil) then
		return 0
	end	
	
	local currentPlanetTag = SceneObject(pShip):getStoredString("current_planet")
	local currentPlanet = BorPlanetManager.planets[currentPlanetTag]
	
	if(currentPlanet == nil) then
		currentPlanet = BorPlanetManager.planets["rp_tatooine"]
	end
	
	local options = {}
	for i = 1, #BorPlanetManager.planets_index, 1 do
		local planetData = {BorPlanetManager.planets_index[i][1], BorPlanetManager.planets_index[i][2]}
		table.insert(options, planetData)
	end
	
	local suiManager = LuaSuiManager()
	suiManager:sendListBox(pObject, pPlayer, "Navicomputer", "Select a destination to make the jump to lightspeed.\n\nCurrent Planet: " .. currentPlanet.name, 1, "@cancel", "", "", "BorRpShip", "plotCourseCallback", 10, options)
end

function BorRpShip:plotCourseCallback(pPlayer, pSui, eventIndex, rowIndex) 
	--Get Ship
	local pCell = SceneObject(pPlayer):getParent()
	
	if(pCell == nil) then
		return 0
	end
	
	local pShip = SceneObject(pCell):getParent()
	
	if(pShip == nil) then
		return 0
	end	
	
	rowIndex = tonumber(rowIndex)
	local newPlanet = BorPlanetManager.planets_index[rowIndex + 1]
	
	SceneObject(pShip):setStoredString("current_planet", newPlanet[2])
	
	local shipName = SceneObject(pShip):getCustomObjectName()
	if(shipName == "") then
		shipName = "The Ship"
	end
	
	local message = shipName .. " jumps to lightspeed, arriving shortly in orbit above " .. newPlanet[1] .. "."
	
	self:broadcastToPassengers(pShip, message)
end

function BorRpShip:promptLandShipMenu(pPlayer, pObject)
	local pCell = SceneObject(pPlayer):getParent()
	
	if(pCell == nil) then
		return 0
	end
	
	local pShip = SceneObject(pCell):getParent()
	
	if(pShip == nil) then
		return 0
	end	
	
	local currentPlanet = SceneObject(pShip):getStoredString("current_planet")
	local currentLanding = SceneObject(pShip):getStoredString("landing_spot")
	local onSpotLandPoint
	
	local options = {}
	local planetObject = BorPlanetManager.planets[currentPlanet]
	
	if(planetObject == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error occured. Could not find planet.")
		return 0
	end
	
	for i = 1, #planetObject.landing_points, 1 do
		local landingPoint = {planetObject.landing_points[i][2], 0}
		table.insert(options, landingPoint)
	end
	
	local suiManager = LuaSuiManager()
	suiManager:sendListBox(pObject, pPlayer, "Navicomputer", "Select a landing point.\n\nCurrent Location: " .. currentLanding, 1, "@cancel", "", "", "BorRpShip", "landShipCallback", 10, options)
end

function BorRpShip:landShipCallback(pPlayer, pSui, eventIndex, rowIndex) 
	local pCell = SceneObject(pPlayer):getParent()
	
	if(pCell == nil) then
		return 0
	end
	
	local pShip = SceneObject(pCell):getParent()
	
	if(pShip == nil) then
		return 0
	end	
	
	local currentPlanet = SceneObject(pShip):getStoredString("current_planet")
	
	local planetObject = BorPlanetManager.planets[currentPlanet]
	local selectedLandingSpot = planetObject.landing_points[rowIndex + 1]
	
	SceneObject(pShip):setStoredString("landing_spot", selectedLandingSpot[1])
	
	local shipName = SceneObject(pShip):getCustomObjectName()
	if(shipName == "") then
		shipName = "The Ship"
	end
	
	local message = shipName .. " has now landed at " .. selectedLandingSpot[2] .. "."
	
	self:broadcastToPassengers(pShip, message)	
	
	--Try to land the ship at that location if possible.
	if(selectedLandingSpot[9] == true) then
		CreatureObject(pPlayer):sendSystemMessage("Debug: Point allows landing.")
	end
	
end

function BorRpShip:renameShip(pObject, pPlayer)
	if(pObject == nil) then
		return 0
	end
	
	if(pPlayer == nil) then
		return 0
	end
	
	local suiManager = LuaSuiManager()
	suiManager:sendInputBox(pObject, pPlayer, "BorRpShip", "renameShipCallback", "Enter a new name for your ship:", "@ok")
end

function BorRpShip:renameShipCallback(pPlayer, pSui, eventIndex, newName)
	if(eventIndex == 1) then
		return 0
	end
	
	if(message == "") then
		CreatureObject(pPlayer):sendSystemMessage("You need to enter a new name.")
		return 0
	end
	
	local inputBox = LuaSuiBox(pSui)
	local pObject = inputBox:getUsingObject()
	
	if(pObject == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error finding ship control device.")
		return 0
	end
	
	--local shipObjID = SceneObject(pObject):getStoredLong("structure")
	--local rawShip = getSceneObject(shipObjID)
	local rawShip = getShipFromControlDevice(pObject)
	
	--We only need to name the object building of a ship if there is a building object for this ship.
	if(rawShip ~= nil) then
		SceneObject(rawShip):setCustomObjectName(newName)
	end
	
	SceneObject(pObject):setCustomObjectName(newName)
	CreatureObject(pPlayer):sendSystemMessage("You ship is now called \"" .. newName .. ".\"")
end

function BorRpShip:landShip(pObject, pPlayer)
	if(SceneObject(pPlayer):getParent() ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("You cannot do this inside a structure.")
		return 0
	end
	
	local pShip = getShipFromControlDevice(pObject)
	
	if(pShip == nil) then
		--CreatureObject(pPlayer):sendSystemMessage("Could not find the ship! Aborting landing sequence...")
		--return 0
		pShip = pObject
	end
	
	local shipID = SceneObject(pShip):getObjectID()
	local currentLandingSpot = getStoredObject(pShip, "landing_point_object")
	
	local eventID = readData(shipID .. ":landShip:shipStatus")
	
	if(eventID ~= 0) then
		CreatureObject(pPlayer):sendSystemMessage("This ship is currently landed elsewhere. Take off to land somewhere else.")
		return 0
	end
	
	--TODO: Make this template dynamic based on ship template
	local flatTemplate = SceneObject(pObject):getStoredString("flatteningTemplate")
	local shipNpcTemplate = SceneObject(pObject):getStoredString("appearanceMobile")
	
	local posX = SceneObject(pPlayer):getWorldPositionX()
	local posY = SceneObject(pPlayer):getWorldPositionY()
	local posZ = SceneObject(pPlayer):getWorldPositionZ()
	local angle = SceneObject(pPlayer):getDirectionAngle()
	local zoneName = SceneObject(pPlayer):getZoneName()
	
	local pPoint = spawnBuilding(pPlayer, flatTemplate, posX, posY, 0)
	
	if(pPoint == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Could not find the landing point object. Aborting landing sequence...")
		return 0
	end
	
	setStoredObject(pShip, pPoint, "landing_point_object")
	
	--Spawn Ship
	local pNpc = spawnRoleplayMobile(zoneName, "rp_base_npc", 1, posX, posZ, posY, angle, 0, shipNpcTemplate, "default", "default", "default")
	
	if(pNpc == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Could not find the ship object for landing animation. Aborting landing sequence...")
		SceneObject(pPoint):destroyObjectFromWorld()
		SceneObject(pPoint):destroyObjectFromDatabase()
		return 0
	end
	
	setStoredObject(pPoint, pNpc, "appearance")
	setStoredObject(pPoint, pShip, "connected_ship")
	
	local shipName = SceneObject(pShip):getCustomObjectName()
	
	if(shipName == "" or shipName == nil) then
		shipName = "ship"
	end
	
	SceneObject(pNpc):setCustomObjectName(shipName)
	CreatureObject(pNpc):setPosture(PRONE)
	createEvent(2 * 1000, "BorRpShip", "startLandAnimation", pNpc, "")
	writeData(shipID .. ":landShip:shipStatus", 2) -- Landing
	CreatureObject(pPlayer):sendSystemMessage("The " .. shipName .. " is now landing...")
	createEvent(29 * 1000, "BorRpShip", "notifyShipLanded", pShip, "") --Time it takes for the player transport to land.
	createEvent(29 * 1000, "BorRpShip", "notifyPointLanded", pPoint, "")
	createEvent(29 * 1000, "BorRpShip", "shipLandedEmote", pNpc, "")
end

function BorRpShip:startLandAnimation(pShip)
	CreatureObject(pShip):setPosture(UPRIGHT)
end

function BorRpShip:shipLandedEmote(pShip)
	if(SceneObject(pShip):isBuildingObject() == false) then
		spatialMoodChat(pShip, "completes its landing sequence.", 0, 38)
	else
		spatialMoodChat(pShip, "completes its landing sequence, and drops down its boarding ramp.", 0, 38)
	end
end

function BorRpShip:notifyShipLanded(pShip)
	local shipID = SceneObject(pShip):getObjectID()
	writeData(shipID .. ":landShip:shipStatus", 3) -- Landed	
	--Alert the Crew
	local shipName = SceneObject(pShip):getCustomObjectName()
	
	if(shipName == "" or shipName == nil) then
		shipName = "ship"
	end
	
	local pPoint = getStoredObject(pShip, "landing_point_object")
	local posX = SceneObject(pPoint):getWorldPositionX()
	local posY = SceneObject(pPoint):getWorldPositionY()
	local zoneName = SceneObject(pPoint):getZoneName()
	local planetName = BorPlanetManager.planets[zoneName].name
	self:broadcastToPassengers(pShip, "The " .. shipName .. " has landed at " .. posX .. ", " .. posY .. ", " .. planetName .. ".")	
end

function BorRpShip:notifyPointLanded(pPoint)
	SceneObject(pPoint):setStoredInt("acceptingPassengers", 1)
end

function BorRpShip:takeOffShip(pObject, pPlayer, isFromShip)
	local pShip
	
	if(isFromShip == true) then
		local pCell = SceneObject(pObject):getParent()
	
		if(pCell == nil) then
			CreatureObject(pPlayer):sendSystemMessage("This Navicomputer is not currently installed on a ship.")
			return 0
		end
	
		pShip = SceneObject(pCell):getParent()
	else
		pShip = getShipFromControlDevice(pObject)
	end
	
	if(pShip == nil) then
		--CreatureObject(pPlayer):sendSystemMessage("Could not find the ship! Aborting launch sequence...")
		--return 0
		pShip = pObject		
	end
	
	local shipID = SceneObject(pShip):getObjectID()
	local currentLandingSpot = getStoredObject(pShip, "landing_point_object")
	
	local eventID = readData(shipID .. ":landShip:shipStatus")
	
	if(currentLandingSpot == nil or eventID == 0) then
		CreatureObject(pPlayer):sendSystemMessage("Your ship is not currently landed anywhere.")
		deleteData(shipID .. ":landShip:shipStatus")
		return 0
	end
	
	
	
	if(eventID ~= 3 and eventID ~= 0) then
		CreatureObject(pPlayer):sendSystemMessage("Your ship is too busy to accept a command right now.")
		return 0
	end
	
	local pNpc = getStoredObject(currentLandingSpot, "appearance")
	if(pNpc ~= nil) then
		CreatureObject(pNpc):setPosture(PRONE)
		createEvent(29 * 1000, "BorRpShip", "clearAppearance", pNpc, "")
	end
	
	writeData(shipID .. ":landShip:shipStatus", 2) -- Landing
	SceneObject(currentLandingSpot):setStoredInt("acceptingPassengers", 0)
	createEvent(29 * 1000, "BorRpShip", "clearLandingPoint", currentLandingSpot, "")
	createEvent(29 * 1000, "BorRpShip", "clearShipData", pShip, "")
	
	local shipName = SceneObject(pShip):getCustomObjectName()
	
	if(shipName == "" or shipName == nil) then
		shipName = "ship"
	end
	
	self:broadcastToPassengers(pShip, "The " .. shipName .. " is taking off!")	
	CreatureObject(pPlayer):sendSystemMessage("The " .. shipName .. " is departing...")
	return 1
end

function BorRpShip:clearAppearance(pNpc)
	SceneObject(pNpc):destroyObjectFromWorld()
	SceneObject(pNpc):destroyObjectFromDatabase()
end

function BorRpShip:clearLandingPoint(pPoint)
	SceneObject(pPoint):destroyObjectFromWorld()
	SceneObject(pPoint):destroyObjectFromDatabase()
end

function BorRpShip:clearShipData(pShip)
	local shipID = SceneObject(pShip):getObjectID()
	deleteData(shipID .. ":landShip:shipStatus")
end

function BorRpShip:testFunction(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("Hello there!")
end

function BorRpShip:promptInstantTravelMenu(pPlayer)
	local suiManager = LuaSuiManager()
	local options = { }
	
	for i = 1, #travel_destinations, 1 do
		if(isZoneEnabled(travel_destinations[i].zone)) then
			table.insert(options, {travel_destinations[i].name, 0})
		end
	end
	
	
	
	if(#options > 0) then
		suiManager:sendListBox(pPlayer, pPlayer, "Personal Ship Travel", "Select a planet you'd like to go to.", 2, "@cancel", "", "@ok", "BorRpShip", "handleInstantTravelSelectPlanet", 32, options)
	else
		CreatureObject(pPlayer):sendSystemMessage("There are no planets currently available to travel to.")
	end
end

function BorRpShip:handleInstantTravelSelectPlanet(pPlayer, pSui, eventIndex, arg0)
	local cancelPressed = (eventIndex == 1)

	if (pPlayer == nil) then
		return
	end

	if (cancelPressed) then
		return
	end
	
	local planet = arg0 + 1
	
	SceneObject(pPlayer):setStoredInt("travel_planet", planet)
	
	local suiManager = LuaSuiManager()
	
	if(planet == nil) then
		return
	end
	
	local options = {}
	local planetObject = BorPlanetManager.planets[BorPlanetManager.planets_index[planet][2]]
	
	if(planetObject == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error occured. Could not find planet: " .. planet)
		return 0
	end
	
	for i = 1, #planetObject.landing_points, 1 do
		local landingPoint = {planetObject.landing_points[i][2], 0}
		table.insert(options, landingPoint)
	end
	
	local suiManager = LuaSuiManager()
	suiManager:sendListBox(pPlayer, pPlayer, "Navicomputer", "Select a landing point.", 1, "@cancel", "", "", "BorRpShip", "personalShipTravel", 10, options)
end

function BorRpShip:personalShipTravel(pPlayer, pSui, eventIndex, arg0) 
	local planet = SceneObject(pPlayer):getStoredInt("travel_planet")
	local planetObject = BorPlanetManager.planets[BorPlanetManager.planets_index[planet][2]]
	
	local dest = planetObject.landing_points[arg0 + 1]
	if(dest == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error finding destination:  " .. (arg0 + 1))
		return
	end
	
	--------------------------------ZONE--------X------Z------Y-------CELL---
	SceneObject(pPlayer):switchZone(dest[3], dest[4],dest[5],dest[6], dest[8]) 
	
	--WIP: Make Ship Take Off
end