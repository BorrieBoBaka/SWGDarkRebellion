/*
 * RpShipDeedTemplate.h
 *
 *  Created on: Oct 6, 2022
 *      Author: BorrieBoBaka
 */

#ifndef RPSHIPDEEDTEMPLATE_H_
#define RPSHIPDEEDTEMPLATE_H_

#include "templates/tangible/DeedTemplate.h"

class RpShipDeedTemplate : public DeedTemplate {
private:
	String controlDeviceObjectTemplate;
	String appearanceMobile;
	String landFlatteningPoint;

public:
	RpShipDeedTemplate() {

	}

	~RpShipDeedTemplate() {

	}

	void readObject(LuaObject* templateData) {
		DeedTemplate::readObject(templateData);

		controlDeviceObjectTemplate = templateData->getStringField("controlDeviceObjectTemplate");
		appearanceMobile = templateData->getStringField("appearanceMobile");
		landFlatteningPoint = templateData->getStringField("landFlatteningPoint");
    }

	String getControlDeviceObjectTemplate()
	{
		return controlDeviceObjectTemplate;
	}

	String getAppearanceMobile()
	{
		return appearanceMobile;
	}

	String getLandFlatteningPoint() {
		return landFlatteningPoint;
	}
};


#endif /* RPSHIPDEEDTEMPLATE_H_ */
