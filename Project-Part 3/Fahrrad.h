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
	Fahrrad(string sName = "", double dMaxGeschwindigkeit = 0.0);
	virtual ~Fahrrad();
	double dGeschwindigkeit() const override;

	void vZeichnen(Weg& weg) const override;
	void vEinlesen(istream& in) override;

};

#endif /* FAHRRAD_H_ */
