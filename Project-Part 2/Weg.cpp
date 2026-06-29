/*
 * Weg.cpp
 *
 *  Created on: Dec 1, 2025
 *      Author: Joey
 */

#include "Weg.h"
//#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include <iomanip>
#include <iostream>
#include <string>

Weg::Weg():
	Simulationsobjekt(""),
	p_dLaenge(0.0),
	p_eTempolimit(Tempolimit::Autobahn) {
	// TODO Auto-generated constructor stub

}

Weg::Weg(const string& sName, double dLaenge, Tempolimit eTempolimit):
		Simulationsobjekt(sName),
		p_dLaenge(dLaenge),
		p_eTempolimit(eTempolimit)
{

}

Weg::~Weg() {
	// TODO Auto-generated destructor stub
}


void Weg::vSimulieren()
{
	p_pFahrzeug.vAktualisieren(); //ensure uptodate before interate
	for (auto& fahrzeug : p_pFahrzeug) //gothru each ele of the list
	{
		if (!fahrzeug) continue; //nullptr
		try
		{
			fahrzeug->vSimulieren();
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
	p_pFahrzeug.push_front(move(pFzg)); //parken am weitesten auf Weg fahrend am Weganfang
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
