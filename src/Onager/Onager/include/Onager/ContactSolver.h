#pragma once

#include "Contact.h"

namespace ong
{
	struct WorldContext;

	struct ContactConstraint
	{
		float veloctiyBias[MAX_CONTACT_POINTS];
	};


	void preSolveContacts(WorldContext* w, Contact** contacts, int numContacts, float invDt, ContactConstraint* contactConstraints);
	void solveContacts(WorldContext* w, Contact** contacts, int numContacts, ContactConstraint* constraints);
}