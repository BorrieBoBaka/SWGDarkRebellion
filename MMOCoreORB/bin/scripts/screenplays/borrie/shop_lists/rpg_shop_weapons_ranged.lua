local shopListTag = "shop_weapons_ranged"

shop_weapons_ranged = {
	manifest = {
		{
			name = "Pistols",
			minItems = 1,
			items = {
				{template = "object/weapon/roleplay/ranged/pistol/flare_gun.iff", cost = 100, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/pistol/ion_pistol.iff", cost = 250, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/pistol/d18_pistol.iff", cost = 350, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/pistol/dl44_blaster_pistol.iff", cost = 400, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/pistol/dl44_metal_blaster_pistol.iff", cost = 450, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/pistol/power_5_heavy_blaster_pistol.iff", cost = 900, max = 10, chance = 100 },
			}
		},
		{
			name = "Rifles",
			minItems = 1,
			items = {
				{template = "object/weapon/roleplay/ranged/rifle/ion_rifle.iff", cost = 300, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/rifle/tusken_elite_rifle.iff", cost = 400, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/rifle/sg82b_stun_rifle.iff", cost = 700, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/rifle/dp23_rifle.iff", cost = 1800, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/rifle/laser_rifle.iff", cost = 2000, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/rifle/berserker_rifle.iff", cost = 2000, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/rifle/bowcaster.iff", cost = 2000, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/rifle/cm_sniper_rifle.iff", cost = 2000, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/rifle/czerka_adventurer.iff", cost = 2000, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/rifle/dawnsorrow_rifle.iff", cost = 2000, max = 10, chance = 100 },
			}
		},
		{
			name = "Carbines",
			minItems = 1,
			items = {

				{template = "object/weapon/roleplay/ranged/carbine/ee3_carbine.iff", cost = 600, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/carbine/laser_carbine.iff", cost = 700, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/carbine/elite_carbine.iff", cost = 1500, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/carbine/charric_carbine.iff", cost = 1500, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/carbine/corestrike_rancor_carbine.iff", cost = 1500, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/carbine/firestar_10k.iff", cost = 1500, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/carbine/proton_carbine.iff", cost = 1500, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/carbine/sfor_republic_carbine.iff", cost = 1500, max = 10, chance = 100 },
				{template = "object/weapon/roleplay/ranged/carbine/wookiee_carbine.iff", cost = 1500, max = 10, chance = 100 },
			}
		},
	}	
}

RPGVendorShopLists:addShopList(shopListTag, shop_weapons_ranged)