/*
 * Streckenende.cpp
 *
 *  Created on: Dec 3, 2025
 *      Author: Joey
 */

#include "Streckenende.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>

Streckenende::Streckenende(Fahrzeug& fzg, Weg& weg)
: Fahrausnahme(fzg,weg)
{
	// TODO Auto-generated constructor stub

}

Streckenende::~Streckenende() {
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten() const
{
	cout <<"Streckenende: " << p_rFahrzeug.getName() << " Weg: " << p_rWeg.getName() << endl;
	p_rWeg.pAbgabe(p_rFahrzeug);
}
