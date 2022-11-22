local themeTag = "music"

rpg_vt_music = {
	dialog = {
		greeting = "What's up? I'm selling the finest instruments to play the most beautiful music, if you're interested. The ultimate form of auditory expression is only a few credits away...", --1
		browse = "There's all sorts of ways to create the music that drives you. What sound calls to you the most?", --2
		items = "From the humble Slitherhorn, to the majestic Nalargon...", --2
		startShopping = "Be sure to take a moment to feel the instrument... see if it fits within your grasp...", --3
		abort = "Let the rhythm guide you, be it away from here, or back to me. ", --4
	}
}

RPGVendorThemes:addTheme(themeTag, rpg_vt_music)