BorLootBoxObjectMenuComponent = {}

--Menu Component Things

function BorLootBoxObjectMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(20, 3, "Unpack")
end

function BorLootBoxObjectMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end
	
	if (selectedID == 20) then --Unpack Lootbox
		self:unpackBox(pPlayer, pObject)		
	end
	
	return 0
end

function BorLootBoxObjectMenuComponent:unpackBox(pPlayer, pObject)

	--Get every item in the lootbox
	local contentCount = SceneObject(pObject):getStoredInt("content_count")
	
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	
	if (pInventory == nil) then
		return 0
	end
	
	if(contentCount == 0) then
		CreatureObject(pPlayer):sendSystemMessage("This box appears to be empty.")
		return
	end
	
	for i = 1,contentCount, 1 do
		local objectTemplate = SceneObject(pObject):getStoredString("content" .. i)
		objectTemplate = string.gsub(objectTemplate, "shared_", "")
		if(objectTemplate ~= "" and objectTemplate ~= nil) then
			local customVar1 = SceneObject(pObject):getStoredString("content_customVar1_" .. i) 
			local customVar2 = SceneObject(pObject):getStoredString("content_customVar2_" .. i) 
			local customVar3 = SceneObject(pObject):getStoredString("content_customVar3_" .. i) 
			local customVar1Value = SceneObject(pObject):getStoredInt("content_customVar1Value_" .. i) 
			local customVar2Value = SceneObject(pObject):getStoredInt("content_customVar2Value_" .. i) 
			local customVar3Value = SceneObject(pObject):getStoredInt("content_customVar3Value_" .. i) 
			
			local objectNoSellVar = SceneObject(pObject):getStoredInt("content_nosell_" .. i) 
			
			local pItem = giveItem(pInventory, objectTemplate, -1, true)
			
			if(pItem ~= nil) then
				if(objectNoSellVar > 0) then
					SceneObject(pItem):setStoredInt("nosell", 1)
				end
				
				--Setup Customization
				if(customVar1 ~= "" or customVar1 ~= nil) then
					TangibleObject(pItem):setCustomizationVariable(customVar1, customVar1Value)
				end
				
				if(customVar2 ~= "" or customVar2 ~= nil) then
					TangibleObject(pItem):setCustomizationVariable(customVar2, customVar2Value)
				end
				
				if(customVar3 ~= "" or customVar3 ~= nil) then
					TangibleObject(pItem):setCustomizationVariable(customVar3, customVar3Value)
				end
				
			else 
				CreatureObject(pPlayer):sendSystemMessage("Error: Could not spawn object " .. objectTemplate)
			end
		else 
			CreatureObject(pPlayer):sendSystemMessage("Error: Could not find an object template for object " .. i .. "/" .. contentCount)
		end
		
		
	end
	
	if (pObject ~= nil) then
		SceneObject(pObject):destroyObjectFromWorld()
		SceneObject(pObject):destroyObjectFromDatabase()
	end
	
	CreatureObject(pPlayer):sendSystemMessage("You open the box to find " .. contentCount .. "items. The box is destroyed in the process.")

end