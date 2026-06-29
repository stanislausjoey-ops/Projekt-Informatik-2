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
#include <string>
#include "Simulationsobjekt.h"
#include "Fahrzeug.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"
using namespace std;


class Weg : public Simulationsobjekt {

protected :
	double p_dLaenge;
	vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeug; //list of pointers to Fahrzeug on weg
	Tempolimit p_eTempolimit; //enum class

public:
	Weg();
	Weg(const string& sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn);
	virtual ~Weg();
	virtual void vSimulieren() override;
	virtual void vAusgeben(ostream& out) const override;
	static void vKopf() ;
	void vAnnahme(unique_ptr<Fahrzeug>); //Fahrzeug no park
	void vAnnahme(unique_ptr<Fahrzeug>,double); //Fahrzeug w park time
	unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&); //erase certain Fzg

	//Getter
	double getLaenge() const;
	double getTempolimit() const;
};

#endif /* WEG_H_ */
