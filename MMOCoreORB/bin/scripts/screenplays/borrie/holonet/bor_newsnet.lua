local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

BorNewsnetMenuComponent = {

}


BorNewsnetEvent = {
	realDate = "Febuary 19th, 2022",
	title = "Untitled Event",
	faction = "None",
	description = "Lorem Ipsum Dolar Set",
}

BorNewsnet = {
	headlines = {},
	localHeadlines = {},
	events = {},
}

function BorNewsnet:displayHolonetOptions(pPlayer, pObject) 
	local newsOptions = {{"Galaxy-wide News", 0}, {"Local News", 0}}
	local suiManager = LuaSuiManager()
	
	if(pObject == nil or pPlayer == nil or suiManager == nil) then
		Logger:log("Newsnet Critical Failure while loading sui display options.", LT_ERROR)
		return 0
	end
	
	suiManager:sendListBox(pObject, pPlayer, "HoloNet Terminal", "Connected to the HoloNet. What would you like to do?", 1, "@cancel", "", "", "BorNewsnet", "displayHeadlinesCallback", 10, newsOptions)
	deleteStringData(SceneObject(pPlayer):getObjectID() .. ":newsnetStoryRange")
end

function BorNewsnet:displayHeadlinesCallback(pPlayer, pSui, eventIndex, rowIndex) 
	
	if(eventIndex == 1) then
		return
	end

	rowIndex = tonumber(rowIndex)
	
	local listBox = LuaSuiListBox(pSui)
	local pObject = listBox:getUsingObject()
	
	if(rowIndex == 0) then --Show Galactic News
		self:showNewsStories(pPlayer, pObject, false)
	elseif(rowIndex == 1) then -- Show Local News
		self:showNewsStories(pPlayer, pObject, true)
	end
end

function BorNewsnet:showNewsStories(pPlayer, pObject, isLocal) 
	local newsStories = {}
	local planet = SceneObject(pPlayer):getZoneName()
	
	local currentheadlines 
	if(isLocal) then
		currentheadlines = self.localHeadlines[planet]
	else 
		currentheadlines = self.headlines
		planet = ""
	end
	
	if(currentheadlines == nil or #currentheadlines == 0) then
		CreatureObject(pPlayer):sendSystemMessage("There is no news stories available for this location.")
		self:displayHolonetOptions(pPlayer, pObject)
		return
	end
	
	for i = 1, #currentheadlines, 1 do
		local storyData = {currentheadlines[i].title, 0}
		table.insert(newsStories, storyData)
	end	
	
	writeStringData(SceneObject(pPlayer):getObjectID() .. ":newsnetStoryRange", planet)
	local suiManager = LuaSuiManager()
	suiManager:sendListBox(pObject, pPlayer, "HoloNet Terminal", "Please select a news story to read further.", 1, "@cancel", "", "", "BorNewsnet", "readStoryCallback", 10, newsStories)
	
end

function BorNewsnet:readStoryCallback(pPlayer, pSui, eventIndex, rowIndex) 
	local planet = readStringData(SceneObject(pPlayer):getObjectID() .. ":newsnetStoryRange")
		
	if(eventIndex == 1) then
		return
	end
	
	rowIndex = tonumber(rowIndex)
	
	local story
	if(planet == "" or planet == nil) then
		story = self.headlines[rowIndex + 1]
	else 
		story = self.localHeadlines[planet][rowIndex + 1]
	end
	
	if(story == nil) then
		Logger:log("Attempted to get a story from the newsnet, but failed.", LT_ERROR)
	end
	
	local message = story.title .. "\n"
	message = message .. story.galaxyDate .. "\n\n"
	message = message .. story.content
	
	local listBox = LuaSuiListBox(pSui)
	local pObject = listBox:getUsingObject()
	
	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pObject, pPlayer, "HoloNet News", message, "@ok", "BorNewsnet", "onStoryReadCallback", NEWSNET_INFO)
end

function BorNewsnet:onStoryReadCallback(pPlayer, pSui, eventIndex, rowIndex) 
	local listBox = LuaSuiListBox(pSui)
	local pObject = listBox:getUsingObject()
	local planet = readStringData(SceneObject(pPlayer):getObjectID() .. ":newsnetStoryRange")
	self:showNewsStories(pPlayer, pObject, planet ~= "") 
end

function BorNewsnet:addHeadline(headline) 
	if(headline.planet == "" or headline.planet == nil) then
		table.insert(self.headlines, headline)
	else 
		if(self.localHeadlines[headline.planet] == nil) then
			self.localHeadlines[headline.planet] = {}
		end
		table.insert(self.localHeadlines[headline.planet], headline)
	end
	
	Logger:log("Headline \"" .. headline.title .. "\" added to Newsnet Terminal", LT_INFO)
end

function BorNewsnet:addEvent(event)
	table.insert(self.events, event)
end

function BorNewsnet:displayEventList(pPlayer, pObject) 
	local suiManager = LuaSuiManager()
	local event = self.events[1]
	
	if(event == nil) then
		CreatureObject(pPlayer):sendSystemMessage("No events were found.")
		return 0
	end
	
	suiManager:sendMessageBox(pObject, pPlayer, "Galactic Events", event.content, "@ok", "BorNewsnet", "onCloseEvents", NEWSNET_INFO)
end

function BorNewsnet:onCloseEvents(pPlayer, pSui, eventIndex, rowIndex) 
	--WIP
end

function BorNewsnet:promptBroadcast(pPlayer, pObject)  
	local suiManager = LuaSuiManager()
	
	suiManager:sendInputBox(pObject, pPlayer, "BorNewsnet", "onSendBroadcastCallback", "Send a public broadcast across the holonet for everyone to see. Costs 100 credits per transmission.", "@ok")
end

function BorNewsnet:onSendBroadcastCallback(pPlayer, pSui, eventIndex, message)
	if(eventIndex == 1) then
		return 0
	end
	
	if(message == "") then
		return 0
	end
	
	--Check if we have the credits
	local playerCreditsCash = CreatureObject(pPlayer):getCashCredits()
	--If we do, subtract
	if(playerCreditsCash >= 100) then
	--Send message
		CreatureObject(pPlayer):subtractCashCredits(100)
		broadcastMessageToGalaxy(pPlayer, message)
	else
		CreatureObject(pPlayer):sendSystemMessage("To send a public broadcast requires 100 credits cash on hand.")
	end
end

--Menu Component Things

function BorNewsnetMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(20, 3, "Read Headlines")
	menuResponse:addRadialMenuItem(80, 3, "Check Upcoming Events")
	menuResponse:addRadialMenuItem(81, 3, "Send Broadcast")
end

function BorNewsnetMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end
	
	if (selectedID == 20) then --Display Headlines
		BorNewsnet:displayHolonetOptions(pPlayer, pObject)		
	elseif(selectedID == 80) then --Check Upcoming Events
		BorNewsnet:displayEventList(pPlayer, pObject)
	elseif(selectedID == 81) then --Send Broadcast
		BorNewsnet:promptBroadcast(pPlayer, pObject)
	end
	
	return 0
end