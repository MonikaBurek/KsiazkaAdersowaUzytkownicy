#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Znajomy
{
    int numerIDZnajomego,numerIDUzytkownika;
    string imie, nazwisko, numerTelefonu, mail, adres;
};

string konwerjsaIntNaString (int liczba)
{
    ostringstream ss;
    ss << liczba;
    string lancuch = ss.str();
    return lancuch;
}


void zapiszZnajomychUzytkownikaDoWektora (vector <Znajomy> &znajomi, string linia, int iloscZnajomych)
{
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;

    Znajomy pusty;

    znajomi.push_back(pusty);

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
                znajomi[iloscZnajomych - 1].numerIDZnajomego = atoi(wyraz.c_str());
                break;
            case 2:
                znajomi[iloscZnajomych - 1].numerIDUzytkownika = atoi(wyraz.c_str());
                break;
            case 3:
                znajomi[iloscZnajomych - 1].imie = wyraz;
                break;
            case 4:
                znajomi[iloscZnajomych - 1].nazwisko = wyraz;
                break;
            case 5:
                znajomi[iloscZnajomych - 1].numerTelefonu = wyraz;
                break;
            case 6:
                znajomi[iloscZnajomych - 1].mail = wyraz;
                break;
            case 7:
                znajomi[iloscZnajomych - 1].adres = wyraz;
                break;
            }
            poczatek = poczatek + ileZnakowWyjac + 1;
        }
    }
}

void wczytajZnajomychZPliku(vector <Znajomy> &znajomi, int idZalogowanegoUzytkownika)
{
    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int idUzytkownikaZPliku = 0;
    int iloscZnajomych = 0;
    fstream plik;

    znajomi.clear();
    plik.open("KsiazkaAdresowa.txt",ios::in); // aby otworzyc plik do odczytu
    if (plik.good() == true)
    {
        while (getline(plik,linia))
        {
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
                    idUzytkownikaZPliku = atoi(wyraz.c_str());
                    if ( iloscPionowychKresek == 2 &&  idZalogowanegoUzytkownika == idUzytkownikaZPliku)
                    {
                        iloscZnajomych++;
                        zapiszZnajomychUzytkownikaDoWektora(znajomi, linia, iloscZnajomych);
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }

        }
        plik.close();
    }

}


void zapiszDaneZnajomychDoPliku (vector <Znajomy> &znajomi)
{
    fstream plik;
    string liniaZDanymiZnajomego = "";
    plik.open("KsiazkaAdresowa.txt", ios::out);

    if (plik.good() == true)
    {
        for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
        {
            liniaZDanymiZnajomego += konwerjsaIntNaString(itr -> numerIDZnajomego) + '|';
            liniaZDanymiZnajomego += konwerjsaIntNaString(itr -> numerIDUzytkownika) + '|';
            liniaZDanymiZnajomego += itr -> imie + '|';
            liniaZDanymiZnajomego += itr -> nazwisko + '|';
            liniaZDanymiZnajomego += itr -> numerTelefonu + '|';
            liniaZDanymiZnajomego += itr -> mail + '|';
            liniaZDanymiZnajomego += itr -> adres + '|';

            plik << liniaZDanymiZnajomego << endl;
            liniaZDanymiZnajomego = "";
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

    vector <Znajomy> znajomi;
    int idZalogowanegoUzytkownika = 4;

    wczytajZnajomychZPliku(znajomi, idZalogowanegoUzytkownika);
    zapiszDaneZnajomychDoPliku(znajomi);

}

