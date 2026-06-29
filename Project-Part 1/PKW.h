/*
 * PKW.h
 *
 *  Created on: Nov 7, 2025
 *      Author: Joey
 */

#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"
#include <limits>

class PKW: public Fahrzeug {
public:
	PKW(const string& sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen=55.0);
	virtual ~PKW();

	void vSimulieren() override;
	void vAusgeben(ostream& out) const override;
	double dTanken(double dMenge = numeric_limits<double>::infinity()) override;

private :
	double p_dVerbrauch; //Liter/100km
	double p_dTankvolumen; //Liter
	double p_dTankinhalt; //Liter
};

#endif /* PKW_H_ */
