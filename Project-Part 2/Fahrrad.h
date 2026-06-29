/*
 * Fahrrad.h
 *
 *  Created on: Nov 7, 2025
 *      Author: Joey
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"
#include "Weg.h"

class Fahrrad: public Fahrzeug {
public:
	Fahrrad(const string& sName, double dMaxGeschwindigkeit);
	virtual ~Fahrrad();
	double dGeschwindigkeit() const override;

	void vZeichnen(Weg& weg) const override;

};

#endif /* FAHRRAD_H_ */
