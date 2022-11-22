local shopListTag = "shop_vehicles"

rpg_shop_speeders = {
	manifest = {
		{
			name = "Vehicles",
			minItems = 1,
			items = {
				{template = "object/tangible/deed/vehicle_deed/speederbike_deed.iff", cost = 4800, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/deed/vehicle_deed/speederbike_swoop_deed.iff", cost = 5750, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/deed/vehicle_deed/landspeeder_x34_deed.iff", cost = 5000, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/deed/vehicle_deed/landspeeder_v35_deed.iff", cost = 6500, max = 10, chance = 100, overridePrice = true },				
				{template = "object/tangible/deed/vehicle_deed/landspeeder_ab1_deed.iff", cost = 8000, max = 10, chance = 100, overridePrice = true },
				{template = "object/tangible/deed/vehicle_deed/landspeeder_xp38_deed.iff", cost = 12000, max = 10, chance = 100, overridePrice = true },
			}
		},
	}	
}

RPGVendorShopLists:addShopList(shopListTag, rpg_shop_speeders)