/*
 * PKW.cpp
 *
 *  Created on: Nov 7, 2025
 *      Author: Joey
 */

#include "PKW.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "SimuClient.h"
#include <cmath>

extern double dGlobaleZeit;

PKW::PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen)
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
	double dZeitdiff = dGlobaleZeit - p_dZeit;
	if (dZeitdiff <= 0.0) return;

	if (p_dTankinhalt <= 0.0)
	{
		p_dGesamtZeit += dZeitdiff;
		p_dZeit = dGlobaleZeit;
		return;
	}

	double dVorStrecke = p_dGesamtStrecke;
	Fahrzeug::vSimulieren();

	double dZumFahren = p_dGesamtStrecke - dVorStrecke;
	if (dZumFahren <= 0.0)
	{
		return;
	}

	//double dStrecke = dZeitdiff * p_dMaxGeschwindigkeit;
	double dVerbrauch = p_dVerbrauch * (dZumFahren/ 100);

	if (p_dTankinhalt >= dVerbrauch)
	{
		p_dTankinhalt -= dVerbrauch;
	}
	else if (p_dTankinhalt < dVerbrauch)
	{
		p_dTankinhalt = 0.0;
	}

	p_dGesamtStrecke += dZumFahren;
	p_dGesamtZeit += dZeitdiff;
	p_dZeit = dGlobaleZeit;

}

void PKW::vAusgeben(ostream& out) const
{
	Fahrzeug::vAusgeben(out);
	out << resetiosflags(ios::left) << setiosflags(ios::right);
	out << setw(25) << p_dTankinhalt
	<< setw(20) << (p_dGesamtStrecke/100.0)*p_dVerbrauch;
	//<< setw(10) << p_dVerbrauch
	//<< setw(10) << p_dTankvolumen;
}


double PKW::dGeschwindigkeit() const
{
	if (!p_pVerhalten)
	{
		return p_dMaxGeschwindigkeit;
	}
	if (p_dMaxGeschwindigkeit > p_pVerhalten->dGeschwindigkeitslimit())
	{
		return p_pVerhalten->dGeschwindigkeitslimit();
	}
	else
	{
		return p_dMaxGeschwindigkeit;
	}
}

void PKW::vZeichnen(Weg& weg) const
{
	double dRelPosition = p_dAbschnittStrecke / weg.getLaenge();
	if (dRelPosition < 0) dRelPosition = 0;
	if (dRelPosition > 1) dRelPosition = 1;

	bZeichnePKW(p_sName, weg.getName(), dRelPosition, dGeschwindigkeit(),p_dTankinhalt);
}

bool PKW::bIsNotBlocking() const
{
	if (!p_pVerhalten) return true; //no behavior assigned
	if (!p_pVerhalten->bBlocks())
		return true;

	return (p_dTankinhalt <= 1e-9); // returns false when fuel still available and still fahren
}

void PKW::vEinlesen(istream& in)
{
	Fahrzeug::vEinlesen(in);
	in >> p_dVerbrauch;
	in >> p_dTankvolumen;

	p_dTankinhalt = p_dTankvolumen / 2.0;
}
