local shopListTag = "shop_mounts_tatooine"

rpg_shop_mount_tatooine = {
	manifest = {
		{
			name = "Mounts",
			minItems = 1,
			items = {
				{template = "object/tangible/deed/pet_deed/bantha_deed.iff", cost = 500, max = 10, chance = 100, overridePrice = true, isMount = true},
				{template = "object/tangible/deed/pet_deed/dewback_deed.iff", cost = 1000, max = 10, chance = 100, overridePrice = true, isMount = true},
				{template = "object/tangible/deed/pet_deed/cu_pa_deed.iff", cost = 3000, max = 10, chance = 100, overridePrice = true, isMount = true},
			}
		},
	}	
}

RPGVendorShopLists:addShopList(shopListTag, rpg_shop_mount_tatooine)