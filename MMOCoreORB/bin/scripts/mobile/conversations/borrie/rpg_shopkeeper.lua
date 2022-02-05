rpg_shopkeeper= ConvoTemplate:new {
  initialScreen = "greeting",
  templateType = "Lua",
  luaClassHandler = "rpg_shopkeeper_convo_handler",
  screens = {}
}

greeting = ConvoScreen:new {
  id = "greeting",
  customDialogText = "Hello there! I have many fine wares to sell. Would you like to look at my inventory?",
  stopConversation = "false",
  options = {
      {"Let me see what you've got.", "browse"},
      {"Not right now.", "abort"},
  }
}
rpg_shopkeeper:addScreen(greeting)

browse = ConvoScreen:new {
  id = "browse",
  customDialogText = "What've you been in the market for?",
  stopConversation = "false",
  options = {
    {"[Example Category]", "items"},
    {"Nevermind.", "abort"},
  }
}
rpg_shopkeeper:addScreen(browse)

items = ConvoScreen:new {
  id = "items",
  customDialogText = "This is what I have in stock.",
  stopConversation = "false",
  options = {
    {"[Example Item]", "shop"},
    {"Let's go back.", "browse"},
  }
}
rpg_shopkeeper:addScreen(items)


shop = ConvoScreen:new {
  id = "shop",
  customDialogText = "All prices are final. Have a look.",
  stopConversation = "true",
  options = {
  }
}
rpg_shopkeeper:addScreen(shop)

abort = ConvoScreen:new {
  id = "abort",
  customDialogText = "Come back anytime!",
  stopConversation = "true",
  options = {
  }
}
rpg_shopkeeper:addScreen(abort)

addConversationTemplate("rpg_shopkeeper", rpg_shopkeeper);
