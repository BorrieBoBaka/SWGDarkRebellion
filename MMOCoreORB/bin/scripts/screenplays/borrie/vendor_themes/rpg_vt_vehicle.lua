local themeTag = "vehicle"

rpg_vt_vehicle = {
	dialog = {
		greeting = "You look like you're in the right point of your life to purchase a new vehicle. I've got a great selection, and they're waiting for you!", --1
		browse = "Sorry, I can't offer any test drives, but I do have an extended warranty I could offer you.", --2
		items = "Wait until you feel how this one controls...", --2
		startShopping = "Some might be used, but I'll tell you; they're in near perfect condition.", --3
		abort = "It's never too late to buy yourself a new vehicle, but it's better to buy sooner than later!", --4
	}
}


RPGVendorThemes:addTheme(themeTag, rpg_vt_vehicle)