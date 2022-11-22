rp_convo_recruiter = ConvoTemplate:new {
  initialScreen = "greeting",
  templateType = "Lua",
  luaClassHandler = "rp_recruiter_convo_handler",
  screens = {}
}

greeting = ConvoScreen:new {
  id = "greeting",
  customDialogText = "Hello, stranger! Would you like to join our cause?",
  stopConversation = "false",
  options = {
      {"I want to join!", "join"},
	  {"Tell me more about your cause.", "new_ask_about"},
      {"No thanks.", "refuse_join"},
  }
}
rp_convo_recruiter:addScreen(greeting)

greeting_member = ConvoScreen:new {
  id = "greeting_member",
  customDialogText = "Greetings comrade. Is there something I can help you with?",
  stopConversation = "false",
  options = {
      {"I'd like to report in for today.", "report"},
	  {"I'd like to discuss advancement.", "ask_promotion"},
	  {"May I requsition some equipment?", "ask_requisition"},
	  {"I'd like to request special training.", "ask_training"},
	  {"What are my orders?", "ask_orders"},
	  {"What's our status?", "ask_about"},
      {"Not right now, thanks.", "abort"},
  }
}
rp_convo_recruiter:addScreen(greeting_member)

ask_requisition = ConvoScreen:new {
  id = "ask_requisition",
  customDialogText = "ask_requisition",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(ask_requisition)

req_ask_uniform = ConvoScreen:new {
  id = "req_ask_uniform",
  customDialogText = "req_ask_uniform",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(req_ask_uniform)

req_ask_loadout = ConvoScreen:new {
  id = "req_ask_loadout",
  customDialogText = "req_ask_loadout",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(req_ask_loadout)

req_ask_id = ConvoScreen:new {
  id = "req_ask_id",
  customDialogText = "req_ask_id",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(req_ask_id)

join = ConvoScreen:new {
  id = "join",
  customDialogText = "join",
  stopConversation = "true",
  options = {

  }
}
rp_convo_recruiter:addScreen(join)

leave = ConvoScreen:new {
  id = "leave",
  customDialogText = "leave",
  stopConversation = "true",
  options = {

  }
}
rp_convo_recruiter:addScreen(leave)

inquire = ConvoScreen:new {
  id = "inquire",
  customDialogText = "inquire",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(inquire)

return_menu = ConvoScreen:new {
  id = "return_menu",
  customDialogText = "return_menu",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(return_menu)

report = ConvoScreen:new {
  id = "report",
  customDialogText = "report",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(report)

ask_promotion = ConvoScreen:new {
  id = "ask_promotion",
  customDialogText = "ask_promotion",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(ask_promotion)

ask_training = ConvoScreen:new {
  id = "ask_training",
  customDialogText = "ask_training",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(ask_training)

grant_training = ConvoScreen:new {
  id = "grant_training",
  customDialogText = "grant_training",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(grant_training)

ask_orders = ConvoScreen:new {
  id = "ask_orders",
  customDialogText = "ask_orders",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(ask_orders)

ask_status = ConvoScreen:new {
  id = "ask_status",
  customDialogText = "ask_status",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(ask_status)

enemy_greeting = ConvoScreen:new {
  id = "enemy_greeting",
  customDialogText = "enemy_greeting",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(enemy_greeting)

ally_greeting = ConvoScreen:new {
  id = "ally_greeting",
  customDialogText = "ally_greeting",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(ally_greeting)

traitor1_greeting = ConvoScreen:new {
  id = "traitor1_greeting",
  customDialogText = "traitor1_greeting",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(traitor1_greeting)

traitor2_greeting = ConvoScreen:new {
  id = "traitor2_greeting",
  customDialogText = "traitor2_greeting",
  stopConversation = "false",
  options = {
      {"I should go.", "abort"},
  }
}
rp_convo_recruiter:addScreen(traitor2_greeting)

addConversationTemplate("rp_convo_recruiter", rp_convo_recruiter);