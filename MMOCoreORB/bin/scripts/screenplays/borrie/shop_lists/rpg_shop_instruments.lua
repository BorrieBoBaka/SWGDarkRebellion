local shopListTag = "shop_instruments"

rpg_shop_instruments = {
	manifest = {
		{
			name = "Musical Instruments",
			minItems = 1,
			items = {
				{template = "object/tangible/instrument/bandfill.iff", 		cost = 15, max = 10, chance = 100, overridePrice = true},
				{template = "object/tangible/instrument/fanfar.iff", 		cost = 15, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/instrument/fizz.iff", 			cost = 15, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/instrument/kloo_horn.iff", 		cost = 15, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/instrument/mandoviol.iff", 		cost = 15, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/instrument/nalargon.iff", 		cost = 15, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/instrument/ommni_box.iff", 		cost = 15, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/instrument/slitherhorn.iff", 	cost = 15, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/instrument/traz.iff", 			cost = 15, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/instrument/flute_droopy.iff", 	cost = 15, max = 10, chance = 100, overridePrice = true },
			}
		},
	}	
}

RPGVendorShopLists:addShopList(shopListTag, rpg_shop_instruments)