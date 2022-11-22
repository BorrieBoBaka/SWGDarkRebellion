/*
 * DMColorObjectSuiCallback.h
 *
 *  Created on: 4/5/2022
 *      Author: Borrie BoBaka
 *		Credits: TA & Valk & bluree for the ColorArmorSuiCallback file.
 */

#ifndef DMCOLOROBJECTSUICALLBACK_H_
#define DMCOLOROBJECTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class DMColorObjectSuiCallback : public SuiCallback {
public:
	DMColorObjectSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isColorPicker() || cancelPressed)
			return;

		if (!creature->isPlayerCreature())
			return;

		SuiColorBox* cBox = cast<SuiColorBox*>(sui);

		int index = Integer::valueOf(args->get(0).toString());

		String palette = cBox->getColorPalette();

		ManagedReference<SceneObject*> armorRehue = cBox->getUsingObject().get();

		if (armorRehue == nullptr)
			return;

		ManagedReference<TangibleObject*> armorRehueTano = armorRehue->asTangibleObject();

		if (armorRehueTano != nullptr) {
			Locker locker(armorRehueTano, creature);

			armorRehueTano->setCustomizationVariable(palette, index, true);
		}
	}
};

#endif /* DMCOLOROBJECTSUICALLBACK_H_ */
