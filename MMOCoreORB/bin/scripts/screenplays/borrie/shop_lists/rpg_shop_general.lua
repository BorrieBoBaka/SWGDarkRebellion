local shopListTag = "shop_general"

rpg_shop_general = {
	manifest = {
		{
			name = "Pistols",
			minItems = 1,
			items = {
				{template = "object/weapon/ranged/pistol/pistol_dl44.iff", cost = 250, max = 10, chance = 100 },
				{template = "object/weapon/ranged/pistol/pistol_fwg5.iff", cost = 250, max = 10, chance = 100 },
			}
		},
		{
			name = "Armor",
			minItems = 2,
			items = {
				{template = "object/tangible/wearables/armor/chitin/armor_chitin_s01_helmet.iff", cost = 250, max = 10, chance = 100 },
				{template = "object/tangible/wearables/armor/composite/armor_composite_chest_plate.iff", cost = 250, max = 10, chance = 100 },
			}
		},
	}	
}

RPGVendorShopLists:addShopList(shopListTag, rpg_shop_general)
