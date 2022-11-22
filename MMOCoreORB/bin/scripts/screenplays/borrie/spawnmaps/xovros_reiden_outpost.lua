XovrosReidenOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "XovrosReidenOutpost",

	planet = "rp_xovros6",	
}

function XovrosReidenOutpostScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnPatrolMobiles()
		self:spawnStationaryMobiles()
		self:spawnSceneObjects()
	end
end

registerScreenPlay("XovrosReidenOutpostScreenPlay",  true)

function XovrosReidenOutpostScreenPlay:spawnSceneObjects() 

	--Travel Terminals
	spawnSceneObject("rp_xovros6", "object/tangible/terminal/terminal_travel_rp.iff", 12.2474, 0.639421, 50.1869, 610005032, 0.976296, 0, -0.21644, 0)
	spawnSceneObject("rp_xovros6", "object/tangible/terminal/terminal_travel_rp.iff", -0.199704, 0.639421, 48.063, 610005032, 1, 0, 0, 0)
	spawnSceneObject("rp_xovros6", "object/tangible/terminal/terminal_travel_rp.iff", -13.1979, 0.639421, 50.7079, 610005032, 0.953717, 0, 0.300706, 0)

	--Other Objects
	local sObj = spawnSceneObject("rp_xovros6", "object/tangible/swsovrp/prop/thm_sign_welcome_standing.iff", -5433.88, 28, -2833.86, 0, 0, 0, 1, 0) --Cantina Sign
	SceneObject(sObj):setCustomObjectName("Riverview Cantina")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/shop_sign_s02.iff", -5394.61, 27.9722, -2869.39, 0, 0, 0, 1, 0) --Cafe Signs
	SceneObject(sObj):setCustomObjectName("Thirsty Spacer Cafe")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/shop_sign_s04.iff", -5391.04, 31.5723, -2912.48, 0, 0.657841, 0.268696, 0.272487, 0.64869) --Fueling Station
	SceneObject(sObj):setCustomObjectName("Reiden Fueling Station")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/shop_sign_s01.iff", -5365.99, 28, -2935.01, 0, 0.894894, 0, 0.44628, 0) --Refugee Services
	SceneObject(sObj):setCustomObjectName("Refugee Services")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/shop_sign_s04.iff", -5331.24, 28, -2916.09, 0, 0.707107, 0, 0.707107, 0) --Communication Center
	SceneObject(sObj):setCustomObjectName("Reiden Comm Control")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/shop_sign_s03.iff", -5284.04, 28.5303, -2925.43, 0, 1, 0, 0, 0) --Dimok's Repair Shop
	SceneObject(sObj):setCustomObjectName("Dimok's One Stop Repair Shop")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/house_sign_consumable_object.iff", -5368.41, 32.7298, -2772.5, 0, 0.382683, 0, 0.92388, 0) --Tailor
	SceneObject(sObj):setCustomObjectName("Jrick's Tailoring")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/streetsign_upright_style_01.iff", -5370.44, 27.9995, -2737.59, 0, 1, 0, 0, 0) --Hotel Sign
	SceneObject(sObj):setCustomObjectName("Hydian Edge Hotel")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/all_sign_city_s02.iff", -5314.99, 28.5312, -2727.53, 0, 1, 0, 0, 0) --Shuttleport
	SceneObject(sObj):setCustomObjectName("Reiden Transportation Services")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/shop_sign_s04.iff", -5271.61, 30.4404, -2710.79, 0, 1, 0, 0, 0) --Security
	SceneObject(sObj):setCustomObjectName("a Reiden Outpost Security Officer HQ")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/shop_sign_s01.iff", -5205.87, 28, -2730.23, 0, 1, 0, 0, 0) --Outpost Depo
	SceneObject(sObj):setCustomObjectName("Reiden Outpost Stockpile")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/house_address.iff", -5211.9, 32.6512, -2748.42, 0, -0.382684, 0, 0.923879, 0) --Lab
	SceneObject(sObj):setCustomObjectName("Frontier Outpost Laboratory")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/swsovrp/prop2/thm_sign_medcenter.iff", -5431.58, 24.8594, -2873.49, 0, 1, 0, 0, 0) --Medic
	SceneObject(sObj):setCustomObjectName("Reiden Outpost Medical Center")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/swsovrp/prop2/thm_sign_bank.iff", -5400.63, 28, -2759.68, 0, 0.707107, 0, 0.707107, 0) --Bazaar
	SceneObject(sObj):setCustomObjectName("The Reiden Marketplace")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/shop_sign_s03.iff", -5667.9, 26.2498, -3136.53, 0, 0.92388, 0, 0.382683, 0) --Welcome Sign
	SceneObject(sObj):setCustomObjectName("-=- Welcome to Reiden Outpost -=-")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/sign/player/shop_sign_s02.iff", -5366.34, 28, -2904.34, 0, -0.382684, 0, 0.923879, 0) --Traffic Control
	SceneObject(sObj):setCustomObjectName("Traffic Control Tower")
	
	--TAILOR--
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/elegant/armoire_elegant_s01.iff", -1.98443, 0.346467, -7.59334, 610005117, 1, 0, 0, 0) --Shirts
	SceneObject(sObj):setCustomObjectName("Shirts")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_shirts")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/elegant/armoire_elegant_s01.iff", -3.23047, 0.346466, -7.59387, 610005117, 1, 0, 0, 0) --Pants
	SceneObject(sObj):setCustomObjectName("Pants")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_pants")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/elegant/armoire_elegant_s01.iff", -4.71973, 0.346466, -7.58118, 610005117, 1, 0, 0, 0) --Footwear
	SceneObject(sObj):setCustomObjectName("Footwear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_footwear")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/elegant/armoire_elegant_s01.iff", -6.22607, 0.346466, -7.5802, 610005117, 1, 0, 0, 0) --Jacket
	SceneObject(sObj):setCustomObjectName("Jacket")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_jackets")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/elegant/armoire_elegant_s01.iff", -7.6626, 0.346466, -7.57092, 610005117, 1, 0, 0, 0) --Vest
	SceneObject(sObj):setCustomObjectName("Vest")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_vests")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/elegant/armoire_elegant_s01.iff", -9.09619, 0.346466, -7.59583, 610005117, 1, 0, 0, 0) --Robes
	SceneObject(sObj):setCustomObjectName("Robes")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_robes")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/elegant/armoire_elegant_s01.iff", -10.5469, 0.346466, -7.61841, 610005117, 1, 0, 0, 0) --Bodysuits
	SceneObject(sObj):setCustomObjectName("Bodysuits")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_bodysuits")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/elegant/armoire_elegant_s01.iff", -12.0117, 0.346466, -7.62427, 610005117, 1, 0, 0, 0) --Skirts
	SceneObject(sObj):setCustomObjectName("Skirts")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_skirts")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/elegant/armoire_elegant_s01.iff", -13.502, 0.346466, -7.60059, 610005117, 1, 0, 0, 0) --Women
	SceneObject(sObj):setCustomObjectName("Women's Wear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_women")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/modern/chest_modern_style_01.iff", -2.20068, 2.80326, -7.94092, 610005117, 0.707107, 0.707106, 2.00972e-14, 5.3383e-15) --Heaad & Goggle
	SceneObject(sObj):setCustomObjectName("Headwear & Goggles")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_headwear")
	SceneObject(sObj):populateInventoryFromContentList("tailor_goggles")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/modern/chest_modern_style_01.iff", -4.83398, 2.80072, -7.94824, 610005117, 0.707108, 0.707106, -4.01943e-14, 1.27177e-14) --Handwear
	SceneObject(sObj):setCustomObjectName("Handwear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_handwear")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/modern/chest_modern_style_01.iff", -7.67188, 2.8002, -7.90381, 610005117, 0.707108, 0.707105, 0, -6.86911e-15) --Jewelry
	SceneObject(sObj):setCustomObjectName("Jewelry")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_jewelry")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/modern/chest_modern_style_01.iff", -10.46, 2.79952, -7.91065, 610005117, 0.707109, 0.707104, 8.03885e-14, -1.71728e-15) --Misc/Belts
	SceneObject(sObj):setCustomObjectName("Belts, Bandoliers & Aprons")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_misc")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/modern/chest_modern_style_01.iff", -13.1074, 2.80107, -7.91125, 610005117, 0.707109, 0.707104, 8.03885e-14, -1.71728e-15) --Bikinis
	SceneObject(sObj):setCustomObjectName("Bikinis")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_bikinis")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/modern/cabinet_modern_style_01.iff", -15.3198, 0.346466, -5.26123, 610005117, 0.707107, 0, 0.707106, 0) --Wookiee
	SceneObject(sObj):setCustomObjectName("Wookiee Wear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_wookiee")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/modern/cabinet_modern_style_01.iff", -15.3301, 0.346487, -2.41321, 610005117, 0.707107, 0, 0.707106, 0) --Ithorian 1
	SceneObject(sObj):setCustomObjectName("Ithorian Wear I")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_ithorian1")
	sObj = spawnSceneObject("rp_xovros6", "object/tangible/furniture/modern/cabinet_modern_style_01.iff", -15.2803, 0.346466, 0.441895, 610005117, 0.707107, 0, 0.707107, 0) --Ithorian 2
	SceneObject(sObj):setCustomObjectName("Ithorian Wear II")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_ithorian2")
end

function XovrosReidenOutpostScreenPlay:spawnMobiles()
	--local pNpc
	local pNpc = spawnRoleplayMobile("rp_xovros6", "rp_convo_npc", 1, -5358.87, 28, -2944.69, 201, 0, 			"21b_surgical_droid", "", "default", "", "rp_xov_meddroid_intro"					) --21b
	SceneObject(pNpc):setCustomObjectName("a 2-1B Surgical Droid")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5368.16, 28, -2940.58, 154, 0, 					"rp_human_female", "xovros_nurse", "default", "random" 								) --Outpost Nurse
	SceneObject(pNpc):setCustomObjectName("an Outpost Nurse")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5292.5, 28, -2937.95, 252, 0, 					"rp_rodian_male", "xovros_mechanic", "default", "xovros_rotto"						) --Rotto Mechanic
	SceneObject(pNpc):setCustomObjectName("Rotto Dimok")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5286.85, 28.5312, -2925.08, 200, 0,				"rp_wookiee_male", "xovros_wookiee_mechanic"," default", "xovros_wookiee_mechanic" 	) --Rotto Mech Assistant
	SceneObject(pNpc):setCustomObjectName("Filipacilocca")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5324.45, 27.4099, -2965.44, 180, 0,				"rp_human_male", "xovros_guard", "default", "random"								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5333.94, 28, -2912.55, 181, 0, 					"rp_human_male", "xovros_guard", "default", "random" 								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5368.23, 28, -2920.63, 36, 0, 					"rp_human_male", "xovros_guard", "default", "random" 								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5363.41, 28, -2915.62, 230, 0, 					"rp_human_female", "xovros_guard", "default", "random" 								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5672.27, 26.5699, -3141.44, 217, 0, 			"rp_human_female", "xovros_guard", "default", "random" 								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5363.28, 28, -2760.59, 311, 0, 					"rp_human_male", "xovros_guard", "default", "random" 								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5320.31, 28, -2647.7, 14, 0, 					"rp_human_male", "xovros_guard", "default", "random" 								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5250.37, 30.501, -2717.35, 0, 0, 				"rp_human_male", "xovros_guard", "default", "random" 								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5269.59, 30.501, -2717.24, 0, 0, 				"rp_human_female", "xovros_guard", "default", "random" 								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5231.94, 28, -2731.29, 69, 0, 					"rp_human_male", "xovros_guard", "default", "random" 								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5199.34, 31.1006, -2760.95, 160, 0, 			"rp_human_male", "xovros_guard", "default", "random"								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5222.96, 28, -2860.04, 90, 0, 					"rp_human_male", "xovros_guard", "default", "random"								) --Security Guard
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_convo_npc", 1, 1.44776, 0.346467, -1.62042, 269, 610005117, 	"rp_weequay_male", "xovros_tailor", "default", "xovros_tailor", "rp_xov_tailor"		) --Tailor
	SceneObject(pNpc):setCustomObjectName("Jrick")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_convo_npc", 1, -5397.87, 28, -2764.32, 126, 0, 				"rp_nikto_male", "xovros_ranged_vendor", "default", "random", "rpg_shopkeeper"		) --Ranged Weapon Vendor
	SceneObject(pNpc):setCustomObjectName("Nilok (a Ranged Weapons Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "novice_ranged")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_weapons_ranged_novice")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_convo_npc", 1, -5392.04, 28, -2762.84, 182, 0, 					"rp_human_female", "xovros_vendor_melee", "default", "random", "rpg_shopkeeper"	) --Melee Weapon Vendor
	SceneObject(pNpc):setCustomObjectName("Kara Il (a Melee Weapons Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "novice_melee")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_weapons_melee_novice")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5386.04, 32.2832, -2861.6, 274, 0, 				"3po_protocol_droid_red","", "default", ""											) --Cafe Maitre D
	SceneObject(pNpc):setCustomObjectName("Cafe Serving Droid")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -1.32636, 0.184067, 0.796921, 124, 610005266, 	"rp_moncal_male", "outpost_doctor",	 "default",	"xovros_cakane"						) --The Doctor
	SceneObject(pNpc):setCustomObjectName("Hadkor Cakane")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 8.62285, -0.894992, 0.447493, 89, 610005048,		"rp_ishi_tib_male",	"xovros_bartender", "default","xovros_bartender"				) --The Bartender
	SceneObject(pNpc):setCustomObjectName("Satoe Winnslon")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 12.2726, 1.13306, 2.16329, 0, 610005108, 		"rp_human_male", "xovros_guard_captain", "default","xovros_tremove"					) --The Sheriff
	SceneObject(pNpc):setCustomObjectName("Tremove Lycrest")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 0.0510276, 1.13306, -3.98945, 0, 610005107, 		"rp_human_female", "xovros_guard", "default","random"								) --Security Officer
	SceneObject(pNpc):setCustomObjectName("a Reiden Outpost Security Officer")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 17.0403, 2.00076, -6.2536, 0, 610005066, 		"rp_twilek_female", "xovros_admin_gown", "default","xovros_draticce"				) --The Admin
	SceneObject(pNpc):setCustomObjectName("Draticce Larmand")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 9.57341, 2, 1.76171, 273, 610005064,				"rp_trandoshan_female", "xovros_ghaddle", "default","xovros_ghaddle"				) --Ghaddle
	SceneObject(pNpc):setCustomObjectName("Ghaddle")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5301.79, 28, -2722.79, 41, 0, 					"rp_human_male", "xovros_pilot", "default",	"random"								) --Shuttle Pilot
	SceneObject(pNpc):setCustomObjectName("Karn Lokborne")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5313.25, 28.5312, -2728.23, 52, 0, 				"rp_human_male", "xovros_senior_mechanic", "default", "random" 						) --Old Mechanic
	SceneObject(pNpc):setCustomObjectName("Jedezrik Lokborne")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -21.8925, 1.59773, 10.3846, 126, 610005096, 		"rp_twilek_female",	"xovros_hotel_receptionist", "default",	"random" 				) --Hotel Receptionist
	SceneObject(pNpc):setCustomObjectName("Junni Hopenwei")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 20.4282, 1.56616, 12.2854, 180, 610005095, 		"rp_twilek_female", "xovros_hotel_owner", "default", "random" 						) --Hotel Owner
	SceneObject(pNpc):setCustomObjectName("O'haryn If'ik")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5287.21, 28, -2652.43, 267, 0, 					"super_battle_droid", "", "default", ""												) --Admin House Security Droid
	SceneObject(pNpc):setCustomObjectName("Larmand Estate Security Droid")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5292.02, 28, -2938.85, 299, 0, 					"r5", "", "default", ""																) --Mech Astromech
	SceneObject(pNpc):setCustomObjectName("R5-L2")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5403.99, 28, -2775.02, 141, 0, 					"rp_human_female",	"xovros_vendor_generic1", "default", "random" 					) --Generic Vendor
	SceneObject(pNpc):setCustomObjectName("a Market Vendor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5397.62, 28, -2770.08, 39, 0, 					"rp_rodian_female","xovros_vendor_generic2", "default",	"random" 					) --Generic Vendor
	SceneObject(pNpc):setCustomObjectName("a Market Vendor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5391.64, 28, -2774.72, 278, 0, 					"rp_gran_male", "xovros_vendor", "default",	"random" 								) --Generic Vendor
	SceneObject(pNpc):setCustomObjectName("a Market Vendor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 4.95953, 2.00003, 13.0502, 180, 610005064, 		"3po_protocol_droid_silver", "", "default", ""										) --City Protocol Droid
	SceneObject(pNpc):setCustomObjectName("Q-3PK")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5220.87, 28, -2796.92, 87, 0, 					"cll8_binary_load_lifter", "", "default", ""										) --Binary Load Lifter
	SceneObject(pNpc):setCustomObjectName("a CLL-8 Binary Load Lifter")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5345.98, 28, -2915.59, 136, 0, 					"cll8_binary_load_lifter", "", "default", ""										) --Binary Load Lifter
	SceneObject(pNpc):setCustomObjectName("a CLL-8 Binary Load Lifter")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5376.11, 28, -2922.05, 227, 0, 					"r4", "", "default", ""																) --City Maintenance Astromech
	SceneObject(pNpc):setCustomObjectName("R4-P1")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 6.98533, -5.5, -6.38725, 89, 610005281, 			"r2", "", "default", ""																) --City Maintenance Astromech
	SceneObject(pNpc):setCustomObjectName("R2-S1")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5340.68, 28, -2944.01, 338, 0, 					"rp_human_male", "xovros_refugee_male1", "default",	"random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5345.05, 28, -2942.02, 63, 0, 					"rp_human_female","xovros_vendor_generic2", "default", "random" 					) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5337.42, 27.9447, -2955.37, 343, 0,				"rp_moncal_male", "xovros_refugee_male2", "default", "random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5339.31, 27.9425, -2954.93, 71, 0, 				"rp_rodian_male", "xovros_refugee_male3", "default", "random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5336.97, 27.9963, -2952.82, 207, 0, 			"rp_bothan_female","xovros_refugee_male7", "default", "random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5348.08, 27.9372, -2952.61, 27, 0, 				"rp_trandoshan_male", "xovros_refugee_male4", "default", "random" 					) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5346.98, 27.9996, -2949.45, 198, 0, 			"rp_twilek_male", "xovros_refugee_male5", "default", "random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5348.76, 28, -2943.02, 261, 0, 					"rp_sullustan_female", "xovros_refugee_male2", "default", "random" 					) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5337.25, 28, -2936.06, 190, 0, 					"rp_human_male", "xovros_refugee_male10", "default", "random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5351.9, 27.9252, -2951.74, 130, 0, 				"rp_rodian_male", "xovros_refugee_male6", "default", "random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5350.98, 27.9065, -2952.57, 314, 0, 			"rp_twilek_male", "xovros_refugee_male2", "default", "random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5369.85, 28, -2927.76, 0, 0, 					"rp_twilek_male", "xovros_refugee_male7", "default", "random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5368.68, 28, -2929.79, 175, 0, 					"rp_human_male", "xovros_refugee_male8", "default",	 "random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5353.54, 28, -2936.56, 116, 0, 					"rp_human_male", "xovros_refugee_male9", "default",	"random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5338.71, 28, -2908.99, 168, 0, 					"rp_nikto_male", "xovros_refugee_male10", "default","random" 						) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5339.63, 28, -2911.57, 53, 0, 					"rp_talz_male", "", "default","random" 												) --Refugee
	SceneObject(pNpc):setCustomObjectName("a Crash Survivor")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -5202.94, 31.1006, -2752.42, 0, 0, 				"rp_moncal_male", "xovros_moncal_scientist", "default","xovros_moncal_scientist" 	) --Scientist
	SceneObject(pNpc):setCustomObjectName("Niso Fobacky")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 0.0603013, 0.125265, -5.68752, 0, 610005320, 	"rp_sullustan_male", "xovros_senior_engineer", "default","random" 					) --Lead Engineer
	SceneObject(pNpc):setCustomObjectName("Dieyko Ciecee")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, 4.64439, -0.894992, -4.768, 0, 610005048, 		"ra7_bug_droid", "", "default", ""													) --Bartender Droid
	SceneObject(pNpc):setCustomObjectName("a Bar Droid")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_base_npc", 1, -4.65298, -0.894997, 20.7546, 198, 610005054, 	"rp_hutt_male", "", "default", "random"												) --Hutt Friend
	SceneObject(pNpc):setCustomObjectName("Binoro the Hutt")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_convo_npc", 1, -5399.24, 28, -2774.49, 211, 0, 				"rp_human_male", "xovros_vendor_camping", "default", "random", "rpg_shopkeeper"		) --Camp Vendor
	SceneObject(pNpc):setCustomObjectName("Cimelf Li (a Camping Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "camping")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_camping")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_convo_npc", 1, 1.13103, 0.184067, 5.99018, 78, 610005266,		"rp_zabrak_female", "xovros_nurse", "default", "random", "rpg_shopkeeper"			) --Stimpack Vendor
	SceneObject(pNpc):setCustomObjectName("Orla Stradnel (a Medical Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "medicine")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_medicine_novice")
	pNpc = spawnRoleplayMobile("rp_xovros6", "rp_convo_npc", 1, -5391.28, 28, -2770.35, 52, 0, "rp_bothan_male", "xovros_vendor_instrument", "default", "random", "rpg_shopkeeper"					) --Instrument Vendor
	SceneObject(pNpc):setCustomObjectName("Lesjku Nirn'dor (an Instrument Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "music")
    SceneObject(pNpc):setStoredString("vendor:shopList", "shop_instruments")
end