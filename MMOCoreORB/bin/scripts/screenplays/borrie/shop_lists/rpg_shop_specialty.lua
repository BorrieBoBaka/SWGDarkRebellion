local shopListTag = "shop_specialty"

rpg_shop_general = {
	manifest = {
		{
			name = "Utility Items",
			minItems = 1,
			items = {
				{template = "object/tangible/borrp/item/campfire_kit.iff", cost = 250, max = 10, chance = 100 },
				{template = "object/tangible/borrp/item/computer_spike.iff", cost = 250, max = 10, chance = 100 },
				{template = "object/tangible/borrp/item/hydrospanner.iff", cost = 250, max = 10, chance = 100 },
				{template = "object/tangible/borrp/item/prybar.iff", cost = 250, max = 10, chance = 100 },
				{template = "object/tangible/borrp/item/security_spike.iff", cost = 250, max = 10, chance = 100 }, 
			}
		},

	}	
}

RPGVendorShopLists:addShopList(shopListTag, rpg_shop_general)


