/*
 * Losfahren.cpp
 *
 *  Created on: Dec 3, 2025
 *      Author: Joey
 */

#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"

Losfahren::Losfahren(Fahrzeug& fzg, Weg& weg)
: Fahrausnahme (fzg,weg)
{
	// TODO Auto-generated constructor stub

}

Losfahren::~Losfahren() {
	// TODO Auto-generated destructor stub
}

void Losfahren::vBearbeiten() const
{
	cout <<"Losfahren: " << p_rFahrzeug.getName() << " Weg: " << p_rWeg.getName()  << endl;

//	p_rWeg.vAnnahme(p_rWeg.pAbgabe(p_rFahrzeug));

	auto p = p_rWeg.pAbgabe(p_rFahrzeug);

	    if (p)
	    {
	        p_rWeg.vAnnahme(std::move(p));
	    }
}
