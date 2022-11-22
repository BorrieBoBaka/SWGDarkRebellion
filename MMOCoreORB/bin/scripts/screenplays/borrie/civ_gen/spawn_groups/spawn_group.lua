CivSpawnGroups = { }

function CivSpawnGroups:addCivSpawnGroup(tag, group)
	CivSpawnGroups[tag] = group;
end

function CivSpawnGroups:getCivSpawnGroup(tag)
	return CivSpawnGroups[tag]
end

