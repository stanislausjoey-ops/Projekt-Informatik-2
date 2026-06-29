/*
 * Fahren.cpp
 *
 *  Created on: Dec 2, 2025
 *      Author: Joey
 */

#include "Fahren.h"
#include "Weg.h"
#include "Streckenende.h"

Fahren::Fahren(Weg& weg)
:Verhalten(weg)
{
	// TODO Auto-generated constructor stub

}

Fahren::~Fahren() {
	// TODO Auto-generated destructor stub
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if(dZeitIntervall <= 0.0){return 0.0;} //check if alr simulate

	double dRestStrecke = p_pWeg.dGetSchranke() - aFzg.getAbschnittStrecke();
	double dZumFahren = dZeitIntervall * aFzg.dGeschwindigkeit();

	if (dRestStrecke <= 0)
	{
		if (aFzg.getAbschnittStrecke() >= p_pWeg.getLaenge() - 1e-9)
		{
			throw Streckenende(aFzg,p_pWeg);
		}
	}
	return (dZumFahren < dRestStrecke)? dZumFahren : dRestStrecke;
}

bool Fahren::bBlocks() const
{
	return true;
}
