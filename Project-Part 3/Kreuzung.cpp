/*
 * Kreuzung.cpp
 *
 *  Created on: Jan 27, 2026
 *      Author: Joey
 */

#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <random>
#include <iomanip>
#include <iostream>
#include <string>
#include <list>
#include <memory>


Kreuzung::Kreuzung(string sName, double dTankstelle ):
Simulationsobjekt(sName), p_dTankstelle(dTankstelle)
{
	// TODO Auto-generated constructor stub

}

Kreuzung::~Kreuzung() {
	// TODO Auto-generated destructor stub
}

void Kreuzung::vVerbinde(string sHinweg, string sRueckweg, double dLaenge,
			shared_ptr<Kreuzung> pStart, shared_ptr<Kreuzung> pZiel, Tempolimit eTempolimit,
			bool bUeberholverbot)
{
	shared_ptr<Weg> pHinweg = make_shared<Weg>(sHinweg, dLaenge, eTempolimit, bUeberholverbot, pZiel); // @suppress("Invalid arguments")
	shared_ptr<Weg> pRueckweg = make_shared<Weg>(sRueckweg, dLaenge, eTempolimit, bUeberholverbot, pStart); // @suppress("Invalid arguments")

	pHinweg->vSetRueckweg(pRueckweg);
	pRueckweg->vSetRueckweg(pHinweg);

	if(pStart) pStart->p_pWege.push_back(move(pHinweg)); //move ownership to 1st ptr in list and connect roads move away fr it
	if(pZiel) pZiel->p_pWege.push_back(move(pRueckweg));
}

void Kreuzung::vTanken(Fahrzeug& aFzg)
{
	if(p_dTankstelle > 0.0)
	{
		double dMenge = aFzg.dTanken(p_dTankstelle);
		p_dTankstelle -= dMenge;
		if(p_dTankstelle < 0)
		{
			p_dTankstelle = 0;
		}
	}
	else
	{
		p_dTankstelle = 0; //makes dTankstelle = 0 incase it has negative value
	}
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> pFzg, double dStartZeit)
{
	if(!pFzg) return;
	vTanken(*pFzg);

	p_pWege.front()->vAnnahme(move(pFzg),dStartZeit);
}

void Kreuzung::vSimulieren()
{
	for(auto it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		(*it)->vSimulieren();
	}
}
shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& pWeg)
{
	if (p_pWege.empty()) return nullptr;
	shared_ptr<Weg> pRueck = pWeg.pGetRueckweg(); //store road we came from

	if (p_pWege.size() == 1) return p_pWege.front();

	static std::mt19937 device(0);
	uniform_int_distribution<int> dist(0, p_pWege.size()-1);

	while(true)
	{
		int zuf = dist(device);
		int zaehler = 0;

		for (auto it = p_pWege.begin(); it != p_pWege.end(); ++it)
		{
			if (zaehler == zuf)
			{
				if(*it != pRueck) return *it; //not the road we came from
				break;
			}
			++zaehler;
		}
	}
}

double Kreuzung::dGetTankstelle()
{
	return p_dTankstelle;
}

void Kreuzung::vEinlesen(istream& in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dTankstelle;
}

void Kreuzung::vAusgeben(ostream& out) const
{
	Simulationsobjekt::vAusgeben(out);
	out << resetiosflags(ios::left) << setiosflags(ios::right);
	out << setw(10) << p_dTankstelle;
}
