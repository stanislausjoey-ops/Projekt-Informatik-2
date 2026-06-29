/*
 * Simulation.h
 *
 *  Created on: Jan 28, 2026
 *      Author: Joey
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "Simulationsobjekt.h"
#include "Kreuzung.h"
#include <map>
#include <string>
#include <memory>
#include <iostream>
using namespace std;

class Simulation {
private:
	map<string,shared_ptr<Kreuzung>> p_pKreuzung;  //map find kreuzung b name (string)

public:
	Simulation();
	virtual ~Simulation();
	void vEinlesen(istream& in, bool bMitGrafik = false);
	void vSimulieren(double dDauer, double dZeitschritt);
};

#endif /* SIMULATION_H_ */
