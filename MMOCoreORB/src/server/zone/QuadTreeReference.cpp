/*
 * QuadTreeReference.cpp
 *
 *  Created on: 03/09/2011
 *      Author: TheAnswer
 */

#include "QuadTreeReference.h"

using namespace server::zone;

bool QuadTreeReference::toBinaryStream(ObjectOutputStream* stream) {
	//if ()
	/*Vector<ManagedReference<QuadTreeEntry*> >* vector = nullptr;

	if (get() != nullptr)
		vector = get()->getContainedEntries();
	else
		vector = new Vector<ManagedReference<QuadTreeEntry*> >();

	vector->toBinaryStream(stream);

	delete vector;*/

	return true;

}

bool QuadTreeReference::parseFromBinaryStream(ObjectInputStream* stream) {
	/*Vector<ManagedReference<QuadTreeEntry*> >* vector = new Vector<ManagedReference<QuadTreeEntry*> >();

	vector->parseFromBinaryStream(stream); //obejcts will get loaded and inserted into zone

	delete vector;*/

	return true;
}

QuadTree* QuadTreeReference::operator=(QuadTree* obj) {
#ifdef WITH_STM
	setObject(obj);
#else
	updateObject(obj);
#endif

	return obj;
}

