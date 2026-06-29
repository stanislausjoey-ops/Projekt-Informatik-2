/*
 * Fahrausnahme.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Joey
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_
#include <exception>

class Fahrzeug;
class Weg;

class Fahrausnahme {
public:
	Fahrausnahme(Fahrzeug&,Weg&);
	virtual ~Fahrausnahme();
	void virtual vBearbeiten() const = 0;

protected :
	Fahrzeug& p_rFahrzeug;
	Weg& p_rWeg;
};

#endif /* FAHRAUSNAHME_H_ */
