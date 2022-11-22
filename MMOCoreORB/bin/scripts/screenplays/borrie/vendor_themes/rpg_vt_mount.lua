local themeTag = "mount"

rpg_vt_mount = {
	dialog = {
		greeting = "Hello! It seems like you could use an animal companion to help carry you on your journies. Care to meet one?", --1
		browse = "I take pride in raising these beasts of burden, they'll all have the perfect temperment for you.", --2
		items = "Here, let me show you who my favorites are...", --2
		startShopping = "I'm sure you'll find the right creature, have a look.", --3
		abort = "Fair enough, if you ever change your mind, we'll be here.", --4
	}
}

RPGVendorThemes:addTheme(themeTag, rpg_vt_mount)