//opieka nad przebiegiem gry

#include<stdio.h>
#include<iostream>
#include<string>
#include<stdlib.h>

#include"kostki.h"
#include"player.h"
#include"plansza.h"

#define ILOSC_KOSTEK 28
#define LICZBA_GRACZY 2

class Domino {
public:
	Domino();
	~Domino();
	void dodaj_gracza(Player* gracz);
	int menu_w_trakcie_gry();
	bool ruchy_graczy();
	void losowanie_poczatkowe();
	bool sa_kostki_w_talii();
	void nikt_nie_wygral();
	void wypisz_tablice();
	
private:
	Plansza plansza;
    Player* gracze[LICZBA_GRACZY];
    Kostka* cala_talia[ILOSC_KOSTEK];

    void wypelnij_talie(Kostka *cala_talia[ILOSC_KOSTEK]);
    Kostka* losuj_kostke(Player *gracz);
};
//naglowki f.globalnych

void zasady_gry();

void wyjscie_z_gry();

int menu_poczatek();

int uczestnicy_gry();
