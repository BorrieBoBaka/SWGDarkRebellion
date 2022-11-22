rp_xov_tailor= ConvoTemplate:new {
  initialScreen = "intro",
  templateType = "Lua",
  luaClassHandler = "rp_xov_tailor_convo_handler",
  screens = {}
}

intro = ConvoScreen:new {
  id = "intro",
  customDialogText = "Oh a pleasure to greet you, gentlebeing. I am Jrick, and this is my tailoring shop. I hope you've come to consider a new look, or something to compliment your current style. I am certain you'll find something that will catch your eye. If you need assistance, do let me know.",
  stopConversation = "false",
  options = {
      {"How do I buy items?", "ask_buy"},
      {"You don't seem to be the tailoring type.", "ask_who"},
      {"Do you sell armor?", "ask_armor"},
  }
}
rp_xov_tailor:addScreen(intro)

ask_buy = ConvoScreen:new {
  id = "ask_buy",
  customDialogText = "Oh your money is no good here. Please, look through my various armoires and chests marked with the name of the item style within. If something catches your eye, simply take it out of the container and it is yours. My stock is bottomless, as should be your taste in style.",
  stopConversation = "false",
  options = {
      {"How do I buy items?", "ask_buy"},
      {"You don't seem to be the tailoring type.", "ask_who"},
      {"Do you sell armor?", "ask_armor"},
  }
}
rp_xov_tailor:addScreen(ask_buy)

ask_who = ConvoScreen:new {
  id = "ask_who",
  customDialogText = "I am but a simple tailor, my friend. I create style and fashion for those who crave it. You shouldn't judge a Jawa by his robe, so to speak. ",
  stopConversation = "false",
  options = {
      {"How do I buy items?", "ask_buy"},
      {"You don't seem to be the tailoring type.", "ask_who"},
      {"Do you sell armor?", "ask_armor"},
  }
}
rp_xov_tailor:addScreen(ask_who)

ask_armor = ConvoScreen:new {
  id = "ask_armor",
  customDialogText = "Alas I do not. Armor is something more valuable and more difficult to create. I focus on making you look good, but if you want someone to make you safe, I recommend finding an armorsmith. They will ask you for credits, however.",
  stopConversation = "false",
  options = {
      {"How do I buy items?", "ask_buy"},
      {"You don't seem to be the tailoring type.", "ask_who"},
      {"Do you sell armor?", "ask_armor"},
  }
}
rp_xov_tailor:addScreen(ask_armor)

addConversationTemplate("rp_xov_tailor", rp_xov_tailor);
