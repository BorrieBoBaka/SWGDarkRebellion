--[[
rpgVendorShopListDirectory = {
	["shop_general"] = rpg_shop_general,
	["shop_weapons_melee_novice"] = rpg_shop_weapons_melee_novice,
	["shop_weapons_ranged_novice"] = rpg_shop_weapons_ranged_novice,
	["shop_camping"] = rpg_shop_camping,
	["shop_medicine_novice"] = rpg_shop_stimpack_novice,
	["shop_instruments"] = rpg_shop_instruments,
	["shop_mounts"] = rpg_shop_mounts,
	["shop_vehicles"] = rpg_shop_speeders,
}
--]]

RPGVendorShopLists = { }

function RPGVendorShopLists:addShopList(tag, group)
	RPGVendorShopLists[tag] = group;
end

function RPGVendorShopLists:getShopList(tag)
	return RPGVendorShopLists[tag]
end



