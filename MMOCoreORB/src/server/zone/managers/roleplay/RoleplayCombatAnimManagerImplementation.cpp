#include "server/zone/Zone.h"
#include "server/zone/managers/roleplay/RoleplayCombatAnimManager.h"

void RoleplayCombatAnimManagerImplementation::loadLuaConfig() {
	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/roleplay/combat_animation_manager.lua")) {
		error("Cannot read combat animation manager data.");
		return;
	}

	//Load 'em

	info("Loaded Roleplay Combat Animations.", true);

	delete lua;
	lua = nullptr;
}