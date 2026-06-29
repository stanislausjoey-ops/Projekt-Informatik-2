/*
 * Parken.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Joey
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken: public Verhalten {
public:
	Parken(Weg&, double);
	virtual ~Parken();

	double dStrecke(Fahrzeug&, double) override;
	bool bBlocks() const override;

private :
	double p_dStartZeit;
};

#endif /* PARKEN_H_ */
