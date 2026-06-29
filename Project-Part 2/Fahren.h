/*
 * Fahren.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Joey
 */

#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"

class Fahren: public Verhalten {
public:
	Fahren(Weg& weg);
	virtual ~Fahren();

	double dStrecke(Fahrzeug&, double) override;
};

#endif /* FAHREN_H_ */
