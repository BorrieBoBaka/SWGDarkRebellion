SulonSaltaloStationScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "SulonSaltaloStationScreenPlay",

	planet = "rp_sulon",	
	
	walkpointList = {
		
	}
}

registerScreenPlay("SulonSaltaloStationScreenPlay",  true)

function SulonSaltaloStationScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnSceneObjects()
		self:spawnCivilians()
	end
end

function SulonSaltaloStationScreenPlay:spawnCivilians() 
	local waypointList = {
		{4240.97, 6, -5398.66, 305, 0,{"tech"},""},
		{4249.54, 6, -5386.5, 224, 0,{"social"},""},
		{4248.48, 6, -5387.2, 68, 0,{"social"},""},
		{4258.2, 6, -5385.92, 91, 0,{"social"},""},
		{4259.82, 6, -5385.38, 227, 0,{"social"},""},
		{4259.53, 6, -5386.41, 322, 0,{"social"},""},
		{4303.95, 6, -5416.15, 194, 0,{"social"},""},
		{4304.45, 6, -5416.8, 280, 0,{"social"},""},
		{4303.8, 6, -5417.5, 0, 0,{"social"},""},
		{4239.86, 6, -5434.64, 81, 0,{"social"},""},
		{4240.35, 6, -5435.68, 18, 0,{"social"},""},
		{4241.41, 6, -5434.97, 304, 0,{"social"},""},
		{4241.28, 6, -5433.79, 216, 0,{"social"},""},
		{4206.73, 6, -5413.12, 327, 0,{"social"},""},
		{4205.91, 6, -5411.36, 163, 0,{"social"},""},
		{4195.55, 6, -5398.99, 338, 0,{"social"},""},
		{4195.35, 6, -5397.46, 193, 0,{"social"},""},
		{7.51514, 0.874984, 0.476074, 62, 10000027,{"sittable"},""},
		{9.59473, 0.874984, 2.29004, 215, 10000027,{"sittable"},""},
		{7.74365, 0.874984, 2.4917, 143, 10000027,{"sittable"},""},
		{0.105469, 0.874984, 5.62256, 241, 10000027,{"sittable"},""},
		{-1.68213, 0.874984, 4.39551, 49, 10000027,{"sittable"},""},
		{-7.3892, 0.875, 3.1023, 251, 10000047,{"drinker"},""},
		{-8.53678, 0.875001, 4.61138, 196, 10000047,{"drinker"},""},
		{-8.54133, 0.875004, -6.39968, 0, 10000047,{"drinker"},""},
		{4184.9, 6, -5438.68, 0, 0,{"tech"},""},
		{4188.71, 9.86328, -5460.34, 265, 0,{"none"},""},
		{4184.82, 6, -5395.39, 192, 0,{"social"},""},
		{4184.84, 6, -5396.74, 347, 0,{"social"},""},
		{4187.88, 6, -5391.86, 186, 0,{"none"},""},
		{4190.53, 6, -5397.26, 90, 0,{"none"},""},
		{4190.66, 6, -5398.24, 83, 0,{"none"},""},
		{4192, 6, -5403.69, 178, 0,{"none"},""},
		{4176.17, 6, -5384.6, 319, 0,{"none"},""},
		{4215.65, 6, -5367.04, 37, 0,{"none"},""},
		{4229.09, 7.92253, -5324.73, 325, 0,{"sit"},""},
		{4229.89, 7.95273, -5323.93, 309, 0,{"sit"},""},
		{4279.54, 6, -5388.11, 268, 0,{"none"},""},
		{4286.38, 6, -5389.65, 178, 0,{"sit"},""},
		{4303.17, 10.3389, -5439.26, 0, 0,{"sit"},""},
		{-6.25684, 0.528463, -0.399414, 90, 10000058,{"sitchair"},""},
		{-6.22705, 0.528463, -1.30957, 73, 10000058,{"sitchair"},""},
		{4350.24, 6, -5384.26, 230, 0,{"none"},""},
		{4323.24, 6, -5389, 311, 0,{"tech"},""},
		{4323.06, 6, -5413.87, 179, 0,{"social"},""},
		{4322.18, 6, -5414.75, 89, 0,{"social"},""},
	}
	
	CivillianGenerator:spawnCivillians(self.screenplayName, "rp_sulon", waypointList, self.walkpointList, "sulon", "sulon")
end

function SulonSaltaloStationScreenPlay:spawnSceneObjects() 
	--Travel Terminals
	spawnSceneObject("rp_sulon", "object/tangible/terminal/terminal_travel_rp.iff", 4316.23, 6, -5390.87, 0, 0, 0, 1, 0)
	
	--Signs
	local sObj = spawnSceneObject("rp_sulon", "object/tangible/sign/player/shop_sign_s01.iff", 4244.06, 6, -5392.05, 0, 1, 0, 0, 0) -- Plainswalker Guns
	SceneObject(sObj):setCustomObjectName("Plainswalker Guns")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/sign/house_sign_consumable_object.iff", 4197.06, 10.5732, -5428.26, 0, -0.92388, 0, 0.382683, 0) --The Salty Saloon
	SceneObject(sObj):setCustomObjectName("The Salty Saloon")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/sign/player/shop_sign_s04.iff", 4195.46, 9.85938, -5462.38, 0, 1, 0, 0, 0) --South River Tailoring
	SceneObject(sObj):setCustomObjectName("South River Tailoring")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/sign/streetsign_upright_style_01.iff", 4212.29, 6.5, -5445.98, 0, 1, 0, 0, 0) --Station Administration
	SceneObject(sObj):setCustomObjectName("Station Administration")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/sign/player/shop_sign_s03.iff", 4266.47, 6, -5375.98, 0, 1, 0, 0, 0) --Saltalo Med Center
	SceneObject(sObj):setCustomObjectName("Saltalo Med Center")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/sign/player/shop_sign_s03.iff", 4225.48, 6, -5344.27, 0, 1, 0, 0, 0) --Saltalo Med Center
	SceneObject(sObj):setCustomObjectName("Saltalo Med Center")
	
	--TAILOR--
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_cabinet_s01.iff", 1.34424, 0.625, 0.176758, 10000185, 1, 0, 0, 0) --Shirts
	SceneObject(sObj):setCustomObjectName("Shirts")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_shirts")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_cabinet_s01.iff", -0.208496, 0.625, 0.176758, 10000185, 1, 0, 0, 0) --Pants
	SceneObject(sObj):setCustomObjectName("Pants")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_pants")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_cabinet_s01.iff", -1.77686, 0.625, 0.176758, 10000185, 1, 0, 0, 0) --Footwear
	SceneObject(sObj):setCustomObjectName("Footwear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_footwear")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_cabinet_s01.iff", -3.37451, 0.625, 0.176758, 10000185, 1, 0, 0, 0)--Jacket
	SceneObject(sObj):setCustomObjectName("Jacket")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_jackets")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", -3.33594, 2.69809, -0.0209961, 10000185, 1, 0, 0, 0) --Vest
	SceneObject(sObj):setCustomObjectName("Vest")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_vests")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", -1.73633, 2.69809, -0.0209961, 10000185, 1, 0, 0, 0) --Robes
	SceneObject(sObj):setCustomObjectName("Robes")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_robes")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", -0.185059, 2.69809, -0.0209961, 10000185, 1, 0, 0, 0) --Bodysuits
	SceneObject(sObj):setCustomObjectName("Bodysuits")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_bodysuits")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", 1.40088, 2.69809, -0.0209961, 10000185, 1, 0, 0, 0) --Skirts
	SceneObject(sObj):setCustomObjectName("Skirts")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_skirts")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", -0.898438, 1.625, 6.69434, 10000185, 0, 0, 1, 0) --Women
	SceneObject(sObj):setCustomObjectName("Women's Wear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_women")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", 0.101562, 1.625, 6.69434, 10000185, 0, 0, 1, 0) --Heaad & Goggle
	SceneObject(sObj):setCustomObjectName("Headwear & Goggles")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_headwear")
	SceneObject(sObj):populateInventoryFromContentList("tailor_goggles")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", 1.10156, 1.625, 6.69434, 10000185, 0, 0, 1, 0) --Handwear
	SceneObject(sObj):setCustomObjectName("Handwear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_handwear")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", 2.10156, 1.625, 6.69434, 10000185, 0, 0, 1, 0) --Jewelry
	SceneObject(sObj):setCustomObjectName("Jewelry")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_jewelry")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", -1.39844, 0.625, 6.69434, 10000185, 0, 0, 1, 0) --Misc/Belts
	SceneObject(sObj):setCustomObjectName("Belts, Bandoliers & Aprons")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_misc")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", -0.398438, 0.625, 6.69434, 10000185, 0, 0, 1, 0) --Bikinis
	SceneObject(sObj):setCustomObjectName("Bikinis")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_bikinis")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", 0.601562, 0.625, 6.69434, 10000185, 0, 0, 1, 0) --Wookiee
	SceneObject(sObj):setCustomObjectName("Wookiee Wear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_wookiee")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", 1.60156, 0.625, 6.69434, 10000185, 0, 0, 1, 0) --Ithorian 1
	SceneObject(sObj):setCustomObjectName("Ithorian Wear I")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_ithorian1")
	sObj = spawnSceneObject("rp_sulon", "object/tangible/furniture/plain/plain_chest_s01.iff", 2.60156, 0.625, 6.69434, 10000185, 0, 0, 1, 0) --Ithorian 2
	SceneObject(sObj):setCustomObjectName("Ithorian Wear II")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_ithorian2")

end

function SulonSaltaloStationScreenPlay:spawnMobiles()
	--Species, Equipment, Skills, Customization
	local pNpc = spawnRoleplayMobile("rp_sulon", "rp_convo_npc", 1, 4178.07, 6, -5382.97, 180, 0, "rp_sullustan_male", "sulon_vendor_melee_01", "default", "random", "rpg_shopkeeper") --Melee Vendor
	SceneObject(pNpc):setCustomObjectName("Targo Lien (a Melee Weapons Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "novice_melee")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_weapons_melee_novice")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_convo_npc", 1, 4186.12, 6, -5375.92, 86, 0,  "rp_bith_male", "sulon_vendor_instrument_01", "default", "random", "rpg_shopkeeper") -- Instrument vendor
	SceneObject(pNpc):setCustomObjectName("Snikk (an Instrument Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "music")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_instruments")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4182.62, 6, -5391.78, 48, 0, "rp_human_male", "xovros_vendor_generic1", "default", "random") --Regular Merchant
	SceneObject(pNpc):setCustomObjectName("a Merchant Vendor")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4190.05, 6, -5403.71, 0, 0, "rp_human_male", "xovros_vendor_generic2", "default", "random") --Regular Merchant
	SceneObject(pNpc):setCustomObjectName("a Merchant Vendor")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4195.07, 6, -5396.05, 269, 0, "rp_human_female", "xovros_vendor_generic", "default", "random") --Regular Merchant
	SceneObject(pNpc):setCustomObjectName("a Merchant Vendor")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_convo_npc", 1, 4222.47, 6, -5356.66, 307, 0, "rp_human_male", "sulon_vendor_scout_01", "default", "random", "rpg_shopkeeper") --Camp Vendor
	SceneObject(pNpc):setCustomObjectName("Steaph Levins (a Camping Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "camping")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_camping")
	--pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, -0.871872, 0.525372, 3.46328, 223, 10000058) --Receptionist Droid
	--pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 1.73973, 0.52165, -3.91691, 279, 10000058) --Administrator
	--pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4.69587, 0.525936, 1.79575, 44, 10000058) --Admin tech
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4185.87, 6.13379, -5454.74, 279, 0, "rp_human_female", "sulon_station_guard", "default", "random") --Guard
	SceneObject(pNpc):setCustomObjectName("a Saltalo Station Militaman")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_convo_npc", 1, 4241.71, 6, -5392.86, 130, 0, "rp_human_male", "sulon_vendor_ranged_01", "default", "random", "rpg_shopkeeper") --Ranged Vendor
	SceneObject(pNpc):setCustomObjectName("Taprindicio Plainswalker (a Ranged Weapon Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "novice_ranged")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_weapons_ranged_novice")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, -1.27067, 0.184067, 0.757029, 122, 10000022, "rp_sullustan_male", "outpost_doctor", "default", "random") -- Doctor
	SceneObject(pNpc):setCustomObjectName("Dr. Ooenub Soroq")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_convo_npc", 1, 2.87014, 0.184067, 4.26567, 0, 10000022, "rp_bothan_male", "xovros_nurse", "default", "random", "rpg_shopkeeper") --Stimpack Vendor
	SceneObject(pNpc):setCustomObjectName("Qendil Var'rok (a Stimpack Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "medicine")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_medicine_novice")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4310.45, 10.3389, -5453.07, 154, 0, "rp_human_male", "sulon_station_guard", "default", "random") --Guard
	SceneObject(pNpc):setCustomObjectName("a Saltalo Station Militaman")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4308.65, 6, -5404.27, 0, 0, "rp_human_female", "sulon_station_guard", "default", "random") --Guard
	SceneObject(pNpc):setCustomObjectName("a Saltalo Station Militaman")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4390.58, 12.5128, -5383.25, 90, 0, "rp_human_male", "sulon_station_guard", "default", "random") --Guard
	SceneObject(pNpc):setCustomObjectName("a Saltalo Station Militaman")
	--pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4354.42, 6, -5384.53, 0, 0) --Shuttle Pilot
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4281.01, 6, -5413.56, 22, 0, "rp_human_male", "grave_tusken_s1", "default", "default") --Grave Tusken 1
	SceneObject(pNpc):setCustomObjectName("a Grave Tusken")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4280.1, 6, -5412.53, 55, 0, "rp_human_male", "grave_tusken_s2", "default", "default") --Grave Tusken 2
	SceneObject(pNpc):setCustomObjectName("a Grave Tusken")
	--pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4323.03, 6, -5408.46, 216, 0) --Dockmaster
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, -9.18971, 0.875003, -3.73559, 87, 10000047, "rp_sullustan_male", "sulon_bartender_aisai", "default", "sulon_bartender_aisai") --Bartender
	SceneObject(pNpc):setCustomObjectName("Aisai Yorvienov")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, -0.879453, 0.875, 1.43195, 226, 10000027, "rp_moncal_female", "sulon_barmaid_fish", "default", "sulon_barmaid_fish") --Barmaid
	SceneObject(pNpc):setCustomObjectName("Okala Kraoteer")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4219.48, 8.47314, -5319.69, 0, 0, "rp_sullustan_female", "sulon_station_guard", "default", "random") --Guard
	SceneObject(pNpc):setCustomObjectName("a Saltalo Station Militaman")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4203.86, 9.20122, -5319.23, 0, 0, "rp_human_male", "sulon_station_guard", "default", "random") --Guard
	SceneObject(pNpc):setCustomObjectName("a Saltalo Station Militaman")
	pNpc = 		 spawnRoleplayMobile("rp_sulon", "rp_base_npc", 1, 4187.8, 6, -5383.05, 226, 0, "rp_sullustan_male", "sulon_station_guard", "default", "random") --Guard
	SceneObject(pNpc):setCustomObjectName("a Saltalo Station Militaman")
end