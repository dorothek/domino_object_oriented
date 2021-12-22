#include "plansza.h"
#include"kostki.h"

Plansza::Plansza()
{
	poczatek = NULL;
}

void Plansza::doloz_kostke(Kostka *kostka, char strona)
{
	if (poczatek == NULL)
	{
		poczatek = new ElementListy<Kostka>(kostka);
		cout << "Pomyslnie dodano pierwszy element" << endl;
		wypisz_weza();
	}
	else
	{
		if (strona == 'P')
		{
			ElementListy<Kostka> *pom = poczatek;
			while (pom->nastepny != NULL)
			{
				pom = pom->nastepny;
			}
			if (pom->dana->get_prawy_numer() != kostka->get_lewy_numer())
			{
				kostka->obracaj();
			}
			pom->nastepny = new ElementListy<Kostka>(kostka);
			pom->nastepny->poprzedni = pom;
			wypisz_weza();
			cout << "Pomyslnie dodano element z prawej strony" << endl;
		}
		else
		{
			if (poczatek->dana->get_lewy_numer()!=kostka->get_prawy_numer())
			{
				kostka->obracaj();
			}
			ElementListy<Kostka> *pom = new ElementListy<Kostka>(kostka);
			poczatek->poprzedni = pom;
			pom->nastepny = poczatek;
			poczatek = pom;
			wypisz_weza();
			cout << "Pomyslnie dodano element z lewej strony" << endl;
		}
	}
}

bool Plansza::sprawdz_ruch(Kostka* wybrana_kostka, char strona)
{
		if(poczatek==NULL) {
			return true;
		}
		ElementListy<Kostka>* glowa_weza = poczatek;
		if (strona == 'P')
		{
			while (glowa_weza->nastepny != NULL)
			{
				glowa_weza = glowa_weza->nastepny;
			}
			if ((glowa_weza->dana->get_prawy_numer() == wybrana_kostka->get_lewy_numer()) || (glowa_weza->dana->get_prawy_numer()==wybrana_kostka->get_prawy_numer()))
			{
				return true;
			}
		}
		else
		{
			if ((glowa_weza->dana->get_lewy_numer() == wybrana_kostka->get_prawy_numer()) || (glowa_weza->dana->get_lewy_numer()==wybrana_kostka->get_lewy_numer()))
			{
				return true;
			}
		}
		return false;
}

void Plansza::wypisz_weza()
{
	ElementListy<Kostka> *pom = poczatek;
	cout << "Stan weza: ";
	if (pom == NULL)
	{
		cout << "Pusta plansza";
	}
	else
	{
		while (pom != NULL)
		{
			pom->dana->wypisz_kostke_taliaU();
			pom = pom->nastepny;
		}
	}
	cout << endl;

}

bool Plansza::czy_pusta()
{
	if (poczatek == NULL)
	{
		return true;
	}
	return false;
}
