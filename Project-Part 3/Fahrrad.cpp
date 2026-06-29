/*
 * Fahrrad.cpp
 *
 *  Created on: Nov 7, 2025
 *      Author: Joey
 */

#include "Fahrrad.h"
#include "SimuClient.h"
#include <cmath>
using namespace std;


Fahrrad::Fahrrad(string sName, double dMaxGeschwindigkeit)
:Fahrzeug(sName,dMaxGeschwindigkeit) {
	// TODO Auto-generated constructor stub

}

Fahrrad::~Fahrrad() {
	// TODO Auto-generated destructor stub
}

double Fahrrad::dGeschwindigkeit() const
{
	double dAbnahme = floor(p_dGesamtStrecke / 20);
	double dGeschwindigkeitNeu = p_dMaxGeschwindigkeit * ( pow(0.9,dAbnahme));
	return max(dGeschwindigkeitNeu,12.0);
}

void Fahrrad::vZeichnen(Weg& weg) const
{
	double dRelPosition = p_dAbschnittStrecke / weg.getLaenge();
	if (dRelPosition < 0) dRelPosition = 0;
	if (dRelPosition > 1) dRelPosition = 1;

	bZeichneFahrrad(p_sName, weg.getName(), dRelPosition, dGeschwindigkeit());
}

void Fahrrad::vEinlesen(istream& in)
{
	Fahrzeug::vEinlesen(in);
}
