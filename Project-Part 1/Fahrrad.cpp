/*
 * Fahrrad.cpp
 *
 *  Created on: Nov 7, 2025
 *      Author: stani
 */

#include "Fahrrad.h"
#include <cmath>
using namespace std;


Fahrrad::Fahrrad(const string& sName, double dMaxGeschwindigkeit)
:Fahrzeug(sName,dMaxGeschwindigkeit) {
	// TODO Auto-generated constructor stub

}

Fahrrad::~Fahrrad() {
	// TODO Auto-generated destructor stub
}

double Fahrrad::dGeschwindigkeit() const
{
	double dAbnahme = floor(p_dGesamtStrecke / 20);
	double dGeschwindigkeitNeu = p_dMaxGeschwindigkeit * ( pow(0.9,dAbnahme));
	return max(dGeschwindigkeitNeu,12.0);
}
