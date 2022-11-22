local themeTag = "general"

rpg_vt_general = {
	dialog = {
		greeting = "Hello. Would you like to browse my inventory?", --1
		browse = "What've you been in the market for?", --2
		items = "Here's what I have in stock.", --2
		startShopping = "All prices are final.", --3
		abort = "Come back any time!", --4
	}
}

RPGVendorThemes:addTheme(themeTag, rpg_vt_general)