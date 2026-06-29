/*
 * main.cpp
 *
 *  Created on: Nov 7, 2025
 *      Author: Joey
 */

#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Simuclient.h"
#include "vertagt_liste.h"
#include "vertagt_aktion.h"
#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

double dGlobaleZeit;

void vAufgabe1()
{
	//statisch
	Fahrzeug f1("Auto 1");
	Fahrzeug f2("Auto 2");

	//dynamisch
	Fahrzeug* f3 = new Fahrzeug("Auto 3");
	delete f3;

	//smart pointer
	auto f4 = make_unique<Fahrzeug>("Auto 4");

	auto f5 = make_shared<Fahrzeug>("Auto 5");
	shared_ptr<Fahrzeug> f6;

	f6 = f5;
	cout << f5.use_count() << "\n";

	//vectors
	vector<unique_ptr<Fahrzeug>> v1 ;
	v1.push_back(move(f4));
	v1.clear();

	vector<shared_ptr<Fahrzeug>> v2 ;
	v2.push_back(f5);
	v2.push_back(move(f6));
	cout << f5.use_count() << "\n";

}

void vAufgabe1a()
{
	// create vector
	vector<unique_ptr<Fahrzeug>> v1;

	//get input with Name and Speed
	for (int i=0 ; i<3; i++)
	{
		string Name;
		cout << "input Name: ";
		getline(cin >> ws,Name);

		double MaxSpeed;
		cout << "input MaxGeschwindigkeit(km/h): ";
		cin >> MaxSpeed;
		v1.push_back(make_unique<Fahrzeug>(Name,MaxSpeed));
	}

	for (int i = 0; i < 5; i++)
	{
		dGlobaleZeit += 0.5;
		cout << "Global Zeit: " << dGlobaleZeit << endl;
		Fahrzeug::vKopf();
		cout << endl;
		cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
		for (auto &A : v1)
		{
			A->vSimulieren();
			A->vAusgeben(cout);
			cout<<endl;
		}
	}
}

void vAufgabe_2()
{
	vector<unique_ptr<Fahrzeug>> v1;
	int iAnzahlPKW = -1;
	int iAnzahlFahrrad = -1;

	//input PKW und Fahrrad

	do
	{
		cout << "geben Sie die Anzahl der PKW ein: " << endl;
		cin >> iAnzahlPKW;
		cout << "geben Sie die Anzahl der Fahrrad ein: " << endl;
		cin >> iAnzahlFahrrad;
	}
	while ((!(iAnzahlPKW >= 0))&&(!(iAnzahlFahrrad >= 0)));

	//create PKW
	for (int i=0; i < iAnzahlPKW; i++)
	{
		string Name;
		double dMaxGeschwindigkeit, dVerbrauch;
		cout << "geben Sie die Name der PKW " << i+1 << " ein: " << endl;
		cin >> Name;
		cout << "Maximal Geschwindigkeit (km/h) fuer  " << Name << " :" << endl;
		cin >> dMaxGeschwindigkeit;
		cout << "Verbrauch (L/100km) fuer " << Name << " :" << endl;
		cin >> dVerbrauch;
		v1.push_back(make_unique<PKW>(Name,dMaxGeschwindigkeit,dVerbrauch));
	}

	//create Fahrrad
	for (int i=0; i < iAnzahlFahrrad; i++)
	{
		string Name;
		double dMaxGeschwindigkeit;
		cout << "geben Sie die Name der Fahrrad " << i+1 << " ein: " << endl;
		cin >> Name;
		cout << "Maximal Geschwindigkeit (km/h) fuer " << Name << " :" << endl;
		cin >> dMaxGeschwindigkeit;
		v1.push_back(make_unique<Fahrrad>(Name,dMaxGeschwindigkeit));
	}

	//Simulation Aufbau
	const double dSchrittDauer = 0.5;
	const double dSimulationsDauer = 5;
	const double dToleranz = 1e-6;

	for (dGlobaleZeit = 0.0; dGlobaleZeit <= dSimulationsDauer + dToleranz; dGlobaleZeit += dSchrittDauer )
	{
		cout << "Global Zeit: " << dGlobaleZeit << endl;
		Fahrzeug::vKopf();
		for (auto& A : v1)
		{
			A->vSimulieren();
			if (fabs(dGlobaleZeit - 3.0 < dToleranz))
			{
				if(auto PKWs = dynamic_cast<PKW*>(A.get()))
				{
					PKWs->dTanken();
				}
			}
			cout << *A << endl;
		}
	}
}

void vAufgabe_3()
{
	PKW A1("BMW", 200, 50);
	PKW A2("Ferrari", 250, 60);
	Fahrrad F1("Brompton",30);

	dGlobaleZeit = 3;
	A1.vSimulieren();
	A2.vSimulieren();
	F1.vSimulieren();

	(F1<A1)? cout << "> operator funktioniert " << endl : cout << "> operator kaput" << endl;
	(A1<A2)? cout << "> operator funktioniert " << endl : cout << "> operator kaput" << endl;

	A1.vKopf();
	cout << "A1 vAusgeben() :" << A1 << endl;
	cout << "A2 vAusgeben() :" << A2 << endl;
	A2 = A1;
	cout << "A1 vAusgeben(n) :" << A1 << endl;
	cout << "A2 vAusgeben(n) :" << A2 << endl;

}


double dEpsilon = 0.001;

void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{15};
    double dTakt = 0.3;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 229, 9.6));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 24.7));
    for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}

void vAufgabe_4()
{
    // Print the header for Weg objects
    Weg::vKopf();

    // Create a Weg object (name, length, optional tempolimit)
    Weg w1("Landstrasse", 100.0, Tempolimit::Landstrasse);

    // Print the Weg using the << operator
    std::cout << w1 << std::endl;
}

void vAufgabe_5()
{
    Weg weg1("Weg1", 20.0);

    auto pFzg1 = std::make_unique<PKW>("BMW", 10.0, 5.0);
    auto pFzg3 = std::make_unique<PKW>("Audi", 8.0, 4.0);

    weg1.vAnnahme(std::move(pFzg1));
    weg1.vAnnahme(std::move(pFzg3),2.0);

    std::cout << "\nInitialer Zustand:\n";
    Weg::vKopf();
    std::cout << weg1 << std::endl;

    const double dTakt = 1.0;
    const double dDauer = 8.0;

    for (dGlobaleZeit = 0.0; dGlobaleZeit <= dDauer; dGlobaleZeit += dTakt) {
        std::cout << "\nZeit = " << dGlobaleZeit << std::endl;
        weg1.vSimulieren();
        Weg::vKopf();
        std::cout << weg1 << std::endl;
    }
}

void vAufgabe_6()
{

    Weg weg1("Hin", 500, Tempolimit::Innerorts);
    Weg weg2("Ruck",500, Tempolimit::Innerorts);
    bInitialisiereGrafik(800,500);
    int iKoordinaten[4] = {700, 250, 100, 250};

    bZeichneStrasse(weg1.getName(), weg2.getName(), 500, 2, iKoordinaten);

    auto pBMW  = make_unique<PKW>("BMW", 40, 10,300);
    auto pAudi = make_unique<PKW>("Audi",  80.0, 5);

    weg1.vAnnahme(move(pBMW));
    weg1.vAnnahme(move(pAudi), 3.0);

    auto pMercedes = make_unique<PKW>("Mercedes", 200.0, 8.0);
    auto pRad = make_unique<Fahrrad>("Fahrrad", 20);

    weg2.vAnnahme(move(pMercedes));
    weg2.vAnnahme(move(pRad));

    const double dTakt  = 0.4;
    const double dDauer = 10.0;

    for (dGlobaleZeit = 0.0; dGlobaleZeit <= dDauer; dGlobaleZeit += dTakt)
    {
        cout << "\nZeit = " << dGlobaleZeit << endl;

        vSetzeZeit(dGlobaleZeit);

        weg1.vSimulieren();
        weg2.vSimulieren();

        Weg::vKopf();
        cout << weg1 << endl;
        cout << weg2 << endl;
        vSleep(500);
    }
    vBeendeGrafik();
}

void vAufgabe_6a()
{
	int a = 1, b = 10;
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(a, b);
	vertagt::VListe<int> TestListe;

	for(int i = 0; i < 10; ++i)
	{
		int zuf = dist(device);
		TestListe.push_back(zuf);
	}
	TestListe.vAktualisieren();

	cout << "Elemente der Liste: ";
	for (auto it = TestListe.begin(); it!= TestListe.end(); it++)
	{
		cout << *it ;
	}
	cout << endl;

	for (auto it = TestListe.begin(); it!= TestListe.end(); it++)
	{
		if (*it > 5){TestListe.erase(it);}
	}

	cout << "Elemente der Liste (nach erase, vor Aktualisieren): ";
	for (auto it = TestListe.begin(); it!= TestListe.end(); it++)
	{
		cout << *it ;
	}
	cout << endl;
	TestListe.vAktualisieren();

	cout << "Elemente der Liste (nach erase und Aktualisieren): ";
	for (auto it = TestListe.begin(); it!= TestListe.end(); it++)
	{
		cout << *it;
	}
	cout << endl;

	TestListe.push_front(2);
	TestListe.push_back(6);
	TestListe.vAktualisieren();
	cout << "Elemente der Liste (nach pushback und pushfront): ";
		for (auto it = TestListe.begin(); it!= TestListe.end(); it++)
		{
			cout << *it;
		}
		cout << endl;
}

int main(){
	//vAufgabe1();
	//vAufgabe1a();
	//vAufgabe_2();
	//vAufgabe_3();
	//vAufgabe_AB1();
	//vAufgabe_4();
	//vAufgabe_5();
	vAufgabe_6();
	//vAufgabe_6a();
	return 0;
	}
