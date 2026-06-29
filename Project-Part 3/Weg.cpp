/*
 * Weg.cpp
 *
 *  Created on: Dec 1, 2025
 *      Author: Joey
 */

#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include <iomanip>
#include <iostream>
#include <string>

Weg::Weg():
	Simulationsobjekt(""),
	p_dLaenge(0.0),
	p_eTempolimit(Tempolimit::Autobahn),
	p_bUeberholverbot(true)
{
	// TODO Auto-generated constructor stub

}

Weg::Weg(const string& sName, double dLaenge, Tempolimit eTempolimit, bool bUeberholverbot, shared_ptr<Kreuzung>pZielKreuzung ):
		Simulationsobjekt(sName),
		p_dLaenge(dLaenge),
		p_eTempolimit(eTempolimit),
		p_bUeberholverbot(bUeberholverbot),
		p_pZielKreuzung(pZielKreuzung)
{

}

Weg::~Weg() {
	// TODO Auto-generated destructor stub
}


void Weg::vSimulieren()
{
	p_pFahrzeug.vAktualisieren();
	vSetSchranke(p_dLaenge);
	for (auto& fahrzeug : p_pFahrzeug)
	{
		if (!fahrzeug) continue; //check if ptr point to nothing
		try
		{
			fahrzeug->vSimulieren();
			if ((p_bUeberholverbot) && !fahrzeug->bIsNotBlocking())
			{
				vSetSchranke(fahrzeug->getAbschnittStrecke());
			}
		}
		catch (Fahrausnahme& aFahrausnahme)
		{
			aFahrausnahme.vBearbeiten();
		}
	}
	p_pFahrzeug.vAktualisieren();
	for (auto& fahrzeug : p_pFahrzeug){fahrzeug->vZeichnen(*this);}
}

void Weg::vAusgeben(ostream &out) const
{
	Simulationsobjekt::vAusgeben(out);
	out << resetiosflags(ios::left) << setiosflags(ios::right)
			<< setw(10) << p_dLaenge
			<< setw(10);
	out << "( ";
	for(auto& fahrzeug :p_pFahrzeug)
	{
		out << fahrzeug->getName() << " " ;
	}
	out << ")";
}

void Weg::vKopf(){
	Simulationsobjekt::vKopf();
	cout << setw(20) << "| Laenge"
		<< setw(15) << "| Fahrzeug" << endl;
	cout << setfill('-') << setw(50) << "-" << setfill(' ') << endl;
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFzg)
{
	pFzg->vNeueStrecke(*this);
	p_pFahrzeug.push_back(move(pFzg));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFzg ,double dStartZeit)
{
	pFzg->vNeueStrecke(*this, dStartZeit);
	p_pFahrzeug.push_front(move(pFzg));
}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

double Weg::getTempolimit() const
{
	return (double)(p_eTempolimit);
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fzg)
{
	for (auto it = p_pFahrzeug.begin(); it!= p_pFahrzeug.end(); ++it)
	{
		if((*it != nullptr) && **it == fzg)
		{
			unique_ptr<Fahrzeug> pLokalPointer = move(*it);
			p_pFahrzeug.erase((it));
			return pLokalPointer;
		}
	}
	return nullptr;
}

bool Weg::bUeberholverbot() const
{
	return p_bUeberholverbot;
}

double Weg::dGetSchranke() const
{
	if(p_bUeberholverbot) return p_dVirtuelleSchranke;
	else return p_dLaenge;
}

void Weg::vSetSchranke(double dSetSchranke)
{
	p_dVirtuelleSchranke = dSetSchranke;
}

shared_ptr<Weg> Weg::pGetRueckweg() const
{
	return p_pRueckweg.lock();
}

shared_ptr<Kreuzung> Weg::pGetZielKreuzung() const
{
	return p_pZielKreuzung.lock();
}

void Weg::vSetRueckweg(shared_ptr<Weg> pRueckweg)
{
	p_pRueckweg = pRueckweg;
}
