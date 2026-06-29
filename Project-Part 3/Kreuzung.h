/*
 * Kreuzung.h
 *
 *  Created on: Jan 27, 2026
 *      Author: Joey
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include <iostream>
#include <list>
#include <string>
#include <memory>
using namespace std;

class Weg;
class Fahrzeug;

class Kreuzung: public Simulationsobjekt {

private:
	list<shared_ptr<Weg>> p_pWege;
	double p_dTankstelle;

public:
	Kreuzung(string = "" , double dTankstelle = 0.0);
	virtual ~Kreuzung();
	static void vVerbinde(string sHinweg, string sRueckweg, double dLaenge,
			shared_ptr<Kreuzung> pStart, shared_ptr<Kreuzung> pZiel, Tempolimit eTempolimit,
			bool bUeberholverbot);
	void vTanken(Fahrzeug&);
	void vAnnahme(unique_ptr<Fahrzeug>, double);
	void vSimulieren();
	shared_ptr<Weg>pZufaelligerWeg(Weg&);
	double dGetTankstelle();
	void vEinlesen(istream& in) override;
	void vAusgeben(ostream& out) const override;
};

#endif /* KREUZUNG_H_ */
