/*
 * Parken.cpp
 *
 *  Created on: Dec 2, 2025
 *      Author: Joey
 */

#include "Parken.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Losfahren.h"
#include <iostream>
#include <cmath>
using namespace std;

extern double dGlobaleZeit;

Parken::Parken(Weg& weg, double dStartZeit)
:Verhalten(weg), p_dStartZeit (dStartZeit)
{
	// TODO Auto-generated constructor stub

}

Parken::~Parken() {
	// TODO Auto-generated destructor stub
}

double Parken::dStrecke(Fahrzeug& aFzg,double dZeitIntervall)
{
	double dEpsilon = 0.00001;
	if (dGlobaleZeit + dEpsilon >= p_dStartZeit)
	{
		//cout << aFzg.getName() << " fahrt weiter auf " << p_pWeg.getName() << " um " << p_dStartZeit << endl;
		throw Losfahren(aFzg, p_pWeg);
		aFzg.vNeueStrecke(p_pWeg);
	}
	else
	{
		return 0.0;
	}
	return 0.0;
}

bool Parken::bBlocks() const
{
	return false;
}
