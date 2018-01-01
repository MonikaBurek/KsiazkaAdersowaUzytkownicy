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


int logowanie(Uzytkownik uzytkownicy[], int iloscUzytkownikow)
{
    string nazwaUzytkownika, hasloUzytkownika;
    cout<< "Podaj nazwe: ";
    cin>>  nazwaUzytkownika;
    int i =0;
    /*  while (i<iloscUzytkownikow)
      {
          if(uzytkownicy[i].nazwa==nazwa)
          {
              for(int proby=0; proby<3; proby++)
              {
                  cout<<"Podaj haslo. Pozostalo prob "<<3-proby<< ":";
                  cin>> haslo;
                  if (uzytkownicy[i].haslo==haslo)
                  {
                      cout<< "Zalogowales sie."<<endl;
                      Sleep(1000);
                      return uzytkownicy[i].idUzytkownik;
                  }
              }
              cout<<"Podales 3 razy bledne haslo.Poczekaj przez 3 sekundy przed kolejna proba"<<endl;
              Sleep(3000);
          }
          i++;
      }
      cout<< "Nie ma uzytkownika z takim loginem"<<endl;
      Sleep(1500);*/
    return 0;
}

void zmianaHasla(Uzytkownik uzytkownicy[], int iloscUzytkownikow, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout<< "Podaj nowe haslo: ";
    cin>> haslo;
    for(int i=0; i<iloscUzytkownikow; i++)
    {
        if(uzytkownicy[i].idUzytkownika==idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo=haslo;
            cout << "Haslo zostalo zmienione"<< endl;
            Sleep(1500);
        }
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
                //       idZalogowanegoUzytkownika=logowanie(uzytkownicy, iloscUzytkownikow);
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
                //     zmianaHasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
            }
            else if(wybor == '2')
            {
                idZalogowanegoUzytkownika=0;
            }
        }

    }
    return 0;
}

