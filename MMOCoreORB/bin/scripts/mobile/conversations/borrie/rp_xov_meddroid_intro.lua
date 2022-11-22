rp_xov_meddroid_intro= ConvoTemplate:new {
  initialScreen = "intro",
  templateType = "Lua",
  luaClassHandler = "rp_xov_meddroid_intro_convo_handler",
  screens = {}
}

intro = ConvoScreen:new {
  id = "intro",
  customDialogText = "Please do not exert yourself. You've recently been exposed to high gravity forces. You may have questions. I cannot answer all of them, but I have been programmed with a few basic answers.",
  stopConversation = "false",
  options = {
      {"Where am I?", "ask_where"},
      {"How did I get here?", "ask_how"},
      {"Is there anything I should be doing?", "ask_what"},
      {"Where are my clothes?", "ask_clothing"},
      {"Who's in charge here?", "ask_leader"},
  }
}
rp_xov_meddroid_intro:addScreen(intro)

ask_where = ConvoScreen:new {
  id = "ask_where",
  customDialogText = "You are in Reiden Outpost, on the planet Xovros VI. Reiden Outpost is a prominent refueling station along the Hydian Way.",
  stopConversation = "false",
  options = {
	  {"Where am I?", "ask_where"},
      {"How did I get here?", "ask_how"},
      {"Is there anything I should be doing?", "ask_what"},
      {"Where are my clothes?", "ask_clothing"},
      {"Who's in charge here?", "ask_leader"},
  }
}
rp_xov_meddroid_intro:addScreen(ask_where)

ask_how = ConvoScreen:new {
  id = "ask_how",
  customDialogText = "You were pulled from your ship by the local security force. Volunteers are actively doing the same with more ships that are crashing to the surface. If you were with anyone, they may be around the camps being set up, or they might be dead. I'm afraid I can't say for certain.",
  stopConversation = "false",
  options = {
	  {"Where am I?", "ask_where"},
      {"How did I get here?", "ask_how"},
      {"Is there anything I should be doing?", "ask_what"},
      {"Where are my clothes?", "ask_clothing"},
      {"Who's in charge here?", "ask_leader"},
  }
}
rp_xov_meddroid_intro:addScreen(ask_how)

ask_what = ConvoScreen:new {
  id = "ask_what",
  customDialogText = "Until the current crisis has been resolved, I am afraid you may be stuck here. The Local Administration may be in need of volunteers as we deal with such a high influx of people. I am told that there is a need for scouts, scientists, and medics, among other things. The local Cantina has been stocked with information.",
  stopConversation = "false",
  options = {
	  {"Where am I?", "ask_where"},
      {"How did I get here?", "ask_how"},
      {"Is there anything I should be doing?", "ask_what"},
      {"Where are my clothes?", "ask_clothing"},
      {"Who's in charge here?", "ask_leader"},
  }
}
rp_xov_meddroid_intro:addScreen(ask_what)

ask_clothing = ConvoScreen:new {
  id = "ask_clothing",
  customDialogText = "We had to replace your clothing due to damage. If you'd like to get into something more your style, you can visit the tailor near the market place, at -5370, -2775. They have a fine selection for you to pick from, I am told.",
  stopConversation = "false",
  options = {
	  {"Where am I?", "ask_where"},
      {"How did I get here?", "ask_how"},
      {"Is there anything I should be doing?", "ask_what"},
      {"Where are my clothes?", "ask_clothing"},
      {"Who's in charge here?", "ask_leader"},
  }
}
rp_xov_meddroid_intro:addScreen(ask_clothing)

ask_leader = ConvoScreen:new {
  id = "ask_leader",
  customDialogText = "Madam Administrator Draticce Larmand is the primary leader of Reiden Outpost and the Xovros system. Head of Security Tremove Lycrest is leading the effort to rescue those who have fallen to the surface. Dr. Hadkor Cakane is our primary medical officer.",
  stopConversation = "false",
  options = {
	  {"Where am I?", "ask_where"},
      {"How did I get here?", "ask_how"},
      {"Is there anything I should be doing?", "ask_what"},
      {"Where are my clothes?", "ask_clothing"},
      {"Who's in charge here?", "ask_leader"},
  }
}
rp_xov_meddroid_intro:addScreen(ask_leader)

addConversationTemplate("rp_xov_meddroid_intro", rp_xov_meddroid_intro);
