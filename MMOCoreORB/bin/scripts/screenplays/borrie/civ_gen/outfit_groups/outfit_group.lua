CivOutfitGroups = { }

function CivOutfitGroups:addCivOutfitGroup(tag, group)
	CivOutfitGroups[tag] = group;
end

function CivOutfitGroups:getCivOutfitGroup(tag)
	return CivOutfitGroups[tag]
end

