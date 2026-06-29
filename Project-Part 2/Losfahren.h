/*
 * Losfahren.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Joey
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Losfahren: public Fahrausnahme {
public:
	Losfahren(Fahrzeug&, Weg&);
	virtual ~Losfahren();

	void vBearbeiten() const override;
};

#endif /* LOSFAHREN_H_ */
