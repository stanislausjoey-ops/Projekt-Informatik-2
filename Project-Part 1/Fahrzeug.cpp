/*
 * Fahrzeug.cpp
 *
 *  Created on: Nov 7, 2025
 *      Author: Joey
 */

#include "Fahrzeug.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int Fahrzeug::p_iMaxID = 0;
extern double dGlobaleZeit;

Fahrzeug::Fahrzeug()
: p_iID(++p_iMaxID),
  p_sName(""),
  p_dMaxGeschwindigkeit(0.0),
  p_dGesamtStrecke(0.0),
  p_dGesamtZeit(0.0),
  p_dZeit(0.0)
		{
		cout <<"Fahrzeug erzeugt." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
		}

Fahrzeug::Fahrzeug(const string& sName)
: p_iID(++p_iMaxID),
  p_sName(sName),
  p_dMaxGeschwindigkeit(0.0),
  p_dGesamtStrecke(0.0),
  p_dGesamtZeit(0.0),
  p_dZeit(0.0)
	{
	cout <<"Fahrzeug erzeugt." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
	}

Fahrzeug::Fahrzeug(const string& sName, double dMaxGeschwindigkeit)
: p_iID(++p_iMaxID),
  p_sName(sName),
  p_dMaxGeschwindigkeit((dMaxGeschwindigkeit>0.0)? dMaxGeschwindigkeit : 0.0),
  p_dGesamtStrecke(0.0),
  p_dGesamtZeit(0.0),
  p_dZeit(0.0)
  	{
	cout <<"Fahrzeug erzeugt." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
	}

Fahrzeug::~Fahrzeug(){
	cout <<"Fahrzeug geloescht." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
}

void Fahrzeug::vAusgeben(ostream& out) const {
	cout << resetiosflags(ios::left) << setiosflags(ios::right)
			<< setw(5) << p_iID
			<< setw(10) << p_sName
			<< setw(30) << dGeschwindigkeit()
			<< setw(20) << p_dGesamtStrecke;
}

void Fahrzeug::vKopf() {
	cout << setw(5) << "ID"
	<< setw(10) << "Name"
	<< setw(30) << "MaxGeschwindigkeit(km/h)"
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

	double dZeitDiff = dGlobaleZeit - p_dZeit;

	p_dGesamtStrecke += dZeitDiff * dGeschwindigkeit();
	p_dGesamtZeit += dZeitDiff;
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

ostream& operator <<(ostream& out,const Fahrzeug& fahrzeug)
{
	fahrzeug.vAusgeben(out);
	return out;
}

bool Fahrzeug::operator<(const Fahrzeug& andereFahrzeug) const
{
	return (p_dGesamtStrecke < andereFahrzeug.p_dGesamtStrecke);
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& Fahrzeug)
{
	p_sName = Fahrzeug.p_sName;
	p_dMaxGeschwindigkeit = Fahrzeug.p_dMaxGeschwindigkeit;

	return *this;
}
