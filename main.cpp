#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
};

string konwerjsaIntNaString (int liczba)
{
    ostringstream ss;
    ss << liczba;
    string lancuch = ss.str();
    return lancuch;
}

void rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string nazwaUzytkownika, hasloUzytkownika;
    int idUzytkownika;
    string liniaZDanymiUzytkownika = "";
    Uzytkownik Osoba;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        while(itr -> nazwa == nazwaUzytkownika)
        {
            cout << "Taki uztkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwaUzytkownika;
        }
    }

    cout << "Podaj haslo: ";
    cin >> hasloUzytkownika;

    if (uzytkownicy.empty() == true)  // je¿eli ksia¿ka adresowa jest pusta
    {
        Osoba.idUzytkownika = 1;           // to nowy adresat ma id=1
    }
    else
    {
        Osoba.idUzytkownika = uzytkownicy.back().idUzytkownika + 1; // w przeciwnym przypadku pobierz id ostatniej osoby z ksi¹¿ki adresowej i zwiêksz wartoœæ o jeden.
    }

    Osoba.nazwa = nazwaUzytkownika;
    Osoba.haslo = hasloUzytkownika;

    uzytkownicy.push_back(Osoba);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> idUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr -> nazwa + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
    }
    cout<< "Konto zalozone." <<endl;
    Sleep(1000);
}

void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int iloscUzytkownikow = 0;
    fstream plik;
    Uzytkownik pusty;

    uzytkownicy.clear();
    plik.open("Uzytkownicy.txt",ios::in); // aby otworzyc plik do odczytu
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
            uzytkownicy.push_back(pusty);
            iloscUzytkownikow++;
            ileZnakowWyjac = 0;
            poczatek = 0;
            iloscPionowychKresek = 0;

            for (int i = 0; i < linia.size(); i++)
            {
                ileZnakowWyjac = i - poczatek;
                if (linia[i] == '|')
                {
                    iloscPionowychKresek++;
                    wyraz = linia.substr (poczatek,ileZnakowWyjac);
                    switch (iloscPionowychKresek)
                    {
                    case 1:
                        uzytkownicy[iloscUzytkownikow - 1].idUzytkownika = atoi(wyraz.c_str());
                        break;
                    case 2:
                        uzytkownicy[iloscUzytkownikow - 1].nazwa = wyraz;
                        break;
                    case 3:
                        uzytkownicy[iloscUzytkownikow - 1].haslo = wyraz;
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }
        }
        plik.close();
    }
}


int logowanieUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string nazwaUzytkownika, hasloUzytkownika;
    bool znalezionyUzytkownik = 0;
    int proby = 0;
    cout << "Podaj nazwe uzytkownika: ";
    cin >>  nazwaUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> nazwa == nazwaUzytkownika)
        {
            znalezionyUzytkownik = 1;
            for(int iloscProb = 0; iloscProb < 3; iloscProb++)
            {
                proby = iloscProb + 1;
                cout << "Podaj haslo. Pozostalo prob " << 3 - iloscProb << ":";
                cin >> hasloUzytkownika;
                if (itr -> haslo == hasloUzytkownika)
                {
                    cout<< "Zalogowales sie."<<endl;
                    return itr -> idUzytkownika;
                }
            }
            if( proby == 3)
            {
               cout << "Podales 3 razy bledne haslo.Poczekaj przez 3 sekundy przed kolejna proba." << endl;
            }
        }
    }

    if(!znalezionyUzytkownik)   //jesli zmienna Znaleziony_znajomy==0
    {
        cout << "Nie ma uzytkownika z takim loginem." << endl;
    }

    Sleep(1500);
    return 0;
}

void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string hasloUzytkownika;
    int pozycjaZnalezionejOsoby = 0;
    cout << "Podaj nowe haslo: ";
    cin >> hasloUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if(itr -> idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[pozycjaZnalezionejOsoby].haslo = hasloUzytkownika;
            cout << "Haslo zostalo zmienione"<< endl;
            Sleep(1500);
        }
        pozycjaZnalezionejOsoby++;
    }
}

void zapiszDaneUzytkownikowDoPliku (vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    string liniaZDanymiUzytkownika = "";
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> idUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr -> nazwa + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';

            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

int main()
{
    vector <Uzytkownik> uzytkownicy;

    int idZalogowanegoUzytkownika=0;

    wczytajUzytkownikowZPliku(uzytkownicy);

    char wybor;
    while(1)
    {
        wczytajUzytkownikowZPliku(uzytkownicy);
        if(idZalogowanegoUzytkownika ==0)
        {
            system("cls");
            cout << "1.Rejestracja" << endl;
            cout << "2.Logowanie" << endl;
            cout << "9.Zakoncz program" << endl;
            cin >> wybor;

            if (wybor == '1')
            {
                rejestracjaUzytkownika(uzytkownicy);
            }
            else if(wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
            }
            else if (wybor=='9')
            {
                exit(0);
            }
        }
        else
        {
            system("cls");
            cout<< "1.Zmiana hasla" <<endl;
            cout<< "2.Wylogowanie" << endl;
            cin>> wybor;

            if (wybor=='1')
            {
            zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            zapiszDaneUzytkownikowDoPliku(uzytkownicy);
            }
            else if(wybor == '2')
            {
                idZalogowanegoUzytkownika = 0;
            }
        }

    }
    return 0;
}

