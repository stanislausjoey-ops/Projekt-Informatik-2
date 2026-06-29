/*
 * PKW.cpp
 *
 *  Created on: Nov 7, 2025
 *      Author: hangon
 */

#include "PKW.h"

extern double dGlobaleZeit;

PKW::PKW(const string& sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen)
:Fahrzeug(sName,dMaxGeschwindigkeit),
 p_dVerbrauch(dVerbrauch),
 p_dTankvolumen(dTankvolumen),
 p_dTankinhalt(dTankvolumen/2)
{

	// TODO Auto-generated constructor stub

}

PKW::~PKW() {
	// TODO Auto-generated destructor stub
}

double PKW::dTanken(double dMenge)
{
	double dPlatz = p_dTankvolumen - p_dTankinhalt;
	if (dMenge >= dPlatz)
	{
		p_dTankinhalt = p_dTankvolumen;
		return dPlatz;
	}
	else
	{
		p_dTankinhalt += dMenge;
		return dMenge;
	}
}

void PKW::vSimulieren()
{
	if (p_dTankinhalt <= 0.0) return;

	double dZeitdiff = dGlobaleZeit - p_dZeit;
	if (dZeitdiff <= 0.0) return;

	double dStrecke = dZeitdiff * p_dMaxGeschwindigkeit;
	double dVerbrauch = p_dVerbrauch * (dStrecke/ 100);

	if (p_dTankinhalt >= dVerbrauch)
	{
		p_dTankinhalt -= dVerbrauch;
	}
	else if (p_dTankinhalt < dVerbrauch)
	{
		p_dTankinhalt = 0.0;
	}

	p_dGesamtStrecke += dStrecke;
	p_dGesamtZeit += dZeitdiff;
	p_dZeit = dGlobaleZeit;

}

void PKW::vAusgeben(ostream& out) const
{
	Fahrzeug::vAusgeben(out);
	cout << resetiosflags(ios::left) << setiosflags(ios::right);
	cout << setw(20) << p_dTankinhalt
	<< setw(20) << (p_dGesamtStrecke/100)*p_dVerbrauch;
}

