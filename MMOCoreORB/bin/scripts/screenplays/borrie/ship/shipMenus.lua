local ObjectManager = require("managers.object.object_manager")

--Exit Terminal
ShipExitMenuComponent = {}

function ShipExitMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(20, 3, "Exit Ship")
end

function ShipExitMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end
	
	if (selectedID == 20) then 
		BorRpShip:exitShip(pPlayer)	
	end
	
	return 0
end

--Navicomputer
ShipNavicomputerMenuComponent = {}

function ShipNavicomputerMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	
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

	local eventID = readData(shipID .. ":landShip:shipStatus")
	if(eventID == 3) then
		menuResponse:addRadialMenuItem(82, 3, "Take Off")
	elseif(eventID == 0) then 
		menuResponse:addRadialMenuItem(80, 3, "Plot a Course")
		menuResponse:addRadialMenuItem(81, 3, "Land the Ship")
	end
	
end

function ShipNavicomputerMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end
	
	if (selectedID == 80) then --Plot a Course
		BorRpShip:promptCourseChangeMenu(pPlayer, pObject)
	elseif(selectedID == 81) then --Land the Ship
		BorRpShip:promptLandShipMenu(pPlayer, pObject)
	elseif(selectedID == 82) then --Take Off
		BorRpShip:takeOffShip(pObject, pPlayer, true)
	end
	
	return 0
end

--ShipControlDevice
RpShipControlDeviceMenuComponent = {}

function RpShipControlDeviceMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	
	local pShip = getShipFromControlDevice(pSceneObject)
	
	if(pShip == nil) then
		pShip = pSceneObject
	end
	
	local shipID = SceneObject(pShip):getObjectID()
	
	local eventID = readData(shipID .. ":landShip:shipStatus")
	
	--menuResponse:addRadialMenuItem(120, 3, "Board Ship")
	if(eventID ~= 2 and eventID ~= 3) then
		menuResponse:addRadialMenuItem(81, 3, "Land Ship")
	elseif(eventID == 3) then
		menuResponse:addRadialMenuItem(82, 3, "Send Ship Away")
	end
	
	if(pShip ~= pSceneObject) then
		menuResponse:addRadialMenuItem(83, 3, "Generate Caller")
	end
	
	menuResponse:addRadialMenuItem(84, 3, "Rename Ship")
end

function RpShipControlDeviceMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (selectedID == 80) then --Board Ship
		
	elseif(selectedID == 81) then --Land Ship
		BorRpShip:landShip(pObject, pPlayer)
	elseif(selectedID == 82) then --Send Ship Away
		BorRpShip:takeOffShip(pObject, pPlayer, false)
	elseif(selectedID == 83) then --Generate Caller
		
	elseif(selectedID == 84) then --Rename Ship
		BorRpShip:renameShip(pObject, pPlayer)
	end
	
	return 0
end