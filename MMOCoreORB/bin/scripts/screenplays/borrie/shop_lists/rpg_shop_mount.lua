local shopListTag = "shop_mounts"

rpg_shop_mount = {
	manifest = {
		{
			name = "Mounts",
			minItems = 1,
			items = {
				{template = "object/weapon/ranged/pistol/pistol_dl44.iff", cost = 250, max = 10, chance = 100 },
				{template = "object/weapon/ranged/pistol/pistol_fwg5.iff", cost = 250, max = 10, chance = 100 },
			}
		},
	}	
}

RPGVendorShopLists:addShopList(shopListTag, rpg_shop_mount)