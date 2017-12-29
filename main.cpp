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
    int idUzytkownik;
    string nazwa, haslo;
};

string konwerjsaIntNaString ( int liczba)
{
    ostringstream ss;
    ss << liczba;
    string lancuch = ss.str();
    return lancuch;
}

void rejestracja(vector <Uzytkownik> uzytkownicy)
{
    string nazwaUzytkownika, hasloUzytkownika;
    int idUzytkownik;
    string liniaZDanymiUzytkownika = "";
    Uzytkownik Osoba;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if (itr -> nazwa == nazwaUzytkownika)
        {
            cout << "Taki uztkownik juz istniej. Wpisz inna nazwe uzytkownika: ";
            break;
        }

    }
    cout << "Podaj haslo: ";
    cin >> hasloUzytkownika;

     if (uzytkownicy.empty() == true)  // je¿eli ksia¿ka adresowa jest pusta
    {
        Osoba.idUzytkownik = 1;           // to nowy adresat ma id=1
    }
    else
    {
        Osoba.idUzytkownik= uzytkownicy.back().idUzytkownik + 1; // w przeciwnym przypadku pobierz id ostatniej osoby z ksi¹¿ki adresowej i zwiêksz wartoœæ o jeden.
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
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr -> idUzytkownik) + '|';
            liniaZDanymiUzytkownika += itr -> nazwa + '|';
            liniaZDanymiUzytkownika += itr -> haslo + '|';


            plik << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plik.close();
        cout << "Dane zostaly zapisne." << endl;
        system("pause");
    }

    cout<< "Konto zalozone." <<endl;
    Sleep(1000);
}

int logowanie(Uzytkownik uzytkownicy[], int iloscUzytkownikow)
{
    string nazwa, haslo;
    cout<< "Podaj nazwe: ";
    cin>>  nazwa;
    int i =0;
    while (i<iloscUzytkownikow)
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
    Sleep(1500);
    return 0;
}

void zmianaHasla(Uzytkownik uzytkownicy[], int iloscUzytkownikow, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout<< "Podaj nowe haslo: ";
    cin>> haslo;
    for(int i=0; i<iloscUzytkownikow; i++)
    {
        if(uzytkownicy[i].idUzytkownik==idZalogowanegoUzytkownika)
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
    int iloscUzytkownikow=0;
    char wybor;
    while(1)
    {
        if(idZalogowanegoUzytkownika ==0)
        {
            system("cls");
            cout<< "1.Rejestracja" <<endl;
            cout<<"2.Logowanie"<<endl;
            cout<<"9.Zakoncz program"<<endl;
            cin>> wybor;

            if (wybor=='1')
            {
          //      iloscUzytkownikow=rejestracja(uzytkownicy,iloscUzytkownikow);
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

