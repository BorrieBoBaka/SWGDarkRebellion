local themeTag = "medicine"

rpg_vt_medicine = {
	dialog = {
		greeting = "Salutations, friend. It's always a good idea to keep at least some first aid with you at all times, especially if you go into dangerous areas. Would you care to buy some medicine?", --1
		browse = "Take a look at my selection of medicine. All seals are intact, and the quality grade is guaranteed.", --2
		items = "This is what I have available for this category.", --2
		startShopping = "I think you'll find the quality unmatched.", --3
		abort = "Fair is fair, but don't wait too long. You don't want to be dying and regret not purchasing these meds!", --4
	}
}

RPGVendorThemes:addTheme(themeTag, rpg_vt_medicine)