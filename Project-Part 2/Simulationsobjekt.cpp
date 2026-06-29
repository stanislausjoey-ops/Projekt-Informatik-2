/*
 * Simulationsobjekt.cpp
 *
 *  Created on: Nov 31 , 2025
 *      Author: Joey
 */

#include "Simulationsobjekt.h"
#include <iostream>
#include <iomanip>
using namespace std;

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt():
	p_sName(""),
	p_iID(++p_iMaxID),
	p_dZeit(0.0)
		{
	//cout <<"Objekt erzeugt." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
}


Simulationsobjekt::Simulationsobjekt(const string &name):
	p_sName(name),
	p_iID(++p_iMaxID),
	p_dZeit(0.0)
		{
	//cout <<"Objekt erzeugt." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
}

Simulationsobjekt::~Simulationsobjekt() {
	cout <<"Objekt geloescht." << " |ID: " << p_iID << " |Name: " << p_sName << "\n";
}

void Simulationsobjekt::vAusgeben(ostream& out) const {
	out << resetiosflags(ios::left) << setiosflags(ios::right)
					<< setw(5) << p_iID
					<< setw(15) << p_sName;
	out << " : ";

}

void Simulationsobjekt::vKopf(){
	cout << "ID"
		<< setw(10) << "| Name";
//	cout << setfill('-') << setw(15) << setfill('  ') << endl;
}

string Simulationsobjekt::getName() const
{
	return p_sName;
}

double Simulationsobjekt::getZeit() const
{
	return p_dZeit;
}

ostream& operator <<(ostream& out,const Simulationsobjekt& obj)
{
	obj.vAusgeben(out);
	return out;
}

bool Simulationsobjekt::operator == (const Simulationsobjekt& obj) const
{
	return p_iID == obj.p_iID;
}
