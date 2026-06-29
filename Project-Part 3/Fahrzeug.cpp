/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 7, 2025
 *      Author: Joey
 */

#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

extern double dGlobaleZeit;

Fahrzeug::Fahrzeug()
: Simulationsobjekt(""),
  p_dMaxGeschwindigkeit(0.0),
  p_dGesamtStrecke(0.0),
  p_dGesamtZeit(0.0),
  p_dAbschnittStrecke(0.0)
  //p_dZeit(0.0)
		{
		cout <<"Fahrzeug erzeugt." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
		}

Fahrzeug::Fahrzeug(const string& sName)
: Simulationsobjekt(sName),
  p_dMaxGeschwindigkeit(0.0),
  p_dGesamtStrecke(0.0),
  p_dGesamtZeit(0.0),
  p_dAbschnittStrecke(0.0)
	{
	cout <<"Fahrzeug erzeugt." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
	}

Fahrzeug::Fahrzeug(const string& sName, double dMaxGeschwindigkeit)
: Simulationsobjekt(sName),
  p_dMaxGeschwindigkeit((dMaxGeschwindigkeit>0.0)? dMaxGeschwindigkeit : 0.0),
  p_dGesamtStrecke(0.0),
  p_dGesamtZeit(0.0),
  p_dAbschnittStrecke(0.0)
  	{
	cout <<"Fahrzeug erzeugt." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
	}

Fahrzeug::~Fahrzeug(){
}

void Fahrzeug::vAusgeben(ostream& out) const {
	Simulationsobjekt::vAusgeben(out);
	out << resetiosflags(ios::left) << setiosflags(ios::right)
			<< setw(10) << dGeschwindigkeit()
			<< setw(25) << p_dGesamtStrecke;
}

void Fahrzeug::vKopf() {
	Simulationsobjekt::vKopf();
	cout << setw(30) << "MaxGeschwindigkeit(km/h)"
	<< setw(20) << "Gesamtstrecke(km)"
	<< setw(20) << "Tankinhalt(L)"
	<< setw(20) << "Gesamtverbrauch(L)"
	<< endl;
	cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;

}

void Fahrzeug::vSimulieren(){
	if (dGlobaleZeit <= p_dZeit)
	{
		return;
	}

	double dT = dGlobaleZeit - p_dZeit;

//	p_dGesamtStrecke += dZeitDiff * dGeschwindigkeit();
	double dTeilStrecke = p_pVerhalten->dStrecke(*this, dT);
	p_dGesamtStrecke += dTeilStrecke;
	p_dAbschnittStrecke += dTeilStrecke;
	p_dGesamtZeit += dT;
	p_dZeit = dGlobaleZeit;

}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

bool Fahrzeug::operator<(const Fahrzeug& andereFahrzeug) const
{
	return (p_dGesamtStrecke < andereFahrzeug.p_dGesamtStrecke);
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& Fahrzeug)
{
	//p_sName = Fahrzeug.p_sName;
	p_dMaxGeschwindigkeit = Fahrzeug.p_dMaxGeschwindigkeit;

	return *this;
}

void Fahrzeug::vNeueStrecke(Weg& weg)
{
	p_pVerhalten = make_unique<Fahren>(weg);
	p_dAbschnittStrecke = 0.0;
}

void Fahrzeug::vNeueStrecke(Weg& weg, double dStartZeit)
{
	p_pVerhalten = make_unique<Parken>(weg, dStartZeit);
	p_dAbschnittStrecke = 0.0;
}

double Fahrzeug::getAbschnittStrecke() const{
	return p_dAbschnittStrecke;
}

void Fahrzeug::vZeichnen(Weg& aWeg) const
{

}

bool Fahrzeug::bIsNotBlocking() const
{
	return false;
}

void Fahrzeug::vEinlesen(istream& in)
{
	Simulationsobjekt::vEinlesen(in);
	in >> p_dMaxGeschwindigkeit;
}
