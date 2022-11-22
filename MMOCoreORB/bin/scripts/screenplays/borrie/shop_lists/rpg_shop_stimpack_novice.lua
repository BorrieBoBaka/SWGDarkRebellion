local shopListTag = "shop_medicine_novice"

rpg_shop_stimpack_novice = {
	manifest = {
		{
			name = "Medicine",
			minItems = 1,
			items = {
				{template = "object/tangible/medicine/roleplay/rp_stimpack_a.iff", cost = 100, max = 10, chance = 100, overridePrice = true },
			}
		},
	}	
}

RPGVendorShopLists:addShopList(shopListTag, rpg_shop_stimpack_novice)