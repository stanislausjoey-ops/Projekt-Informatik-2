/*
 * Verhalten.cpp
 *
 *  Created on: Dec 2, 2025
 *      Author: Joey
 */

#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"

#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"

Verhalten::Verhalten(Weg& weg):p_pWeg(weg) {
	// TODO Auto-generated constructor stub

}

Verhalten::~Verhalten() {
	// TODO Auto-generated destructor stub
}

double Verhalten::dGeschwindigkeitslimit()
{
	return p_pWeg.getTempolimit();
}

bool Verhalten::bBlocks() const
{
	return true;
}
