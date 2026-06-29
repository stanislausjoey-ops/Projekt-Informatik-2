/*
 * Simulationsobjekt.h
 *
 *  Created on: Nov 31, 2025
 *      Author: Joey
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>

using namespace std;

class Simulationsobjekt {

private :


protected:
	string p_sName;
	int p_iID;
	double p_dZeit;
	static int p_iMaxID;

public:
	Simulationsobjekt();
	Simulationsobjekt(const string &sName);
	virtual ~Simulationsobjekt();
	Simulationsobjekt(const Simulationsobjekt&) = delete; //prevent copied obj

	virtual void vAusgeben(ostream& out) const;
	virtual void vSimulieren()=0;
	static void vKopf();

	//getters
	string getName() const;
	double getZeit() const;

	bool operator==(const Simulationsobjekt& obj) const;

};

ostream& operator <<(ostream& out,const Simulationsobjekt& obj);

#endif /* SIMULATIONSOBJEKT_H_ */
