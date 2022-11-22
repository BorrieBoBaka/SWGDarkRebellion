--[[

rpgVendorThemeDirectory = {
	["general"] = rpg_vt_general,
	["novice_ranged"] = rpg_vt_weapon_vendor_ranged,
	["novice_melee"] = rpg_vt_weapon_vendor_melee,
	["camping"] = rpg_vt_camping,
	["medicine"] = rpg_vt_medicine,
	["music"] = rpg_vt_music,
	["mount"] = rpg_vt_mount,
	["vehicle"] = rpg_vt_vehicle,
}

--]]

RPGVendorThemes = { }

function RPGVendorThemes:addTheme(tag, group)
	RPGVendorThemes[tag] = group;
end

function RPGVendorThemes:getTheme(tag)
	return RPGVendorThemes[tag]
end

