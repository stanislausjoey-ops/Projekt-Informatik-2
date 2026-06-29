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
	PKW(string sName ="", double dMaxGeschwindigkeit = 0.0, double dVerbrauch = 0.0, double dTankvolumen=55.0);
	virtual ~PKW();

	void vSimulieren() override;
	void vAusgeben(ostream& out) const override;
	double dTanken(double dMenge = numeric_limits<double>::infinity()) override;
	double dGeschwindigkeit() const override;
	void vZeichnen(Weg& weg) const;
	bool bIsNotBlocking() const override;
	void vEinlesen(istream& in) override;

private :
	double p_dVerbrauch; //Liter/100km
	double p_dTankvolumen; //Liter
	double p_dTankinhalt; //Liter
};

#endif /* PKW_H_ */
