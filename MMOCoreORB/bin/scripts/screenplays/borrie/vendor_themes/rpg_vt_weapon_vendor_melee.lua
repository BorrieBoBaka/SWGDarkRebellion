local themeTag = "novice_melee"

rpg_vt_weapon_vendor_melee = {
	dialog = {
		greeting = "Hitting something yourself is always preferable from afar. I've got quite an array of melee weapons on sale here. Care to buy one?", --1
		browse = "What've you been in the market for?", --2
		items = "Here's what I have in stock.", --2
		startShopping = "All prices are final.", --3
		abort = "Come back any time!", --4
	}
}

RPGVendorThemes:addTheme(themeTag, rpg_vt_weapon_vendor_melee)