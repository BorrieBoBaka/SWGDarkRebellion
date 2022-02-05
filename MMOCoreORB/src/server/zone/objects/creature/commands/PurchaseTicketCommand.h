/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PURCHASETICKETCOMMAND_H_
#define PURCHASETICKETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/transaction/TransactionLog.h"

#include "QueueCommand.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/TicketSelectionSuiCallback.h"
#include "server/zone/managers/planet/PlanetTravelPoint.h"
#include "server/zone/objects/group/GroupObject.h"

class PurchaseTicketCommand : public QueueCommand {
public:

	PurchaseTicketCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		SortedVector<QuadTreeEntry*> closeObjects;
		CloseObjectsVector* vec = (CloseObjectsVector*) creature->getCloseObjects();
		vec->safeCopyTo(closeObjects);

		bool nearTravelTerminal = false;

		for (int i = 0; i < closeObjects.size(); i++) {
			SceneObject* object = cast<SceneObject*>( closeObjects.get(i));
			if (object != nullptr && object->getGameObjectType() == SceneObjectType::TRAVELTERMINAL && checkDistance(creature, object, 8)) {
				nearTravelTerminal = true;
				break;
			}

		}

		if (!nearTravelTerminal) {
			creature->sendSystemMessage("@travel:too_far"); // You are too far from the terminal to purchase a ticket.
			return GENERALERROR;
		}

		ManagedReference<CityRegion*> currentCity = creature->getCityRegion().get();

		int departureTax = 0;
		if (currentCity != nullptr){
			if (currentCity->isBanned(creature->getObjectID())) {
				creature->sendSystemMessage("@city/city:city_cant_purchase_ticket"); //You are banned from using the services of this city. You cannot purchase a ticket.
				return GENERALERROR;
			}
			if(!currentCity->isClientRegion()){
				departureTax = currentCity->getTravelTax();
			}
		}
		ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

		if (inventory == nullptr)
			return GENERALERROR;

		String departurePlanet, departurePoint, arrivalPlanet, arrivalPoint, type;
		bool roundTrip = true;


		try {
			UnicodeTokenizer tokenizer(arguments);
			tokenizer.getStringToken(departurePlanet);
			tokenizer.getStringToken(departurePoint);
			tokenizer.getStringToken(arrivalPlanet);
			tokenizer.getStringToken(arrivalPoint);
			if(tokenizer.hasMoreTokens()) {
				tokenizer.getStringToken(type);
				if (type == "single" || type == "0")
					roundTrip = false;
			}

		} catch(Exception& e) {
			return INVALIDPARAMETERS;
		}

		departurePlanet = departurePlanet.replaceAll("_", " ");
		departurePoint = departurePoint.replaceAll("_", " ");
		arrivalPlanet = arrivalPlanet.replaceAll("_", " ");
		arrivalPoint = arrivalPoint.replaceAll("_", " ");

		ManagedReference<Zone*> departureZone = server->getZoneServer()->getZone(departurePlanet);
		ManagedReference<Zone*> arrivalZone = server->getZoneServer()->getZone(arrivalPlanet);

		if (departureZone == nullptr)
			return GENERALERROR;

		if (arrivalZone == nullptr)
			return GENERALERROR;

		ManagedReference<PlanetManager*> pmDeparture = departureZone->getPlanetManager();
		ManagedReference<PlanetManager*> pmArrival = arrivalZone->getPlanetManager();

		if (!pmArrival->isExistingPlanetTravelPoint(arrivalPoint)) {
			creature->sendSystemMessage("@travel:no_location_found"); //No location was found for your destination.
			return INVALIDPARAMETERS;
		}

		if (!pmDeparture->isExistingPlanetTravelPoint(departurePoint)) {
			creature->sendSystemMessage("The given departure point was not found.");
			return INVALIDPARAMETERS;
		}

		Reference<PlanetTravelPoint*>  destPoint = pmArrival->getPlanetTravelPoint(arrivalPoint);

		if (destPoint == nullptr)
			return GENERALERROR;

		ManagedReference<CreatureObject*> arrivalShuttle = destPoint->getShuttle();

		if (arrivalShuttle == nullptr)
			return GENERALERROR;


		ManagedReference<CityRegion*> destCity = arrivalShuttle->getCityRegion().get();

		if (destCity != nullptr){
			if (destCity.get()->isBanned(creature->getObjectID())) {
				creature->sendSystemMessage("@city/city:banned_from_that_city");  // You have been banned from traveling to that city by the city militia
				return GENERALERROR;
			}
		}

		//Check to see if this point can be reached from this location.
		if (!pmDeparture->isTravelToLocationPermitted(departurePoint, arrivalPlanet, arrivalPoint))
			return GENERALERROR;

		if (roundTrip && !pmArrival->isTravelToLocationPermitted(arrivalPoint, departurePlanet, departurePoint))
			return GENERALERROR; //If they are doing a round trip, make sure they can travel back.

		int baseFare = pmDeparture->getTravelFare(departurePlanet, arrivalPlanet);

		if (baseFare == 0) { // Make sure that the travel route is valid
			creature->sendSystemMessage("Invalid travel route specified.");
			return GENERALERROR;
		}

		int fare = baseFare + departureTax;

		if (roundTrip)
			fare *= 2;

		//Make sure they have space in the inventory for the tickets before purchasing them.
		Locker _lock(inventory, creature);

		if (inventory->getContainerObjectsSize() + ((roundTrip) ? 2 : 1) > inventory->getContainerVolumeLimit()) {
			creature->sendSystemMessage("@error_message:inv_full"); //Your inventory is full.
			return GENERALERROR;
		}

		/*
		//Check if they have funds.
		int bank = creature->getBankCredits();
		int cash = creature->getCashCredits();

		if (bank < fare) {
			int diff = fare - bank;

			if (diff > cash) {
				ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(creature, 0);
				suiBox->setPromptTitle("");
				suiBox->setPromptText("You do not have sufficient funds for that.");

				creature->sendMessage(suiBox->generateMessage());
				creature->sendSystemMessage("@travel:short_funds"); //You do not have enough money to complete the ticket purchase.
				return GENERALERROR;
			}

			TransactionLog trxBank(creature, TrxCode::TRAVELSYSTEM, bank, false);
			trxBank.addState("departurePlanet", departurePlanet);
			trxBank.addState("departurePoint", departurePoint);
			trxBank.addState("arrivalPlanet", arrivalPlanet);
			trxBank.addState("arrivalPoint", arrivalPoint);

			creature->subtractBankCredits(bank); //Take all from the bank, since they didn't have enough to cover.

			TransactionLog trxCash(creature, TrxCode::TRAVELSYSTEM, diff, true);
			trxCash.groupWith(trxBank);
			trxCash.addState("departurePlanet", departurePlanet);
			trxCash.addState("departurePoint", departurePoint);
			trxCash.addState("arrivalPlanet", arrivalPlanet);
			trxCash.addState("arrivalPoint", arrivalPoint);

			creature->subtractCashCredits(diff); //Take the rest from the cash.
			trxCash.groupWith(trxBank);
		} else {
			TransactionLog trx(creature, TrxCode::TRAVELSYSTEM, fare, false);
			trx.addState("departurePlanet", departurePlanet);
			trx.addState("departurePoint", departurePoint);
			trx.addState("arrivalPlanet", arrivalPlanet);
			trx.addState("arrivalPoint", arrivalPoint);

			creature->subtractBankCredits(fare); //Take all of the fare from the bank.
		}
		*/

		//StringIdChatParameter params("@base_player:prose_pay_acct_success"); //You successfully make a payment of %DI credits to %TO.
		//params.setDI(baseFare + (roundTrip * baseFare));
		//params.setTO("@money/acct_n:travelsystem"); //the Galactic Travel Commission
		//
		//creature->sendSystemMessage(params);

		ManagedReference<SceneObject*> ticket1 = pmDeparture->createTicket(departurePoint, arrivalPlanet, arrivalPoint);
		if (ticket1 == nullptr) {
			creature->sendSystemMessage("Error creating travel ticket.");
			return GENERALERROR;
		}

		if (inventory->transferObject(ticket1, -1, true)) {
			ticket1->sendTo(creature, true);
		} else {
			ticket1->destroyObjectFromDatabase(true);
			creature->sendSystemMessage("Error transferring travel ticket to inventory.");
			return GENERALERROR;
		}

		if (roundTrip) {
			ManagedReference<SceneObject*> ticket2 = pmArrival->createTicket(arrivalPoint, departurePlanet, departurePoint);

			if (inventory->transferObject(ticket2, -1, true)) {
				ticket2->sendTo(creature, true);
			} else {
				ticket2->destroyObjectFromDatabase(true);
				creature->sendSystemMessage("Error transferring round-trip travel ticket to inventory.");
				return GENERALERROR;
			}
		}
		_lock.release();

		if(currentCity != nullptr && !currentCity->isClientRegion() && departureTax > 0) {
			Locker clocker(currentCity, creature);
			int taxPaid = departureTax + (roundTrip * departureTax);
			currentCity->addToCityTreasury(taxPaid);

			StringIdChatParameter param("@city/city:city_ticket_pay"); // You pay a tax of %DI credits to the local City Travel Authority.
			param.setDI(taxPaid);

			creature->sendSystemMessage(param);
		}

		//ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(creature, 0);
		//suiBox->setPromptTitle("");
		//suiBox->setPromptText("@travel:ticket_purchase_complete"); //Ticket purchase complete
		//
		//creature->sendMessage(suiBox->generateMessage());

		//creature->sendSystemMessage("DEBUG: The Purchase Ticket Command was executed.");

		//Teleporting

		// calculate arrival position
		//ticket1

		ManagedReference<TicketObject*> ticketObject = ticket1.castTo<TicketObject*>();

		//Disgusting Edit, but I'm too noob in C++ to do this reliably.
		String arrivalPlanet2 = ticketObject->getArrivalPlanet();
		String arrivalPointName2 = ticketObject->getArrivalPoint();

		ManagedReference<Zone*> arrivalZone2 = server->getZoneServer()->getZone(arrivalPlanet2);

		Reference<PlanetTravelPoint*> arrivalPoint2 = arrivalZone2->getPlanetManager()->getPlanetTravelPoint(arrivalPointName2);

		ManagedReference<CreatureObject*> targetShuttleObject = arrivalPoint2->getShuttle();

		Coordinate p;
		float x;
		float y;

		p.initializePosition(arrivalPoint2->getArrivalPosition());

		ManagedReference<CityRegion*> region = targetShuttleObject != nullptr ? targetShuttleObject->getCityRegion().get() : nullptr;

		// Randomize the arrival a bit to try and avoid everyone zoning on top of each other
		// For NPC cities, use the generic method
		if (region == nullptr || region->isClientRegion()) {
			p.randomizePosition(3);

			x = p.getPositionX();
			y = p.getPositionY();

		} else {
			// relative orientation of the shuttle
			float oy = targetShuttleObject->getDirection()->getY();
			float dirDegrees = (acos(oy) * 180 / M_PI) * 2;

			// the proper location for arrival is along a 36 degree arc centered on the shuttle's facing axis, between 13 and 16 meters out
			dirDegrees = dirDegrees - 18 + System::random(36);
			float dirRadians = dirDegrees * M_PI / 180;
			float distance = 13 + System::random(3);

			// update the X & Y positions accordingly
			x = p.getPositionX() + sin(dirRadians) * distance;
			y = p.getPositionY() + cos(dirRadians) * distance;
		}

		creature->switchZone(arrivalZone2->getZoneName(), x, p.getPositionZ(), y, 0);

		Locker ticketLocker(ticketObject);

		// remove the ticket from inventory and destroy it.
		ticket1->destroyObjectFromWorld(true);
		ticket1->destroyObjectFromDatabase(true);

		//End Teleporting Code

		return SUCCESS;
	}

};

#endif //PURCHASETICKETCOMMAND_H_
