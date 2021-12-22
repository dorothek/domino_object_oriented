#include<iostream>
#include<stdio.h>
#include"kostki.h"

using namespace std;

Kostka::Kostka()
{
	lewy_numer = 0;
	prawy_numer = 0;
	do_kogo_nalezy = "Nikt";
}

Kostka::Kostka(int lewy, int prawy, string czyja)
{
	do_kogo_nalezy = czyja;
	lewy_numer = lewy;
	prawy_numer = prawy;
}

int Kostka::get_lewy_numer()
{
	return lewy_numer;
}

int Kostka::get_prawy_numer()
{
	return prawy_numer;
}

string Kostka::get_do_kogo_nalezy()
{	
	return do_kogo_nalezy;
}

void Kostka::set_lewy_numer(int value)
{
	lewy_numer = value;
}

void Kostka::set_prawy_numer(int value)
{
	prawy_numer = value;
}

void Kostka::set_do_kogo_nalezy(string value)
{
	do_kogo_nalezy = value;
}

void Kostka::obracaj()
	{
		int pom = lewy_numer;
		lewy_numer = prawy_numer;
		prawy_numer = pom;
	}

	void Kostka::wypisz_kostke()
	{
		cout << "[" << lewy_numer << "|" << prawy_numer << "]" << "Nalezy do: " << do_kogo_nalezy << endl;
	}
	void Kostka::wypisz_kostke_taliaU()
	{
		cout << "[" << lewy_numer << "|" << prawy_numer << "]";
	}
