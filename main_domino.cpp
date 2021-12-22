#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>

#include"domino.h"
#include"kostki.h"
#include"player.h"

using namespace std;

int main()
{
	zasady_gry();
	while (1)
	{
		int opcja = menu_poczatek();
		Domino* domino = new Domino();
		if (opcja == 1) //nowa gra
		{
			int jacy_gracze = uczestnicy_gry();
			if (jacy_gracze == 1)
			{
				domino->dodaj_gracza(new Osoba());
				domino->dodaj_gracza(new Osoba());
			}
			if (jacy_gracze == 2)
			{
				domino->dodaj_gracza(new Osoba());
				domino->dodaj_gracza(new Komputer());
			}
			if (jacy_gracze == 3)
			{
				domino->dodaj_gracza(new Komputer());
				domino->dodaj_gracza(new Komputer());
			}
			domino->losowanie_poczatkowe();
		}
		while (1)
		{
			int menu = domino->menu_w_trakcie_gry();
			if (menu == 1)
			{
				if (domino->ruchy_graczy())
				{
					break;
				}
			}
			if (menu == 3)
			{
				break;
			}
		}
		delete domino;
	}
	return 0;
}
