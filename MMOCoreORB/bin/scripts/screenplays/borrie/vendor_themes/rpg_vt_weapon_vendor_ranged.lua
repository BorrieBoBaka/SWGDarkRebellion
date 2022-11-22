local themeTag = "novice_ranged"

rpg_vt_weapon_vendor_ranged = {
	dialog = {
		greeting = "Greetin's. You got something you need shot? I got just the thing for you.", --1
		browse = "What've you been in the market for?", --2
		items = "Here's what I have in stock.", --2
		startShopping = "All prices are final.", --3
		abort = "Come back any time!", --4
	}
}

RPGVendorThemes:addTheme(themeTag, rpg_vt_weapon_vendor_ranged)