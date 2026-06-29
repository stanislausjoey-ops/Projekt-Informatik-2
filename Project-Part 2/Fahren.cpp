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
	if(dZeitIntervall <= 0.0){return 0.0;} //alr simulated

	double dRestStrecke = p_pWeg.getLaenge() - aFzg.getAbschnittStrecke();
	double dZumFahren = dZeitIntervall * aFzg.dGeschwindigkeit();

	if (dRestStrecke > 0)
		{
			if (dZumFahren < dRestStrecke )
			{
				return dZumFahren;
			}
			else
			{
				return dRestStrecke;
			}
		}
	else
	{
		throw Streckenende(aFzg,p_pWeg);
	}
}
