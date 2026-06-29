/*
 * Weg.h
 *
 *  Created on: Dec 1, 2025
 *      Author: Joey
 */

#ifndef WEG_H_
#define WEG_H_

#include <string>
#include <list>
#include <memory>
#include "Simulationsobjekt.h"
#include "Fahrzeug.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"
using namespace std;

class Fahrzeug;
class Kreuzung;

class Weg : public Simulationsobjekt {

protected :
	double p_dLaenge;
	vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeug;
	Tempolimit p_eTempolimit;
	bool p_bUeberholverbot;
	double p_dVirtuelleSchranke  = 0;
	const weak_ptr<Kreuzung> p_pZielKreuzung;
	weak_ptr<Weg> p_pRueckweg;

public:
	Weg();
	Weg(const string& sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn, bool bUeberholverbot = true,
			shared_ptr<Kreuzung>pZielKreuzung = nullptr);
	virtual ~Weg();
	virtual void vSimulieren() override;
	virtual void vAusgeben(ostream& out) const override;
	static void vKopf() ;
	void vAnnahme(unique_ptr<Fahrzeug>);
	void vAnnahme(unique_ptr<Fahrzeug>,double);
	unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);
	void vSetSchranke(double);
	void vSetRueckweg(shared_ptr<Weg>);

	//Getter
	double getLaenge() const;
	double getTempolimit() const;
	bool bUeberholverbot() const;
	double dGetSchranke() const;
	shared_ptr<Weg> pGetRueckweg() const;
	shared_ptr<Kreuzung> pGetZielKreuzung() const;
};

#endif /* WEG_H_ */
