#ifndef VEHICLEOBJECTTEMPLATE_H_
#define VEHICLEOBJECTTEMPLATE_H_

#include "templates/creature/SharedCreatureObjectTemplate.h"

class VehicleObjectTemplate : public SharedCreatureObjectTemplate {
	int decayRate, decayCycle, passengerCapacity;
	String passengerSeat;

public:
	VehicleObjectTemplate() {
		decayRate = 0;
		decayCycle = 0;
		passengerCapacity = 0;
	}

	~VehicleObjectTemplate() {

	}

	void readObject(LuaObject* templateData) {
		SharedCreatureObjectTemplate::readObject(templateData);
		decayRate = templateData->getIntField("decayRate");
		decayCycle = templateData->getIntField("decayCycle");
		//needed fields for multipassenger read from lua (EiF)
		passengerCapacity = templateData->getIntField("passengerCapacity");
		passengerSeat = templateData->getStringField("passengerSeatString");

    }

	bool isVehicleObjectTemplate() {
		return true;
	}

	//used for display on vehicle examine and for checks when a non-owner attempts to mount the vehicle
	int getPassengerCapacity() {
		return passengerCapacity;
	}

	//used for generating a passenger seat for a passenger
	String& getPassengerSeatString() {
		return passengerSeat;
	}


	int getDecayRate() {
		return decayRate;
	}

	int getDecayCycle() {
		return decayCycle;
	}

};

#endif /* VEHICLEOBJECTTEMPLATE_H_ */
