#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>

#include"domino.h"
#include"plansza.h"
#include"kostki.h"
#include"player.h"

using namespace std;

Domino::Domino()
{
	for(int i=0;i<LICZBA_GRACZY;i++)
	{
		gracze[i]=NULL;
	}
	wypelnij_talie(cala_talia);
}
Domino::~Domino() {
	cout << "Resetuje gre..." << endl;
	for (int i = 0; i < LICZBA_GRACZY; i++)
	{
		delete gracze[i];
	}
	for (int i = 0; i < ILOSC_KOSTEK; i++)
	{
		delete cala_talia[i];
	}
	cout << "--------------------------------------------------------------------------------------------" << endl;
}


void Domino::dodaj_gracza(Player* nowy_gracz)
{
	for(int i=0;i<LICZBA_GRACZY;i++)
	{
		if(gracze[i]==NULL) {
			gracze[i]=nowy_gracz;
			nowy_gracz->ustaw_numer_gracza(i+1);
			return;
		}
	}
}

void Domino::wypelnij_talie(Kostka *cala_talia[ILOSC_KOSTEK])
{
	fstream InFile;
	InFile.open("domino.txt", ios::in);
	if (InFile.is_open())
	{
		string line;
		for (int i = 0; i < ILOSC_KOSTEK; i++)
		{
			getline(InFile, line);
			int lewy;
			int prawy;
			sscanf(line.c_str(), "%d %d", &lewy, &prawy);
			cala_talia[i] = new Kostka(lewy, prawy, "Nikt");
		}
	}
	else
	{
		cout << "Blad odczytu z pliku" << endl;
		exit(1);
	}
	InFile.close();
}

int Domino::menu_w_trakcie_gry()
{
	cout << endl << endl;
	cout << "Zdecyduj:";
	cout << " Kolejny ruch wybierz 1 | Przerwij gre wybierz 2" << endl;
	int wybor = 0;
	while (scanf("%d", &wybor) != 1 || wybor < 1 || wybor > 2 || getchar() != '\n')
	{
		cout << "Bledne dane. Popraw swoj wybor." << endl;
		while (getchar() != '\n')
			;
	}
	if (wybor == 2)
	{
		int opcja;
		cout << "Zagraj ponownie wybierz 1 | Koniec programu wybierz 2 " << endl;
		while (scanf("%d", &opcja) != 1 || opcja < 1 || opcja > 2 || getchar() != '\n')
		{
			cout << "Bledne dane. Popraw swoj wybor." << endl;
			while (getchar() != '\n')
				;
		}
		if (opcja == 1)
		{
			return 3;
		}
		else
		{
			wyjscie_z_gry();
		}
	}
	return wybor;
}

bool Domino::ruchy_graczy()
{
	system("CLS");
	plansza.wypisz_weza();
	int brak_kostek = 0;
	for (int i=0; i<LICZBA_GRACZY; i++)
	{
		if(gracze[i]!=NULL)
		{
			cout << endl;
			int wynik_ruchu = gracze[i]->ruch_gracza(&plansza);
			// sprawdzenie ilości kostek i ew. losowanie
			if(wynik_ruchu==-1)
			{
				if (sa_kostki_w_talii())
				{
					losuj_kostke(gracze[i]);
				}
				else
				{
					cout << "Brak wolnych kostek w talii. Tracisz mozliwosc ruchu." << endl;
					brak_kostek++;
				}
			}
			if (gracze[i]->czy_gracz_wygral())
			{
				return true;
			}
		}
	}
	if (brak_kostek == LICZBA_GRACZY)
	{
		nikt_nie_wygral();
		return true;
	}
	return false;
}

void Domino::losowanie_poczatkowe()//losuje dla kazdego gracza po 6 kostek i dodaje czlony do listy jednokierunkowej
{
	for (int n = 0; n < LICZBA_GRACZY; n++)
	{
		if(gracze[n]!=NULL)
		{	
			for (int i = 0; i < 6; i++)
			{
				losuj_kostke(gracze[n]);
			}
		}
	}
}

bool Domino::sa_kostki_w_talii()
{
	for (int i = 0; i < ILOSC_KOSTEK; i++)
	{
		if (cala_talia[i]->do_kogo_nalezy == "Nikt")
		{
			return true;
		}
	}
	return false;
}


void Domino::nikt_nie_wygral()
{
	cout << endl;
	cout << "W tej rozgrywce nikt nie wygral :( :( :(" << endl;

	for (int i = 0; i < LICZBA_GRACZY; i++)
	{
		cout << "Gracz o nazwie " << gracze[i]->nazwa << ", numer gracza " << i + 1 << " konczy z liczba kostek: " << gracze[i]->licz_kostki_gracza() << endl;
	}
}

Kostka* Domino::losuj_kostke(Player *gracz)
{
	srand((unsigned) time(NULL));
	while (1)
	{
		int x = rand() % 28;
		if (cala_talia[x]->do_kogo_nalezy == "Nikt")
		{
			cala_talia[x]->do_kogo_nalezy = gracz->nazwa;
			gracz->dodaj_do_talii_gracza(cala_talia[x]);
			return cala_talia[x];
		}
	}
}

void Domino::wypisz_tablice()
{
	for (int i = 0; i < 28; i++)
	{
		cala_talia[i]->wypisz_kostke();
	}
}


void zasady_gry()
{
	cout << "\t\t\t\tWitaj w grze w domino!" << endl;
	cout << "\tAutorka gry jest Dorota Siciak, studentka I roku informatyki na UKSW" << endl;
	cout << "Zasady gry sa nastepujace:" << endl;
	cout << "Na poczatku kazdy z graczy otrzymuje po 6 kostek domina.\n" <<
		"Gracz rozpoczynajacy decyduje o umieszczeniu pierwszej kostki na planszy.\n" <<
		"Nastepnie kazdy z graczy doklada z prawej badz lewej strony kostke ze swojej talii \n" <<
		"majaca na jednej z polowek taka sama liczbe oczek jak polowka kostki umieszczonej na planszy.\n" <<
		"W przypadku braku pasujacych kostek we wlasnej talii gracz moze poprosic o wylosowanie nowej kostki.\n" <<
		"W przypadku blednie podjetej decyzji nowa kostka losowana jest automatycznie.\n" <<
		"Wygrywa gracz, ktory jako pierwszy pozbedzie sie wszystkich kostek.\n" <<
		"Mozliwa jest sytuacja remisu, gdy nikt nie pozbedzie sie wszystkich kostek.\n" <<
		"W takim wypadku program konczac wyswietla informacje, kto z jaka iloscia kostek konczy." << endl<<endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
}

void wyjscie_z_gry()
{
	cout << endl;
	cout << "Miej sie dobrze! Do zobaczenia ponownie! :) " << endl;
	cout << "Koncze prace programu." << endl;
	exit(0);
}

int menu_poczatek()
{
	cout << "Nowa gra nacisnij 1  |  Wyjscie z programu nacisnij 2" << endl;
	int wybor;
	while (scanf("%d", &wybor) != 1 || wybor < 1 || wybor > 2 || getchar() != '\n')
	{
		cout << "Bledne dane. Popraw swoj wybor." << endl;
		while (getchar() != '\n')
			;
	}
	if (wybor == 2)
	{
		wyjscie_z_gry();
	}
	else
	{
		return wybor;
	}
}

int uczestnicy_gry()
{
	cout << "Kto z kim bedzie gral?" << endl;
	cout << "Czlowiek z czlowiekiem 1\n" << "Czlowiek z komputerem 2\n" << "Komputer z komputerem 3" << endl;
	int wybor;
	while (scanf("%d", &wybor) != 1 || wybor < 1 || wybor > 3 || getchar() != '\n')
	{
		cout << "Bledne dane. Popraw swoj wybor." << endl;
		while (getchar() != '\n')
			;
	}
	return wybor;
}