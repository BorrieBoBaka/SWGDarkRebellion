local themeTag = "camping"

rpg_vt_camping = {
	dialog = {
		greeting = "Ayo, lookin' to rough it out there? I've got camping equipment for all your needs.", --1
		browse = "You got an idea what you're looking for? You can't go wrong with the basic kit, but if you'd like to upgrade...", --2
		items = "Here's some of the best camping supplies money can buy.", --2
		startShopping = "All prices are final.", --3
		abort = "If you're ever stuck out in the rain or shine, think of me!", --4
	}
}

RPGVendorThemes:addTheme(themeTag, rpg_vt_camping)