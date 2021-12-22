#pragma once

//odpowiedzialna za obiekty graczy
//klasa nadrzedna ogolna Player oraz klasy dziedziczace po niej Komputer i Osoba

#include<stdio.h>
#include<string>

#include"kostki.h"
#include"plansza.h"

//ogolna klasa gracza

class Player {
public:
	string nazwa;
	Player();
	void wypisz_liste();
	virtual int wybor_kostki();
	virtual int ruch_gracza(Plansza* plansza);
	int licz_kostki_gracza();
	//gdy nikt nie wygral a kostki w talii sie skonczyly to wygrywa ten ktoremu zostalo mnie kostek
	void ustaw_numer_gracza(int numer);
	void dodaj_do_talii_gracza(Kostka *adres_wylosowanej);
	bool czy_gracz_wygral();
protected:
	ElementListy<Kostka>* glowa_kostki_gracza = NULL;
	ElementListy<Kostka>* wybierz_element(int numer);
	ElementListy<Kostka>* wytnij_element(int numer);
	void wypisz_numer_gracza();
private:
	int numer_gracza;
};

class Osoba : public Player {
public:
	Osoba();
	int ruch_gracza(Plansza* plansza);
	int wybor_kostki();
};

class Komputer : public Player {

public:
	Komputer();
	int ruch_gracza(Plansza* plansza);
};
