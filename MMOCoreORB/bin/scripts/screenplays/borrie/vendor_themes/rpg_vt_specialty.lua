local themeTag = "specialty"

vt = {
	dialog = {
		greeting = "Greetings, Customer. If you need it, we probably have it. How may I help you?", --1
		browse = "We have a wide array of goods. What is it you might be looking for in particular?", --2
		items = "This is everything we have for that particular category. See anything you like?", --2
		startShopping = "Take a closer look, of course. I can guarantee it will work as intended, at the very least.", --3
		abort = "I hope you grace our store with your presence once more. Good luck on your travels.", --4
	}
}

RPGVendorThemes:addTheme(themeTag, vt)