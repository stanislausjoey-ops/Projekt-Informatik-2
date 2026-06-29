/*
 * Fahrzeug.h
 *
 *  Created on: Nov 7, 2025
 *      Author: hangon
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Fahrzeug {

private :
	static int p_iMaxID;
	const int p_iID;

public :
	Fahrzeug();
	Fahrzeug(const Fahrzeug&) = delete;
	Fahrzeug(const string& sName);
	Fahrzeug(const string& sName,double dMaxGeschwindigkeit);
	virtual ~Fahrzeug();
	virtual void vAusgeben(ostream& out) const;
	static void vKopf();
	virtual void vSimulieren();
	virtual double dTanken(double dMenge = 0.0);
	virtual double dGeschwindigkeit() const;
	bool operator<(const Fahrzeug& andereFahrzeug) const;
	Fahrzeug& operator=(const Fahrzeug& andereFahrzeug);

protected :
	string p_sName;
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	double p_dZeit;
};

ostream& operator <<(ostream& out,const Fahrzeug& fahrzeug);

#endif /* FAHRZEUG_H_ */
