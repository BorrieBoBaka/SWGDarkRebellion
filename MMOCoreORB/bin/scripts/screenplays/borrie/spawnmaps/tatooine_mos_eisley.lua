local Logger = require("utils.logger")

RpTatooineMosEisleyScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "RpTatooineMosEisleyScreenPlay",

	planet = "rp_tatooine",	
	
	walkpointList = {
		market_shopper1 = {
			{745.296, 0, 281.54, 180, 0,false, "none"},
			{748.047, 0, 279.843, 98, 0,true, "shop"},
			{750.615, 0, 267.862, 137, 0,true, "shop"},
			{743.498, 0, 254.154, 200, 0,false, "none"},
			{737.639, 0, 229.698, 214, 0,false, "none"},
			{719.56, 0, 223.706, 250, 0,false, "none"},
			{716.976, 0, 217.721, 177, 0,true, "shop"},
			{714.527, 0, 223.021, 336, 0,false, "none"},
			{678.21, 0, 226.482, 275, 0,false, "none"},
			{668.156, 0, 248.694, 339, 0,true, "shop"},
			{674.656, 0, 252.419, 68, 0,true, "shop"},
			{672.488, 0, 259.678, 263, 0,true, "shop"},
			{671.774, 0, 284.275, 354, 0,false, "none"},
			{680.253, -0.25, 301.799, 34, 0,false, "none"},
			{722.902, -0.25, 323.929, 40, 0,false, "none"},
			{781.809, -0.25, 314.541, 95, 0,false, "none"},
			{805.175, -0.25, 303.873, 146, 0,false, "none"},
			{767.391, -0.25, 302.339, 261, 0,false, "none"},
			{749.95, 0, 286.123, 206, 0,false, "none"},
		},
	}
}

registerScreenPlay("RpTatooineMosEisleyScreenPlay",  true)

function RpTatooineMosEisleyScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnSceneObjects()
		self:spawnCivilians()
	end
end

function RpTatooineMosEisleyScreenPlay:spawnCivilians() 
	local waypointList = {
		--{741.764, 0, 291.229, 178, 0,{"walker_market_shopper1"},"r5"},
		{786.172, 0, 191.22, 228, 0,{"none"}},
		{929.494, 0.25, 148.493, 354, 0,{"sit"}},
		{1072.39, 0, 96.3649, 217, 0,{"sit"}},
		{1073.37, 0, 95.1716, 195, 0,{"sit"}},
		{921.788, 0, 173.653, 27, 0,{"social"}},
		{922.682, 0, 175.192, 205, 0,{"social"}},
		{892.727, 0, 199.93, 185, 0,{"social"}},
		{892.562, 0, 198.817, 6, 0,{"social"}},
		{893.555, 0.3, 199.091, 286, 0,{"social"}},
		{805.95, 0.3, 291.058, 3, 0,{"social"}},
		{805.992, 0.3, 292.391, 165, 0,{"social"}},
		{751.481, 0, 281.623, 89, 0,{"none"}},
		{742.071, 0, 270.258, 88, 0,{"none"}},
		{742.026, 0, 272.175, 88, 0,{"none"}},
		{741.942, 0, 273.423, 136, 0,{"social"}},
		{739.242, 0, 259.498, 86, 0,{"sit"}},
		{724.965, 0.522461, 289.462, 358, 0,{"sit"}},
		{725.895, 0.522461, 289.532, 1, 0,{"sit"}},
		{724.781, 0, 291.552, 157, 0,{"social"}},
		{718.102, 0, 348.145, 165, 0,{"none"}},
		{749.026, 0.3, 326.98, 240, 0,{"none"}},
		{679.187, 0.3, 317.971, 217, 0,{"social"}},
		{677.535, 0.3, 317.538, 77, 0,{"social"}},
		{678.836, 0.3, 316.45, 359, 0,{"social"}},
		{675.268, 0, 278.179, 231, 0,{"social"}},
		{673.875, 0, 277.167, 55, 0,{"social"}},
		{664.717, 0, 261.239, 88, 0,{"none"}},
		{675.005, 0, 252.951, 91, 0,{"none"}},
		{719.536, 0, 228.904, 351, 0,{"none"}},
		{713.048, 0, 228.529, 174, 0,{"none"}},
		{724.63, 0, 228.469, 270, 0,{"none"}},
		{722.356, 0, 228.943, 106, 0,{"social"}},
		{725.584, 0, 228.344, 268, 0,{"none"}},
		{724.628, 0, 227.484, 301, 0,{"social"}},
		{714.922, 0, 218.042, 55, 0,{"social"}},
		{715.789, 0, 218.362, 245, 0,{"social"}},
		{757.266, 0, 241.415, 225, 0,{"none"}},
		{739.189, 0, 265.731, 54, 0,{"social"}},
		{752.516, 0, 269.75, 302, 0,{"none"}},
		{755.673, 1.75, 226.694, 339, 0,{"none"}},
		{723.479, 0, 213.459, 14, 0,{"drinker"}},
		{723.397, 0, 215.405, 163, 0,{"sittable"}},
		{724.626, 0, 214.939, 242, 0,{"sittable"}},
		{729.448, 0, 225.639, 227, 0,{"sittable"}},
		{728.656, 0, 223.951, 354, 0,{"sittable"}},
		{727.89, 0, 225.425, 120, 0,{"sitchair"}},
		{737.008, 0, 222.249, 5, 0,{"sitchair"}},
		{737.8, 0, 223.748, 229, 0,{"sittable"}},
		{708.302, 0, 207.688, 355, 0,{"none"}},
		{746.231, 0, 241.039, 297, 0,{"social"}},
		{745.039, 0, 241.71, 119, 0,{"social"}},
		{745.032, 0, 240.551, 32, 0,{"social"}},
		{697.495, 0, 218.887, 104, 0,{"tech"}},
		{717.806, 0, 217.545, 177, 0,{"tech"}},
		{668.046, 0, 253.509, 352, 0,{"tech"}},
		{667.53, 0, 251.602, 171, 0,{"tech"}},
		{674.679, 0, 266.277, 87, 0,{"tech"}},
		{674.679, 0, 267.269, 138, 0,{"social"}},
		{675.058, 0, 270.617, 212, 0,{"none"}},
		{666.498, 0, 278.22, 48, 0,{"none"}},
		{642.954, 0, 266.029, 144, 0,{"social"}},
		{643.414, 0.3, 249.464, 74, 0,{"sit"}},
		{645.47, 0, 249.327, 272, 0,{"social"}},
		{620.521, 0, 171.679, 309, 0,{"tech"}},
		{707.9, 0, 155.738, 110, 0,{"social"}},
		{708.99, 0, 155.461, 283, 0,{"social"}},
		{709.116, 0, 153.595, 13, 0,{"none"}},
		{740.055, 0.3, 187.055, 215, 0,{"none"}},
		{738.654, 0.3, 186.755, 172, 0,{"none"}},
		{798.385, 0.3, 214.082, 131, 0,{"none"}},
		{797.91, 0.3, 213.369, 98, 0,{"sit"}},
		{791.077, 0, 233.163, 221, 0,{"social"}},
		{790.613, 0, 234.292, 185, 0,{"social"}},
		{756.74, 0, 266.397, 129, 0,{"sit"}},
		{706.943, 0, 318.454, 17, 0,{"social"}},
		{708.355, 0, 318.427, 319, 0,{"social"}},
		{707.549, 0, 321.413, 180, 0,{"social"}},
		{708.638, 0, 320.8, 207, 0,{"social"}},
		{706.522, 0, 320.651, 132, 0,{"social"}},
		{691.984, 0, 334.331, 271, 0,{"tech"}},
		{703.42, 0.3, 364.449, 258, 0,{"sit"}},
		{703.246, 0.3, 363.591, 269, 0,{"none"}},
		{677.848, 0, 406.372, 27, 0,{"social"}},
		{678.752, 0, 407.776, 211, 0,{"social"}},
		{677.494, 0, 407.759, 128, 0,{"none"}},
		{627.598, 0, 279.392, 262, 0,{"tech"}},
		{568.913, 0, 268.028, 214, 0,{"none"}},
		{572.985, -0.25, 335.949, 5, 0,{"tech"}},
		{561.588, -0.25, 339.759, 308, 0,{"none"}},
		{560.286, 0, 328.081, 114, 0,{"social"}},
		{561.61, 0, 327.218, 301, 0,{"social"}},
		{562.426, 0, 326.146, 280, 0,{"none"}},
		{558.254, 0, 381.735, 20, 0,{"none"}},
		{482.775, 0, 316.705, 105, 0,{"sit"}},
		{484.124, 0, 317.876, 180, 0,{"sit"}},
		{541.946, 0, 257.874, 341, 0,{"sit"}},
		{542.677, 0, 258.355, 46, 0,{"sit"}},
		{607.642, 0, 261.086, 100, 0,{"tech"}},
		{672.143, 0, 236.672, 166, 0,{"social"}},
		{672.491, 0, 235.194, 347, 0,{"social"}},
		{651.276, 0, 153.399, 247, 0,{"social"}},
		{602.694, 0, 122.505, 328, 0,{"sit"}},
		{550.47, 0, 101.06, 258, 0,{"none"}},
		{551.124, 0, 102.099, 224, 0,{"social"}},
		{625.01, 0, 90.2157, 144, 0,{"social"}},
		{625.934, 0, 88.2798, 333, 0,{"social"}},
		{662.413, 0, 66.8027, 163, 0,{"social"}},
		{663.91, 0, 65.8513, 231, 0,{"social"}},
		{663.263, 0, 64.021, 347, 0,{"social"}},
		{661.932, 0, 64.1215, 34, 0,{"social"}},
		{661.177, 0, 64.992, 59, 0,{"none"}},
		{671.598, 0, 39.3487, 267, 0,{"none"}},
		{651.032, 0, -25.0738, 81, 0,{"none"}},
		{597.514, 0, -97.4577, 73, 0,{"sit"}},
		{600.743, 0, -123.147, 164, 0,{"none"}},
		{611.772, 0.3, -113.596, 4, 0,{"social"}},
		{611.856, 0.3, -112.139, 185, 0,{"social"}},
		{626.531, 0, -53.5361, 82, 0,{"social"}},
		{627.55, 0, -53.3455, 258, 0,{"none"}},
		{721.082, 0, 129.822, 155, 0,{"social"}},
		{722.809, 0, 128.849, 289, 0,{"none"}},
		{721.816, 0, 127.377, 235, 0,{"none"}},
		{721.043, 0, 127.031, 1, 0,{"none"}},
		{720.314, 0, 127.896, 18, 0,{"none"}},
		{721.495, 0, 126.124, 6, 0,{"social"}},
		{741.691, 0, 105.099, 313, 0,{"social"}},
		{740.959, 0, 107.312, 159, 0,{"none"}},
		{739.943, 0, 106.654, 127, 0,{"none"}},
		{739.561, 0, 104.697, 74, 0,{"none"}},
		{703.774, 0, 117.016, 183, 0,{"social"}},
		{704.577, 0, 117.853, 195, 0,{"none"}},
		{719.191, 0.196289, 93.4542, 200, 0,{"social"}},
		{718.592, 0.195312, 92.0889, 24, 0,{"social"}},
		{707.369, 0.196289, 91.9237, 166, 0,{"social"}},
		{707.976, 0.195312, 90.4882, 166, 0,{"none"}},
		{706.711, 0.196289, 90.2159, 161, 0,{"none"}},
		{722.699, 0.298828, 79.3969, 267, 0,{"sit"}},
		{722.861, 0.299805, 80.1909, 273, 0,{"sit"}},
		{706.546, 1.18457, 97.7243, 1, 0,{"sit"}},
		{836.487, 0.3, 125.776, 178, 0,{"none"}},
		{839.13, 0, 57.5282, 52, 0,{"none"}},
		{840.51, 0, 58.6733, 227, 0,{"social"}},
		{840.499, 0, 60.4585, 151, 0,{"sit"}},
		{811.989, 0, 2.82504, 80, 0,{"sit"}},
		{833.927, 0, -40.1135, 84, 0,{"social"}},
		{835.759, 0, -38.8064, 234, 0,{"none"}},
		{836.13, 0, -39.8591, 336, 0,{"none"}},
		{836.251, 0, -40.7182, 277, 0,{"none"}},
		{835.901, 0, -41.5499, 305, 0,{"none"}},
		{884.433, 0.3, -34.2018, 357, 0,{"tech"}},
		{839.175, 0, -84.9149, 237, 0,{"social"}},
		{836.847, 0, -84.3929, 127, 0,{"social"}},
		{837.28, 0, -86.0191, 33, 0,{"social"}},
		{801.856, 0, -162.294, 167, 0,{"none"}},
		{888.791, 0, -130.576, 56, 0,{"sit"}},
		{886.037, 0, -126.448, 263, 0,{"social"}},
		{883.953, 0, -126.612, 85, 0,{"none"}},
		{1180.85, 0, -143.737, 64, 0,{"none"}},
		{1182.4, 0, -143.173, 248, 0,{"social"}},
		{1209.68, 0, -98.5152, 75, 0,{"tech"}},
		{1239.81, 0, -23.2985, 125, 0,{"none"}},
		{1264.9, 0, 67.3898, 337, 0,{"none"}},
		{1247.94, 1.26172, 80.3312, 95, 0,{"sit"}},
		{1262.84, 0, 153.847, 264, 0,{"tech"}},
		{1263.91, 0, 160.077, 57, 0,{"social"}},
		{1265.38, 0, 160.76, 204, 0,{"social"}},
		{1350.56, 0, 315.338, 270, 0,{"tech"}},
		{1274.49, 0, 334.72, 83, 0,{"tech"}},
		{1260.49, 0, 341.791, 126, 0,{"none"}},
		{1275.54, 0, 359.252, 265, 0,{"sit"}},
		{1260.14, 0, 386.691, 267, 0,{"social"}},
		{1258.55, 0, 386.612, 275, 0,{"social"}},
		{1257.19, 0.3, 387.387, 107, 0,{"none"}},
		{1165.72, 0, 303.442, 27, 0,{"none"}},
		{1176.11, 0, 269.845, 194, 0,{"social"}},
		{1177.08, 0, 267.867, 277, 0,{"social"}},
		{1175.73, 0, 266.4, 6, 0,{"social"}},
		{1173.7, 0, 267.105, 328, 0,{"social"}},
		{1172.5, 0, 268.543, 134, 0,{"social"}},
		{1173.57, 0, 269.431, 127, 0,{"none"}},
		{1154.53, 0, 282.748, 157, 0,{"sit"}},
		{962.998, -0.25, 258.673, 264, 0,{"social"}},
		{960.628, -0.25, 258.947, 93, 0,{"social"}},
		{947.854, 0, 281.11, 74, 0,{"social"}},
		{934.5, 0, 309.433, 45, 0,{"social"}},
		{1061.17, 0, 293.086, 269, 0,{"sit"}},
		{1048.27, 0, 302.524, 0, 0,{"social"}},
		{1048.37, 0, 304.187, 182, 0,{"social"}},
		{1056.65, 0, 332.537, 15, 0,{"social"}},
		{1057.44, 0, 335.306, 195, 0,{"social"}},
		{1055.3, 0, 335.214, 125, 0,{"social"}},
		{1059.14, 0, 334.401, 274, 0,{"none"}},
		{1057.64, 0.3, 348.065, 244, 0,{"drinker"}},
		{1032.49, 0, 360.279, 132, 0,{"sit"}},
		{1032, 0, 358.878, 56, 0,{"sit"}},
		{1026.62, 0, 388.682, 336, 0,{"none"}},
		{1027.29, 0, 389.496, 303, 0,{"none"}},
		{1025.83, 0, 390.509, 142, 0,{"social"}},
		{1002.87, 0, 401.487, 159, 0,{"sit"}},
		{1005.05, 0, 400.987, 244, 0,{"sit"}},
		{991.07, 0, 387.596, 37, 0,{"none"}},
		{979.378, 0, 411.264, 23, 0,{"tech"}},
		{966.834, 0, 417.337, 245, 0,{"none"}},
		{991.721, 0, 468.609, 318, 0,{"social"}},
		{989.953, 0, 470.254, 133, 0,{"social"}},
		{991.392, 0, 470.931, 197, 0,{"social"}},
		{990.011, 0, 468.345, 24, 0,{"none"}},
		{1046.53, 0, 484.971, 70, 0,{"sit"}},
		{1101.26, 0, 451.359, 193, 0,{"tech"}},
		{955.99, 0, 136.845, 24, 0,{"sit"}},
		{955.136, 0, 137.303, 28, 0,{"sit"}},
		{954.477, 0, 138.274, 76, 0,{"sit"}},
		{984.865, 0, 150.574, 158, 0,{"none"}},
		{1006.76, 0, 124.185, 258, 0,{"none"}},
		{1051.87, 0, 103.055, 232, 0,{"tech"}},
		{1048.95, 0, 75.8958, 308, 0,{"social"}},
		{1048.15, 0, 77.0469, 143, 0,{"social"}},
		{1049.51, 0, 77.4266, 229, 0,{"social"}},
		{1049.09, 0, 56.2886, 60, 0,{"none"}},
		{1066.36, 0, 52.6018, 15, 0,{"none"}},
		{1043.06, 0, 99.505, 242, 0,{"sit"}},
		{1040.01, 0, 31.6045, 10, 0,{"social"}},
		{1040.38, 0, 33.4872, 48, 0,{"social"}},
		{1041.75, 0, 34.4092, 226, 0,{"none"}},
		{1055.5, 0, 11.8196, 235, 0,{"none"}},
		{867.175, 0.3, 152.387, 346, 0,{"none"}},
		{867.135, 0.3, 153.789, 178, 0,{"social"}},
		{814.486, 0.3, -60.5094, 245, 0,{"social"}},
		{812.775, 0.3, -60.9226, 222, 0,{"social"}},
		{810.909, 0.3, -62.3073, 55, 0,{"social"}},
		{775.702, 0, -41.4262, 21, 0,{"tech"}},
		{832.658, 0, 16.1025, 313, 0,{"none"}},
		{484.084, 1.74805, 145.819, 216, 0,{"sit"}},
		{459.815, 0, 180.587, 311, 0,{"tech"}},
		{504.362, 0, 257.912, 292, 0,{"social"}},
		{502.612, 0, 258.701, 113, 0,{"social"}},
		{502.745, 0, 256.812, 31, 0,{"social"}},
		{517.93, 0, 345.475, 96, 0,{"none"}},
		{527.154, 0, 367.227, 138, 0,{"sit"}},
		{20.6076, -0.894993, 4.10171, 72, 610008176,{"sittable"}},
		{21.3166, -0.894993, 5.58439, 158, 610008176,{"sittable"}},
		{23.2705, -0.894994, 4.7568, 252, 610008176,{"sittable"}},
		{16.5245, -0.894992, -3.1439, 232, 610008176,{"sittable"}},
		{14.2375, -0.894992, -4.84698, 51, 610008176,{"sittable"}},
		{14.6531, -0.894992, -2.90315, 135, 610008176,{"sittable"}},
		{16.4756, -0.894992, -4.70127, 319, 610008176,{"sittable"}},
		{20.9083, -0.894992, 14.5177, 358, 610008178,{"sitchair"}},
		{22.5637, -0.894992, 16.6839, 260, 610008178,{"sitchair"}},
		{22.5203, -0.894992, 15.7884, 210, 610008178,{"sitchair"}},
		{4.5341, -0.894992, 17.3468, 294, 610008180,{"sitchair"}},
		{4.58264, -0.894992, 16.0487, 271, 610008180,{"sitchair"}},
		{2.90691, -0.894992, 14.2652, 358, 610008180,{"sittable"}},
		{0.85307, -0.894992, 16.0249, 90, 610008180,{"sittable"}},
		{9.70056, -0.894992, 18.1067, 345, 610008180,{"sittable"}},
		{10.2159, -0.894992, 21.5839, 218, 610008180,{"sittable"}},
		{7.54703, -0.894992, 21.2395, 145, 610008180,{"sittable"}},
		{7.1906, -0.894992, 18.7056, 46, 610008180,{"sittable"}},
		{-1.80855, -0.894993, 23.3928, 236, 610008182,{"sittable"}},
		{-1.96477, -0.894992, 20.9954, 311, 610008182,{"sittable"}},
		{22.1272, -0.894996, -19.5368, 76, 610008177,{"sittable"}},
		{24.1595, -0.894996, -20.9097, 0, 610008177,{"sittable"}},
		{25.9509, -0.894997, -19.1203, 269, 610008177,{"sittable"}},
		{22.7923, -0.894997, -17.47, 143, 610008177,{"sittable"}},
		{25.8962, -0.894998, -14.2154, 236, 610008177,{"sittable"}},
		{22.6596, -0.894997, -14.2299, 121, 610008177,{"sittable"}},
		{-13.1713, -0.894987, -20.1323, 22, 610008181,{"sittable"}},
		{-13.4973, -0.894867, -17.2896, 137, 610008181,{"sittable"}},
		{-10.8699, -0.894851, -17.1567, 231, 610008181,{"sittable"}},
		{48.5378, 0.105, -0.69122, 270, 610008174,{"sitchair"}},
		{48.4792, 0.105, 1.52004, 266, 610008174,{"sitchair"}},
		{40.0597, 0.105, -8.96283, 258, 610008174,{"social"}},
		{39.0159, 0.105, -9.08933, 81, 610008174,{"social"}},
		{16.8917, -0.894992, -3.9489, 271, 610008176,{"drinker"}},
		{3.23204, -0.894992, -7.78685, 161, 610008176,{"drinker"}},
		{-5.09885, -0.894992, -4.768, 356, 610008176,{"drinker"}},
		{-3.11131, -0.894992, -4.768, 359, 610008176,{"drinker"}},
		{-11.672, -0.894832, -16.3562, 202, 610008181,{"drinker"}},
		{2.45914, -0.894992, -4.85529, 0, 610008176,{"drinker"}},
		{3.37055, -0.894992, -4.9639, 327, 610008176,{"drinker"}},
		{-8.04936, -0.894992, 5.66256, 127, 610008176,{"drinker"}},
		{-4.34492, -0.894992, 5.66256, 171, 610008176,{"drinker"}},
		{-3.39098, -0.894992, 5.66256, 216, 610008176,{"drinker"}},
		{0.0793189, -0.894992, 5.66256, 88, 610008176,{"drinker"}},
		{0.878321, -0.894992, 5.72649, 264, 610008176,{"none"}},
		{-6.78098, -0.894992, 5.66256, 193, 610008176,{"none"}},
		{-6.1922, -0.894992, -4.768, 0, 610008176,{"none"}},
		{-11.3708, -0.894992, -4.768, 81, 610008176,{"social"}},
		{-10.2237, -0.894992, -4.768, 267, 610008176,{"social"}},
		{26.7844, -0.894996, -3.57261, 307, 610008176,{"social"}},
		{25.7092, -0.894995, -2.51107, 133, 610008176,{"drinker"}},
		{-13.9921, -0.895002, -10.3276, 114, 610008176,{"none"}},
		{-33.141, 0.10501, -9.68907, 230, 610008187,{"social"}},
		{-34.1469, 0.10501, -10.6025, 47, 610008187,{"social"}},
		{-41.7863, 0.105009, -25.6413, 155, 610008188,{"tech"}},
		{39.8954, 0.104999, 2.74058, 1, 610008174,{"tech"}},
		{556.528, -0.25, 244.027, 329, 0,{"tech"}},
		{525.185, -0.25, 225.733, 269, 0,{"tech"}},
		{535.042, -0.25, 237.258, 64, 0,{"social"}},
		{536.519, -0.25, 238.006, 349, 0,{"social"}},
		{567.283, 0, 193.427, 285, 0,{"sit"}},

	}
	
	CivillianGenerator:spawnCivillians(self.screenplayName, "rp_tatooine", waypointList, self.walkpointList, "tatooine", "tatooine")
end

function RpTatooineMosEisleyScreenPlay:spawnSceneObjects() 
	--Travel Terminals
	spawnSceneObject("rp_tatooine", "object/tangible/terminal/terminal_travel_rp.iff", -13.0021, 0.639421, 51.1865, 610008050, 1, 0, 0.332372, 0)
	spawnSceneObject("rp_tatooine", "object/tangible/terminal/terminal_travel_rp.iff", -2.7419, 0.639421, 48.1677, 610008050, 1, 0, 0, 0)
	spawnSceneObject("rp_tatooine", "object/tangible/terminal/terminal_travel_rp.iff", 2.54505, 0.639421, 48.1693, 610008050, 1, 0, 0, 0)
	spawnSceneObject("rp_tatooine", "object/tangible/terminal/terminal_travel_rp.iff", 12.6536, 0.639421, 51.1838, 610008050, 0.909306, 0, -0.416129, 0)
	
	--Signs
	local sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/all_sign_city_s03.iff", 947.255, 0, 139.882, 0, 0.97237, 0, 0.233445, 0) --Tailor Sign
	SceneObject(sObj):setCustomObjectName("Eisley Tailoring")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/all_sign_city_s01.iff", 590.485, 0, 263.569, 0, 1, 0, 0, 0) --Junkshop
	SceneObject(sObj):setCustomObjectName("West Eisley Junkyard")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/streetsign_upright_style_01.iff", 612.531, 0, 357.16, 0, 1, 0, 0, 0) --Ship Shop
	SceneObject(sObj):setCustomObjectName("Antion's Ship Dealer")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/streetsign_upright_style_01.iff", 728.115, 0, 338.132, 0, 0.92388, 0, 0.382683, 0) --Speciality Shop
	SceneObject(sObj):setCustomObjectName("Main Street Specialty Shop")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/all_sign_city_s03.iff", 766.92, 2.0752, 276.406, 0, 0.707107, 0, 0.707107, 0) --Security HQ
	SceneObject(sObj):setCustomObjectName("Mos Eisley Police Station")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/streetsign_wall_style_01.iff", 1030.25, 6.2793, 245.364, 0, 0.707107, 0, 0.707107, 0) --Club
	SceneObject(sObj):setCustomObjectName("Twinsiren Club")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/streetsign_upright_style_01.iff", 606.332, 0, -83.3598, 0, 0.707107, 0, 0.707107, 0) --Lodge
	SceneObject(sObj):setCustomObjectName("Dunewalker Lodge")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/streetsign_upright_style_01.iff", 450.508, 1.99023, 157.077, 0, 1, 0, 0, 0) --Clinic
	SceneObject(sObj):setCustomObjectName("Mos Eisley Medical Clinic")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/all_sign_city_s02.iff", 830.15, 0, -36.813, 0, 0.707107, 0, 0.707107, 0) --Arena Place
	SceneObject(sObj):setCustomObjectName("Eisley Arena Bloodworks")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/streetsign_wall_style_01.iff", 1027.23, 3, 107.41, 0, 0.382683, 0, 0.92388, 0) --Space Port
	SceneObject(sObj):setCustomObjectName("Mos Eisley Spaceport")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/sign/streetsign_upright_style_01.iff", 1073.49, 0, 68.3427, 0, 0.707107, 0, 0.707107, 0) --Public Hangar
	SceneObject(sObj):setCustomObjectName("Public Transportation Dock")
	
	--TAILOR--
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 8.78601, 0.403271, -11.165, 610008132, 0.999983, 0, -0.00579456, 0) --Shirts
	SceneObject(sObj):setCustomObjectName("Shirts")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_shirts")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 5.04968, 0.403271, -11.2072, 610008132, 0.999983, 0, -0.00579456, 0) --Pants
	SceneObject(sObj):setCustomObjectName("Pants")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_pants")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 0.719971, 0.403271, -11.2594, 610008132, 0.999983, 0, -0.00579456, 0) --Footwear
	SceneObject(sObj):setCustomObjectName("Footwear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_footwear")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", -2.97528, 0.403271, -11.304, 610008132, 0.999983, 0, -0.00579456, 0) --Jacket
	SceneObject(sObj):setCustomObjectName("Jacket")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_jackets")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/chest_modern_style_01.iff", -1.10101, 3.09675, -11.3878, 610008132, 0.707104, 0.707105, -0.00133156, 0.00133156) --Vest
	SceneObject(sObj):setCustomObjectName("Vest")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_vests")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/chest_modern_style_01.iff", -1.10065, 2.22375, -11.3878, 610008132, 0.707104, 0.707105, -0.00133156, 0.00133156) --Robes
	SceneObject(sObj):setCustomObjectName("Robes")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_robes")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/chest_modern_style_01.iff", -1.10065, 1.30945, -11.3878, 610008132, 0.707104, 0.707105, -0.00133156, 0.00133156) --Bodysuits
	SceneObject(sObj):setCustomObjectName("Bodysuits")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_bodysuits")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 11.202, 0.403271, -8.65625, 610008132, -0.702997, 0, 0.711192, 0) --Skirts
	SceneObject(sObj):setCustomObjectName("Skirts")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_skirts")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 11.1785, 0.403271, -6.46765, 610008132, -0.702997, 0, 0.711192, 0) --Women
	SceneObject(sObj):setCustomObjectName("Women's Wear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_women")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/chest_modern_style_01.iff", 6.92175, 3.09675, -11.3584, 610008132, 0.707104, 0.707105, -0.00133156, 0.00133156) --Heaad & Goggle
	SceneObject(sObj):setCustomObjectName("Headwear & Goggles")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_headwear")
	SceneObject(sObj):populateInventoryFromContentList("tailor_goggles")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/chest_modern_style_01.iff", 6.91962, 2.22375, -11.3592, 610008132, 0.707104, 0.707105, -0.00133156, 0.00133156) --Handwear
	SceneObject(sObj):setCustomObjectName("Handwear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_handwear")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/chest_modern_style_01.iff", 6.91962, 1.33228, -11.3592, 610008132, 0.707104, 0.707105, -0.00133156, 0.00133156) --Jewelry
	SceneObject(sObj):setCustomObjectName("Jewelry")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_jewelry")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 11.1545, 0.403271, -4.3006, 610008132, -0.702997, 0, 0.711192, 0) --Misc/Belts
	SceneObject(sObj):setCustomObjectName("Belts, Bandoliers & Aprons")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_misc")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 11.1304, 0.403271, -2.12482, 610008132, -0.702997, 0, 0.711192, 0) --Bikinis
	SceneObject(sObj):setCustomObjectName("Bikinis")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_bikinis")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 11.1044, 0.403271, 0.171387, 610008132, -0.702997, 0, 0.711192, 0) --Wookiee
	SceneObject(sObj):setCustomObjectName("Wookiee Wear")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_wookiee")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 11.0788, 0.403271, 2.50256, 610008132, -0.702997, 0, 0.711192, 0)--Ithorian 1
	SceneObject(sObj):setCustomObjectName("Ithorian Wear I")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_ithorian1")
	sObj = spawnSceneObject("rp_tatooine", "object/tangible/furniture/modern/armoire_modern_style_01.iff", 11.1247, 0.403271, 4.60206, 610008132, -0.702997, 0, 0.711192, 0)--Ithorian 2
	SceneObject(sObj):setCustomObjectName("Ithorian Wear II")
	SceneObject(sObj):setPublicContainer(true)
	SceneObject(sObj):setDispenserContainer(true)
	SceneObject(sObj):populateInventoryFromContentList("tailor_ithorian2")
end

function RpTatooineMosEisleyScreenPlay:spawnMobiles()
	--Species, Equipment, Skills, Customization
	
	local pNpc
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1048, 0, 58.6983, 104, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1006.88, 0, 120.202, 88, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1009.15, 0, 118.872, 0, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1003.97, 0, 124.102, 128, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1004.04, 0, 123.296, 31, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1015.13, 0, 109.634, 127, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1016.19, 0, 109.7, 178, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1019.08, 0, 112.424, 6, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 996.454, 0, 156.619, 158, 0, "ronto", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Ronto")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 927.062, 0, 176.94, 219, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 827.661, 0, 185.862, 278, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 826.763, 0, 186.541, 124, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 824.342, 0, 193.96, 163, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 784.537, 0, 189.978, 97, 0, "ronto", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Ronto")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 805.457, 0.0521921, 148.683, 227, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 744.463, 0, 131.521, 215, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 744.391, 0, 123.51, 335, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 612.202, 0, 170.174, 118, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 628.829, 0.3, 141.032, 245, 0, "wed_treadwell", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "wed")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 627.593, 0, 141.133, 127, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 628.028, 0.3, 139.64, 300, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 509.489, 0, 110.317, 141, 0, "ronto", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Ronto")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 511.334, 0, 110.163, 263, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 502.688, 0.3, 161.276, 131, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 447.169, 0, 161.999, 100, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 418.697, 0, 130.05, 248, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 647.104, 0, 125.541, 162, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 652.651, 0, 122.754, 240, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 676.389, 0, 49.131, 300, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 675.213, 0, 51.7731, 169, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 662.93, 0, 22.3811, 129, 0, "nuna", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Nuna")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 661.526, 0, 20.4032, 225, 0, "nuna", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Nuna")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 663.211, 0, 19.7971, 321, 0, "nuna", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Nuna")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 621.731, 0, -42.8493, 0, 0, "nuna", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Nuna")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 620.874, 0, -43.9168, 294, 0, "nuna", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Nuna")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 586.441, 0.3, -71.7516, 75, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 609.683, 0.3, -104.207, 316, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 609.789, 0.3, -102.846, 268, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 633.818, 0.3, -139.467, 62, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 708.75, 0, -166.679, 216, 0, "ronto", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Ronto")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 675.021, 0, -156.163, 237, 0, "r5", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r5")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 813.286, 0, -122.393, 66, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 820.748, 0, -119.175, 218, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 881.388, 0, -78.9323, 322, 0, "eg6_power_droid", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "eg6")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 881.584, 0, -77.7988, 274, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 880.384, 0, -78.6436, 4, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 880.562, 0, -76.7914, 186, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 901.492, 0, -63.3507, 279, 0, "ronto", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Ronto")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 829.183, 0, -43.7441, 35, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 815.421, 0, 32.8535, 125, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 837.793, 0, 82.4542, 101, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 838.24, 0, 81.1182, 81, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 759.982, 0, 238.435, 288, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 739.514, 0, 267.415, 181, 0, "pit_droid", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Pit Droid")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 740.048, 0, 266.856, 212, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 740.216, 0, 265.608, 0, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 708.338, 0, 216.865, 269, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 708.917, 0, 217.712, 239, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 707.807, 0, 228.082, 222, 0, "wed_treadwell", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "wed")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 716.827, 0, 208.189, 25, 0, "eg6_power_droid", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "eg6")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 706.866, 0, 208.148, 52, 0, "r5", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r5")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 643.372, 0, 264.919, 336, 0, "le_repair_droid", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "le")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 648.857, 0.3, 195.831, 0, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 648.647, 0.3, 198.091, 128, 0, "ronto", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Ronto")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 705.521, 0, 320.413, 113, 0, "r4", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r4")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 632.025, 0, 281.805, 0, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 633.893, 0, 282.546, 0, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 625.238, 0, 278.203, 34, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 565.31, 0, 266.194, 52, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 569.579, 0, 264.918, 0, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 561.838, 0, 382.036, 254, 0, "r5", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r5")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 493.453, 0, 319.212, 190, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 489.637, 0, 320.001, 169, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 544.159, 0, 259.951, 222, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 607.371, 0, 259.385, 0, 0, "wed_treadwell", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "wed")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 583.329, 0, 365.666, 317, 0, "cll8_binary_load_lifter", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a CLL-8 Binary Load Lifter")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 664.016, 0, 243.901, 50, 0, "cll8_binary_load_lifter", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a CLL-8 Binary Load Lifter")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 689.399, 0, 207.474, 47, 0, "ronto", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Ronto")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 649.766, 0, 152.591, 44, 0, "3po_protocol_droid_red", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "3po")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 682.719, 0, 181.581, 257, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 682.719, 0, 181.581, 257, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 682.329, 0, 182.406, 196, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 681.456, 0, 181.357, 82, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 604.364, 0, 125.199, 271, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 651.064, 0, -22.5284, 124, 0, "r4", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r4")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 742.859, 0, 105.685, 300, 0, "3po_protocol_droid_silver", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "3po")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 703.607, 0, 115.519, 0, 0, "3po_protocol_droid_red", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "3po")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 687.482, 0, 100.856, 39, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 853.693, 0, 128.676, 134, 0, "r5", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r5")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 838.244, 0, -84.0254, 192, 0, "r2", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r2")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 838.654, 0, -86.347, 332, 0, "le_repair_droid", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "le")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 935.544, 0, -115.692, 238, 0, "cll8_binary_load_lifter", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a CLL-8 Binary Load Lifter")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1028, 0, -161.267, 287, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1026.95, 0, -161.771, 318, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1030.18, 0, -160.16, 272, 0, "cll8_binary_load_lifter", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a CLL-8 Binary Load Lifter")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1264.89, 0, 65.9058, 0, 0, "wed_treadwell", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "wed")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1257.25, 0, 365.025, 8, 0, "bantha", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Bantha")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1165.9, 0, 305.198, 126, 0, "ronto", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Ronto")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1114.37, 0.3, 255.425, 1, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1115.35, 0.3, 255.706, 296, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1113.49, 0.3, 256.174, 89, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 951.653, 0, 281.706, 260, 0, "dewback", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Dewback")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 935.664, 0, 309.411, 0, 0, "r2", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r2")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 896.042, 0.3, 317.786, 104, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 896.871, 0.3, 317.767, 209, 0, "3po_protocol_droid_red", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "3po")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 897.543, 0.3, 317.073, 305, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 993.75, 0, 402.952, 0, 0, "wed_treadwell", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "wed")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 964.967, 0, 416.164, 32, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 963.806, 0, 416.162, 60, 0, "r4", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r4")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 964.551, 0, 417.05, 94, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 990.522, 0, 467.993, 336, 0, "3po_protocol_droid_red", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "3po")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 943.218, 0.3, 254.092, 0, 0, "r5", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r5")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 922.842, 0, 305.332, 219, 0, "eg6_power_droid", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "eg6")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 950.81, 0, 138.817, 75, 0, "eg6_power_droid", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "eg6")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1066.87, 0, 53.6383, 219, 0, "le_repair_droid", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "le")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1058.91, 0, 81.2596, 164, 0, "r3", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r3")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1051.22, 0, 104.356, 174, 0, "r5", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "r5")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1068.83, 0, 37.2625, 293, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1067.66, 0, 37.4098, 51, 0, "jawa", "default", "default", "default") --Equip, Skill, Customization
	setRandomCreatureName(pNpc, "rodian")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1034.59, 0, 33.3862, 97, 0, "cll8_binary_load_lifter", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a CLL-8 Binary Load Lifter")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1054.84, 0, 111.016, 28, 0, "cll8_binary_load_lifter", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a CLL-8 Binary Load Lifter")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1074.55, 0, 89.9502, 21, 0, "pit_droid", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Pit Droid")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 1075.29, 0, 90.7819, 230, 0, "pit_droid", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a Pit Droid")
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_base_npc", 1, 776.632, 0, -39.4721, 140, 0, "cll8_binary_load_lifter", "default", "default", "default") --Equip, Skill, Customization
	SceneObject(pNpc):setCustomObjectName("a CLL-8 Binary Load Lifter")
	
	--VENDORS--
	
	--Melee Vendor Light
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_convo_npc", 1, 751.528, 0, 261.175, 289, 0, "rp_moncal_male", "sulon_vendor_melee_01", "default", "random", "rpg_shopkeeper")
	SceneObject(pNpc):setCustomObjectName("Okibam Rotso (a Melee Weapons Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "novice_melee")
	SceneObject(pNpc):setStoredString("vendor:shopList", "shop_weapons_melee_novice")
	--Ranged Vendor Light
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_convo_npc", 1, 750.769, 0, 275.276, 222, 0, "rp_zabrak_male", "xovros_ranged_vendor", "default", "random", "rpg_shopkeeper")
	SceneObject(pNpc):setCustomObjectName("Gjolan (a Ranged Weapon Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "novice_ranged")
	SceneObject(pNpc):setStoredString("vendor:shopList", "shop_weapons_ranged_novice")
	--Camping Vendor
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_convo_npc", 1, 738.375, 0, 275.533, 90, 0, "rp_human_female", "xovros_vendor_camping", "default", "random", "rpg_shopkeeper") 
	SceneObject(pNpc):setCustomObjectName("Raphella Lees (a Camping Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "camping")
	SceneObject(pNpc):setStoredString("vendor:shopList", "shop_camping")
	--Instrument Vendor
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_convo_npc", 1, 689.751, 0, 218.815, 89, 0, "rp_twilek_male", "xovros_hotel_receptionist", "default", "random", "rpg_shopkeeper") 
	SceneObject(pNpc):setCustomObjectName("Nayosan Yi'frit (an Instrument Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "music")
	SceneObject(pNpc):setStoredString("vendor:shopList", "shop_instruments")
	--Speeder Vendor
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_convo_npc", 1, 666.118, 0, 243.782, 118, 0, "rp_rodian_male", "vehicle_dealer_vendor", "default", "random", "rpg_shopkeeper")
	SceneObject(pNpc):setCustomObjectName("Sprei Ikiki (a Speeder Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "vehicle")
	SceneObject(pNpc):setStoredString("vendor:shopList", "shop_vehicles")
	--Mount Vendor
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_convo_npc", 1, 491.48, 0, 316.591, 192, 0, "rp_gotal_male", "vendor_mount", "default", "random", "rpg_shopkeeper") 
	SceneObject(pNpc):setCustomObjectName("Pyvaln Rokk (a Mount Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "mount")
	SceneObject(pNpc):setStoredString("vendor:shopList", "shop_mounts_tatooine")
	--Cheap Stimpack Vendor
	pNpc = spawnRoleplayMobile("rp_tatooine", "rp_convo_npc", 1, 482.509, 0, 131.549, 330, 0, "rp_gran_male", "xovros_nurse", "default", "random", "rpg_shopkeeper")
	SceneObject(pNpc):setCustomObjectName("Horuuk Kyl (a Stimpack Vendor)")
	SceneObject(pNpc):setStoredString("vendor:theme", "medicine")
	SceneObject(pNpc):setStoredString("vendor:shopList", "shop_medicine_novice")

end