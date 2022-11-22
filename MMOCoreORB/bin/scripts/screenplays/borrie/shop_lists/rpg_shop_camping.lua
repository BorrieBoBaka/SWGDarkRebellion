local shopListTag = "shop_camping"

rpg_shop_camping = {
	manifest = {
		{
			name = "Camp Kits",
			minItems = 1,
			items = {
				{template = "object/tangible/scout/camp/camp_basic.iff", 	cost = 5, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/scout/camp/camp_multi.iff", 	cost = 15, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/scout/camp/camp_improved.iff", cost = 50, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/scout/camp/camp_quality.iff", 	cost = 150, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/scout/camp/camp_elite.iff", 	cost = 500, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/scout/camp/camp_luxury.iff", 	cost = 1500, max = 10, chance = 100, overridePrice = true },
			}
		},
	}	
}

RPGVendorShopLists:addShopList(shopListTag, rpg_shop_camping)