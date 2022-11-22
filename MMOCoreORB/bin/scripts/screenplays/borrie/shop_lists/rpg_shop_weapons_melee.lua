local shopListTag = "shop_weapons_melee"

shop_weapons_melee = {
	manifest = {
		{
			name = "Two Handed Melee",
			minItems = 1,
			items = {
				{template = "object/weapon/roleplay/melee/twohanded/axe.iff", cost = 200, max = 10, chance = 100, overridePrice = false },
				{template = "object/weapon/roleplay/melee/twohanded/vibroaxe.iff", cost = 550, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/melee/twohanded/katana.iff", cost = 850, max = 10, chance = 100 },
			}
		},
		{
			name = "One Handed Melee",
			minItems = 1,
			items = {
				{template = "object/weapon/roleplay/ranged/onehanded/dagger.iff", cost = 50, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/melee/onehanded/sword.iff", cost = 55, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/melee/onehanded/mace.iff", cost = 500, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/melee/onehanded/stun_baton.iff", cost = 800, max = 10, chance = 100 },
			}
		},
		{
			name = "Polearms",
			minItems = 1,
			items = {
				{template = "object/weapon/roleplay/melee/polearm/wood_staff.iff", cost = 25, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/melee/polearm/metal_staff.iff", cost = 200, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/melee/polearm/reinforced_staff.iff", cost = 600, max = 10, chance = 100 },
			}
		},
	}	
}

RPGVendorShopLists:addShopList(shopListTag, shop_weapons_melee)