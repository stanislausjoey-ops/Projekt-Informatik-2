/*
 * Fahrzeug.h
 *
 *  Created on: Nov 7, 2025
 *      Author: Joey
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>
#include "Simulationsobjekt.h"
#include "Verhalten.h"
using namespace std;

class Weg;


class Fahrzeug : public Simulationsobjekt {

private :

public :
	Fahrzeug();
	Fahrzeug(const Fahrzeug&) = delete;
	Fahrzeug(const string& sName);
	Fahrzeug(const string& sName,double dMaxGeschwindigkeit);
	virtual ~Fahrzeug();
	virtual void vAusgeben(ostream& out) const override;
	static void vKopf();
	virtual void vSimulieren() override;
	virtual double dTanken(double dMenge = 0.0);
	virtual double dGeschwindigkeit() const;
	bool operator<(const Fahrzeug& andereFahrzeug) const;
	Fahrzeug& operator=(const Fahrzeug& andereFahrzeug);
	void vNeueStrecke(Weg&);
	void vNeueStrecke(Weg&, double);
	virtual void vZeichnen(Weg& weg) const;

	//getter
	double getAbschnittStrecke() const;

protected :
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	unique_ptr<Verhalten> p_pVerhalten;
	double p_dAbschnittStrecke;
};

//ostream& operator <<(ostream& out,const Fahrzeug& fahrzeug);

#endif /* FAHRZEUG_H_ */
