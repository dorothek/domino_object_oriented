#pragma once

//odpowiedzialna za obiekty kostek domina

#include<stdio.h>
#include<string>

using namespace std;

template<class TYP>
class ElementListy{
public:
	TYP *dana;
	template<class T> ElementListy(T * t)
	{
		dana=t;
		nastepny = NULL; //prawy
		poprzedni = NULL; //lewy
	}
	ElementListy *nastepny; //prawy
	ElementListy *poprzedni; //lewy
};


class Kostka
{
private:
	int lewy_numer;
	int prawy_numer;

public:
	string do_kogo_nalezy;

	Kostka();
	Kostka(int lewy, int prawy, string czyja);

	int get_lewy_numer();
	int get_prawy_numer();
	string get_do_kogo_nalezy();
	void set_lewy_numer(int value);
	void set_prawy_numer(int value);
	void set_do_kogo_nalezy(string value);

	void obracaj();
	void wypisz_kostke();
	void wypisz_kostke_taliaU();
};
