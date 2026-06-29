/*
 * Streckenende.cpp
 *
 *  Created on: Dec 3, 2025
 *      Author: Joey
 */

#include "Streckenende.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include <iostream>

extern double dGlobaleZeit;

Streckenende::Streckenende(Fahrzeug& fzg, Weg& weg)
: Fahrausnahme(fzg,weg)
{
	// TODO Auto-generated constructor stub

}

Streckenende::~Streckenende() {
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten() const
{
	cout <<"Streckenende: " << p_rFahrzeug.getName() << " Weg: " << p_rWeg.getName() << endl;
	//p_rWeg.pAbgabe(p_rFahrzeug);

	shared_ptr<Kreuzung> pKreuzung = p_rWeg.pGetZielKreuzung();
	unique_ptr<Fahrzeug> pFzg = p_rWeg.pAbgabe(p_rFahrzeug); //remove from that weg
	if (pKreuzung)
	{
	shared_ptr<Weg> pNeuerWeg = pKreuzung->pZufaelligerWeg(p_rWeg);

	pKreuzung->vTanken(*pFzg); //refuel
	cout <<"ZEIT	 : " << dGlobaleZeit << endl;
	cout <<"KREUZUNG : " << pKreuzung->getName() << " " << pKreuzung->dGetTankstelle() << endl;
	cout <<"WECHSEL  : " << p_rWeg.getName() << " -> " << pNeuerWeg->getName() << endl;
	cout <<"FAHRZEUG : " << endl;
	pFzg->vKopf();
	pFzg->vAusgeben(cout);
	cout << endl << endl;

	pNeuerWeg->vAnnahme(move(pFzg), dGlobaleZeit);
	}
}
