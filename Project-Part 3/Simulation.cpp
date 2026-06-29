/*
 * Simulation.cpp
 *
 *  Created on: Jan 28, 2026
 *      Author: Joey
 */

#include "Simulation.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahrrad.h"
#include "TempoLimit.h"
#include "Simulationsobjekt.h"
#include "Simuclient.h"
#include <iostream>
#include <iomanip>
using namespace std;

extern int iZeile;
extern double dGlobaleZeit;

Simulation::Simulation() {
	// TODO Auto-generated constructor stub

}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::vEinlesen(istream& in, bool bMitGrafik)
{
	if(bMitGrafik)
	{
		bInitialisiereGrafik(1000,1000);
	}
	while (!in.eof()) //loop till the stream reach end of file
	{
		string sSchluesselwort = "";
		in >> sSchluesselwort;

		if (sSchluesselwort == "KREUZUNG")
		{
			iZeile++;
			shared_ptr<Kreuzung> kreuzung = make_shared<Kreuzung>();
			in >> *kreuzung;


			if(p_pKreuzung.find(kreuzung->getName()) != p_pKreuzung.end())
			{
				throw runtime_error("Kreuzung existiert schon");
			}
			p_pKreuzung[kreuzung->getName()] = kreuzung;

			if(bMitGrafik)
			{
				int x,y;
				in >> x >> y;
				bZeichneKreuzung(x,y);
			}
		}
		else if (sSchluesselwort == "STRASSE")
		{
			iZeile++;
			string sNameQ, sNameZ, sNameW1, sNameW2;
			double dLaenge;
			int iLimit, iUeberholverbot;
			bool bUeberholverbot;
			Tempolimit eLimit;

			in >> sNameQ;
			in >> sNameZ;
			in >> sNameW1;
			in >> sNameW2;
			in >> dLaenge;
			in >> iLimit;
			in >> iUeberholverbot;

			switch (iLimit)
			{
			case 1: eLimit = Tempolimit::Innerorts;
				break;
			case 2: eLimit = Tempolimit::Landstrasse;
				break;
			case 3: eLimit = Tempolimit::Autobahn;
				break;
			default: throw runtime_error("Falsches Tempolimit");
				break;
			}

			switch (iUeberholverbot)
			{
			case 0: bUeberholverbot = false;
				break;
			case 1: bUeberholverbot = true;
				break;
			default: throw runtime_error("Falsches Ueberholverbot");
				break;
			}

			if(p_pKreuzung.find(sNameQ) == p_pKreuzung.end())
			{
				throw runtime_error("Die Quellekreuzung: " + sNameQ + " existiert nicht.");
			}

			if(p_pKreuzung.find(sNameZ) == p_pKreuzung.end())
			{
				throw runtime_error("Die Zielkreuzung: " + sNameZ + " existiert nicht.");
			}
			Kreuzung::vVerbinde(sNameW1, sNameW2, dLaenge, p_pKreuzung[sNameQ],  p_pKreuzung[sNameZ], eLimit, bUeberholverbot);

			if(bMitGrafik)
			{
				int iKoordinatenpaareAnzahl, k; //pairs of coord

				in >> iKoordinatenpaareAnzahl;
				int iKoordinatenZahl = 2* iKoordinatenpaareAnzahl;
				int iKoordinaten[iKoordinatenZahl];
				for (int i = 0; i < iKoordinatenZahl; i++)
				{
					in >> k;
					iKoordinaten[i] = k;
				}
				bZeichneStrasse(sNameW1,sNameW2,dLaenge,iKoordinatenpaareAnzahl,iKoordinaten);
			}
		}
		else if(sSchluesselwort == "FAHRRAD")
		{
			iZeile++;
			unique_ptr<Fahrrad> fahrrad = make_unique<Fahrrad>();
			in >> *fahrrad;

			string sNameS;
			double dLosZeit;
			in >> sNameS;
			in >> dLosZeit;

			if(p_pKreuzung.find(sNameS) == p_pKreuzung.end())
			{
				throw runtime_error("Kreuzung ist nicht da");
			}
			p_pKreuzung[sNameS]->vAnnahme(move(fahrrad),dLosZeit);
		}
		else if(sSchluesselwort == "PKW")
		{
			iZeile++;
			unique_ptr<PKW> pkw = make_unique<PKW>();
			in >> *pkw;

			string sNameS;
			double dLosZeit;
			in >> sNameS;
			in >> dLosZeit;

			if(p_pKreuzung.find(sNameS) == p_pKreuzung.end())
			{
				throw runtime_error("Kreuzung ist nicht da");
			}
			p_pKreuzung[sNameS]->vAnnahme(move(pkw),dLosZeit);
		}
		else
		{
			iZeile++;
			throw runtime_error("Schluesselwort nicht erkennbar " + sSchluesselwort);
		}
	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
	for (dGlobaleZeit = 0; dGlobaleZeit <= dDauer; dGlobaleZeit += dZeitschritt)
	{
		vSetzeZeit(dGlobaleZeit);
		for (auto &Kreuzung:p_pKreuzung)
		{
			Kreuzung.second->vSimulieren();
		}
	}
}
