#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<iostream>

#include"player.h"
#include"kostki.h"


//player

Player::Player()
{
	numer_gracza = 0;
}


int Player::wybor_kostki()
{
	return 0;
}

void Player::ustaw_numer_gracza(int numer)
{
	numer_gracza = numer;
}

int Player::ruch_gracza(Plansza *plansza)
{
	return 0;
}


ElementListy<Kostka>* Player::wybierz_element(int numer) //zwraca adres do wybranej kostki
{
	ElementListy<Kostka> *wybrana_kostka = NULL;
	ElementListy<Kostka> *pomocnicza = glowa_kostki_gracza;
	for (int i = 0; i < numer ; i++)
	{
		wybrana_kostka = pomocnicza;
		pomocnicza = pomocnicza->nastepny;
	}
	return wybrana_kostka;
}
ElementListy<Kostka>* Player::wytnij_element(int numer) //wycina element
{
	ElementListy<Kostka> *element_wycinany = wybierz_element(numer);
	ElementListy<Kostka> *element_poprzedzajacy = NULL;
	if (numer == 1)
	{
		glowa_kostki_gracza = element_wycinany->nastepny;
	}
	else
	{
		element_poprzedzajacy = wybierz_element( numer-1);
		element_poprzedzajacy->nastepny = element_wycinany->nastepny;

	}
	element_wycinany->nastepny = NULL;
	return element_wycinany;
}

void Player::wypisz_numer_gracza()
{
	cout << numer_gracza << endl;
}

bool Player::czy_gracz_wygral()
{
	if (licz_kostki_gracza() > 0)
	{
		return false;
	}
	else
	{
		cout << endl;
		cout << nazwa << ", wygrales!!!! Gratulacja wygranej!!!!" << endl;
		return true;
	}
}

void Player::dodaj_do_talii_gracza(Kostka *adres_wylosowanej)
{
	if (glowa_kostki_gracza == NULL)
	{
		glowa_kostki_gracza = new ElementListy<Kostka>(adres_wylosowanej);
	}
	else
	{
		ElementListy<Kostka> *pomocnicza = glowa_kostki_gracza;
		while (pomocnicza->nastepny != NULL)
		{
			pomocnicza = pomocnicza->nastepny;
		}
		pomocnicza->nastepny = new ElementListy<Kostka>(adres_wylosowanej);
	}
}

int Player::licz_kostki_gracza() {
	if (glowa_kostki_gracza == NULL) {
		return 0;
	} else {
		int ilosc = 1;
		ElementListy<Kostka> *pomocnicza = glowa_kostki_gracza;
		while (pomocnicza->nastepny != NULL)
		{
			pomocnicza = pomocnicza->nastepny;
			ilosc ++;
		}
		return ilosc;
	}

}

//osoba

Osoba::Osoba()
{
	cout << "Podaj nazwe uzytkownika:" << endl;
	cin >> nazwa;
	cout << "Witaj " << nazwa << "!" << endl;
}


 // 1 - dodana kostka
 // 0 nie dodana kostka
 // -1 - losuj kostke dla gracza

int Osoba::ruch_gracza(Plansza* plansza)
{
	cout << "Ruch gracza numer ";
	wypisz_numer_gracza();
	cout << nazwa << ", to Twoj ruch, wybierz jaki." << endl;
	cout << "Oto Twoja talia: ";
	wypisz_liste();
	cout << "1 Wylosuj nowa kostke | 2 Uzyj kostki ze swojej talii" << endl;
	int zacznij_ruch;
	while (scanf("%d", &zacznij_ruch) != 1 || zacznij_ruch < 1 || zacznij_ruch > 2 || getchar() != '\n')
	{
		cout << "Bledne dane. Popraw swoj wybor." << endl;
		while (getchar() != '\n')
			;
	}
	if (zacznij_ruch == 2)
	{
		int kostka = wybor_kostki();
		ElementListy<Kostka>* wybrany = wybierz_element(kostka);
		if (plansza->czy_pusta())
		{
			ElementListy<Kostka>* kostka_do_dodania = wytnij_element(kostka);
			plansza->doloz_kostke(kostka_do_dodania->dana, 'L');
			delete kostka_do_dodania;
			return 1;
		}
		else
		{
			cout << "Co chcesz zrobic z kostka?";
			wybrany->dana->wypisz_kostke_taliaU();
			cout << endl;
			cout << "1 doloz z prawej | 2 doloz z lewej" << endl;
			int funkcje_kostki;
			char strona;
			while (1)
			{
				while (scanf("%d", &funkcje_kostki) != 1 || funkcje_kostki < 1 || funkcje_kostki > 2 || getchar() != '\n')
				{
					cout << "Bledne dane. Popraw swoj wybor." << endl;
					while (getchar() != '\n')
						;
				}
				if (funkcje_kostki == 1 || funkcje_kostki == 2)
				{
					if (funkcje_kostki == 1)
					{
						strona = 'P';
					}
					if (funkcje_kostki == 2)
					{
						strona = 'L';
					}
					if (!plansza->sprawdz_ruch(wybrany->dana, strona))
					{
						cout << "Nie mozna zrobic takiego ruchu, za kare dostajesz nowa kostke." << endl;
						return 4;
					}
					else
					{
						ElementListy<Kostka>* kostka_do_dodania = wytnij_element(kostka);
						plansza->doloz_kostke(kostka_do_dodania->dana, strona);
						delete kostka_do_dodania;
						return 1;
					}
				}
			}
		}
	}
	else
	{
		return -1;
	}
	return 0;
}

int Osoba::wybor_kostki() //czlowiek wybiera kostke
{
	wypisz_liste();
	int liczba_kostek = licz_kostki_gracza();
	while (1)
	{
		int kostka;
		cout << "Wybierz kostke, ktora chcesz dolozyc" << endl;
		while (scanf("%d", &kostka) != 1 || kostka < 1 || kostka > 6 || getchar() != '\n')
		{
			cout << "Bledne dane. Popraw swoj wybor." << endl;
			while (getchar() != '\n')
				;
		}
		if (kostka > liczba_kostek)
		{
			cout << "Nie masz tylu kostek. Wybierz jeszcze raz" << endl;
		}
		else
		{
			return kostka;
		}
	}
	return 0;
}

//komputer

Komputer::Komputer()
{
	nazwa = "Komputer";
	cout << "Witaj " << nazwa << "!" << endl;
}

int Komputer::ruch_gracza(Plansza *plansza)
{
	cout << "Ruch komputera, gracz numer ";
	wypisz_numer_gracza();
	cout << endl;
	for (int i = 1; i <= licz_kostki_gracza(); i++)
	{
		ElementListy<Kostka>* zachowana=wybierz_element(i);
		if (plansza->sprawdz_ruch(zachowana->dana, 'L'))
		{
			wytnij_element(i);
			plansza->doloz_kostke(zachowana->dana, 'L');
			delete zachowana;
			return 1;
		}
		if (plansza->sprawdz_ruch(zachowana->dana, 'P'))
		{
			wytnij_element(i);
			plansza->doloz_kostke(zachowana->dana, 'P');
			delete zachowana;
			return 1;
		}
	}
	return -1;
}

void Player::wypisz_liste()
{
	if (glowa_kostki_gracza == NULL)
	{
		cout << "Brak kostek w talii gracza" << nazwa << endl;
	}
	else
	{
		ElementListy<Kostka> *pomocnicza = glowa_kostki_gracza;
		int numer = 1;
		while (pomocnicza != NULL)
		{
			cout << "   " << numer << ")";
			pomocnicza->dana->wypisz_kostke_taliaU();
			pomocnicza = pomocnicza->nastepny;
			numer++;
		}
		cout << endl;
	}
}
