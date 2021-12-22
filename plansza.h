#pragma once
//opieka nad wezem ukladanym na planszy

#include<iostream>
#include"kostki.h"


class Plansza{
public:
	ElementListy<Kostka>* poczatek;
	Plansza();
	void doloz_kostke(Kostka* element, char strona);
	bool sprawdz_ruch(Kostka* wybrana_kostka, char strona);
	void wypisz_weza();
	bool czy_pusta();
};
