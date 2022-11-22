rp_recruiter_convo_handler = Object:new {
}

function rp_recruiter_convo_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption)
    -- Assign the player to variable creature for use inside this function.
    local creature = LuaCreatureObject(conversingPlayer)
    -- Get the last conversation to determine whetehr or not we're  on the first screen
    local convosession = creature:getConversationSession()
    lastConversation = nil
    local conversation = LuaConversationTemplate(conversationTemplate)



    -- If there is a conversation open, do stuff with it
    if ( conversation ~= nil ) then
    -- check to see if we have a next screen
        if ( convosession ~= nil ) then
            local session = LuaConversationSession(convosession)
            if ( session ~= nil ) then
                lastConversationScreen = session:getLastConversationScreen()
            end
        end
        -- Last conversation was nil, so get the first screen
        if ( lastConversationScreen == nil ) then
            nextConversationScreen = conversation:getScreen("greeting")
        else
            -- Start playing the rest of the conversation based on user input
            local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
            -- Set variable to track what option the player picked and get the option picked
            local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
            nextConversationScreen = conversation:getScreen(optionLink)
        end
    end
-- end of the conversation logic.

	if ( lastConversationScreen ~= nil ) then
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		local optionData = luaLastConversationScreen:getOptionData(selectedOption)
		SceneObject(conversingPlayer):setStoredInt("faction_conv_last_index", tonumber(optionData))		
	end	
		
return nextConversationScreen
end

function rp_recruiter_convo_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
    -- Plays the screens of the conversation.
    local player = LuaSceneObject(conversingPlayer)
    local screen = LuaConversationScreen(conversationScreen)
    local screenID = screen:getScreenID()
    local pConvScreen = screen:cloneScreen()
    local clonedConversation = LuaConversationScreen(pConvScreen)
	


	
	--Get personal data about this nPC.
	local factionTag = SceneObject(conversingNPC):getStoredString("rp_faction")
	local faction = BorFactionManager.factions[factionTag]
	local themeTag = SceneObject(conversingNPC):getStoredString("rp_fac_recruiter_theme")
	local theme = BorFactionManager.recruiterThemes[themeTag]
	
	--Get personal data about the Player
	local playerFactionTag = SceneObject(conversingPlayer):getStoredString("faction_current")
	
	--DEBUG
	--playerFactionTag = "empire"
	
	--CreatureObject(conversingPlayer):sendSystemMessage(factionTag .. " " .. themeTag .. " " .. screenID .. "!")
	
	
	clonedConversation:removeAllOptions()
		
	--Set logic for which logic to take for the first screen.
	if(screenID == "greeting") then
		if(playerFactionTag == "") then
			traitorLevel = BorFactionManager:getTraitorLevel(conversingPlayer, factionTag)
			if(traitorLevel == 1) then
				screenID = "traitor1_greeting"
			elseif(traitorLevel == 2) then
				screenID = "traitor2_greeting"
			else 
				screenID = "greeting"
			end			
		elseif(playerFactionTag == factionTag) then
			screenID = "greeting_member"
		elseif(BorFactionManager:getFactionIsEnemy(factionTag, playerFactionTag) == true) then
			screenID = "enemy_greeting"
		elseif(BorFactionManager:getFactionIsAlly(factionTag, playerFactionTag) == true) then
			screenID = "ally_greeting"
		end
	end
	
	
	if(screenID == "greeting") then
		clonedConversation:setCustomDialogText(theme.greeting)
		clonedConversation:addOption("I'd like to join the " .. faction.name, "join")
		clonedConversation:addOption("What is the " .. faction.name .. " all about?", "inquire")
		clonedConversation:addOption("I should be going.", "abort")
	elseif(screenID == "join") then
		clonedConversation:setCustomDialogText(theme.join)
		--Send SUI to prompt if they'd like to join. 
		BorFactionManager:playerPromptJoinFaction(conversingPlayer, faction.tag)		
	elseif(screenID == "leave") then
		clonedConversation:setCustomDialogText(theme.leave)
		--Send SUI to prompt if they'd like to leave. 
		BorFactionManager:playerPromptLeaveFaction(conversingPlayer, faction.tag)	
	elseif(screenID == "inquire") then
		clonedConversation:setCustomDialogText(theme.inquire)
		clonedConversation:addOption("I'd like to join the " .. faction.name, "join")
		clonedConversation:addOption("I should be going.", "abort")	
	elseif(screenID == "greeting_member" or screenID == "return_menu") then
		if(screenID == "return_menu") then
			clonedConversation:setCustomDialogText(theme.return_menu)
		else
			clonedConversation:setCustomDialogText(theme.member_greeting)
		end
		if(BorFactionManager:canReportIn(conversingPlayer)) then
			clonedConversation:addOption("Reporting in for the day.", "report")
		end		
		clonedConversation:addOption("Am I eligible for advancement?", "ask_promotion")
		clonedConversation:addOption("I'd like to make a requisition", "ask_requisition")
		clonedConversation:addOption("I'm looking for training", "ask_training")
		--clonedConversation:addOption("What are my orders?", "ask_orders")
		--clonedConversation:addOption("Can I have a status report of the " .. faction.name .. "?", "ask_status")
		clonedConversation:addOption("I would like to tender my resignation.", "leave")
		clonedConversation:addOption("I'll be going.", "abort")
	elseif(screenID == "report") then
		clonedConversation:setCustomDialogText(theme.report)
		--Report In
		BorFactionManager:reportIn(conversingPlayer)
		clonedConversation:addOption("I'd like to discuss something else.", "return_menu")
		clonedConversation:addOption("I'll be going.", "abort")
	elseif(screenID == "ask_promotion") then
		clonedConversation:setCustomDialogText(theme.promotion)
		BorFactionManager:promptPromotion(conversingPlayer)
		clonedConversation:addOption("Thank you, though I'd like to discuss something else.", "return_menu")
		clonedConversation:addOption("Thank you.", "abort")
	elseif(screenID == "ask_training") then
		clonedConversation:setCustomDialogText(theme.training)
		for i = 1, #faction.training, 1 do
			clonedConversation:addOptionWithData(faction.training[i], tostring(i))
		end
		clonedConversation:addOption("I'd like to discuss something else.", "return_menu")
	elseif(screenID == "grant_training") then
		clonedConversation:setCustomDialogText(theme.training_grant)
		BorFactionManager:promptGainTraining(conversingPlayer, SceneObject(conversingPlayer):getStoredInt("faction_conv_last_index"))
		clonedConversation:addOption("I'd like to discuss something else.", "return_menu")
	elseif(screenID == "ask_orders") then
		clonedConversation:setCustomDialogText(theme.orders)
		clonedConversation:addOption("I'd like to discuss something else.", "return_menu")
	elseif(screenID == "ask_status") then
		clonedConversation:setCustomDialogText(theme.status)
		clonedConversation:addOption("I'd like to discuss something else.", "return_menu")
	elseif(screenID == "enemy_greeting") then
		clonedConversation:setCustomDialogText(theme.enemy_greeting)
		clonedConversation:addOption("Until we meet again...", "abort")
	elseif(screenID == "ally_greeting") then
		clonedConversation:setCustomDialogText(theme.ally_greeting)
		clonedConversation:addOption("What is the " .. faction.name .. " all about?", "inquire")
		clonedConversation:addOption("Have a good day!", "abort")
	elseif(screenID == "traitor1_greeting") then
		clonedConversation:setCustomDialogText(theme.traitor1_greeting)
		clonedConversation:addOption("I was an undercover agent. I am returning home.", "abort")
		clonedConversation:addOption("I should go.", "abort")
	elseif(screenID == "traitor2_greeting") then
		clonedConversation:setCustomDialogText(theme.traitor2_greeting)
		clonedConversation:addOption("I've made my decision. Goodbye.", "abort")
	elseif(screenID == "ask_requisition") then
		clonedConversation:setCustomDialogText(theme.requisition_options)
		clonedConversation:addOption("I need a new uniform.", "req_ask_uniform")
		clonedConversation:addOption("I need my munitions loadout.", "req_ask_loadout")
		clonedConversation:addOption("Nevermind", "return_menu")
	elseif(screenID == "req_ask_uniform") then
		clonedConversation:setCustomDialogText(theme.get_req_uniform)
		clonedConversation:addOption("Thank you.", "return_menu")
		BorFactionManager:getRequisitionUniform(conversingPlayer)
	elseif(screenID == "req_ask_loadout") then
		clonedConversation:setCustomDialogText(theme.get_req_loadout)
		clonedConversation:addOption("Thank you.", "return_menu")
		BorFactionManager:getRequisitionLoadout(conversingPlayer)
	elseif(screenID == "req_ask_id") then
		clonedConversation:setCustomDialogText(theme.get_req_id)
		clonedConversation:addOption("Thank you.", "return_menu")
		BorFactionManager:getRequisitionLoadout(conversingPlayer)
	end
	
    return pConvScreen
end