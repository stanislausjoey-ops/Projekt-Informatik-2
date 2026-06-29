/*
 * Verhalten.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Joey
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_

class Weg;
class Fahrzeug;

class Verhalten {
public:
	Verhalten(Weg& weg );
	virtual ~Verhalten();

	virtual double dStrecke(Fahrzeug&, double) = 0;
	double dGeschwindigkeitslimit();

protected:
	Weg& p_pWeg;
};

#endif /* VERHALTEN_H_ */
