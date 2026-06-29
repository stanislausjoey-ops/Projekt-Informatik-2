/*
 * Streckenende.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Joey
 */

#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"

class Streckenende: public Fahrausnahme {
public:
	Streckenende(Fahrzeug&, Weg&);
	virtual ~Streckenende();

	void vBearbeiten() const override;
};

#endif /* STRECKENENDE_H_ */


