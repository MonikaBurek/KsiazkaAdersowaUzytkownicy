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

int znajdzKolejnyNumerIDZnajomego ()
{
    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int najwiekszyNumerID = 0;
    int aktualnyNumerID = 0;
    int kolejnyNumerID = 0;
    fstream plik;

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
                    aktualnyNumerID= atoi(wyraz.c_str());
                    if ( iloscPionowychKresek == 1 )
                    {
                        if (aktualnyNumerID > najwiekszyNumerID)
                        {
                            najwiekszyNumerID = aktualnyNumerID;
                        }
                    }
                }
            }
        }
    }
    kolejnyNumerID = najwiekszyNumerID + 1;
    return kolejnyNumerID;

}

void zapiszNowegoZnajomego(vector <Znajomy> &znajomi, int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, adres, numerTelefonu, mail;
    string liniaZDanymiZnajomego = "";
    Znajomy Osoba;

    cout << endl << "Zapisywanie nowego znajomego." << endl << endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin,numerTelefonu);
    cout << "Podaj mail: ";
    cin >> mail;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin,adres);

    Osoba.numerIDZnajomego = znajdzKolejnyNumerIDZnajomego();
    Osoba.numerIDUzytkownika = idZalogowanegoUzytkownika;
    Osoba.imie = imie;
    Osoba.nazwisko = nazwisko;
    Osoba.numerTelefonu = numerTelefonu;
    Osoba.mail = mail;
    Osoba.adres = adres;

    znajomi.push_back(Osoba);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::app);

    if (plik.good() == true)
    {
            liniaZDanymiZnajomego += konwerjsaIntNaString(Osoba.numerIDZnajomego) + '|';
            liniaZDanymiZnajomego += konwerjsaIntNaString(Osoba.numerIDUzytkownika) + '|';
            liniaZDanymiZnajomego += Osoba.imie + '|';
            liniaZDanymiZnajomego += Osoba.nazwisko + '|';
            liniaZDanymiZnajomego += Osoba.numerTelefonu + '|';
            liniaZDanymiZnajomego += Osoba.mail + '|';
            liniaZDanymiZnajomego += Osoba.adres + '|';

            plik << liniaZDanymiZnajomego << endl;
            liniaZDanymiZnajomego = "";

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

void usunLinieZPliku (int idZalogowanegoUzytkownika)
{
    vector <string> linieDoUsuniecia;
    string linia;
    string wyraz;
    int iloscPionowychKresek = 0;
    int ileZnakowWyjac = 0;
    int poczatek = 0 ;
    int idUzytkownikaZPliku;
    bool znalezionaLinia;

    fstream plik;
    ofstream nowyPlik;

    linieDoUsuniecia.clear();
    plik.open("KsiazkaAdresowa.txt", ios::in); // aby otworzyc plik do odczytu
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
                        linieDoUsuniecia.push_back(linia);
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }
        }
        plik.close();
    }

    nowyPlik.open("PlikBezLinii.txt");
    plik.open("KsiazkaAdresowa.txt",ios::in);

     while (getline(plik,linia))
    {
        znalezionaLinia = 0;
        for( int i = 0; i < linieDoUsuniecia.size(); i++ )
        {
            if ( linia == linieDoUsuniecia[i] )
            {
                znalezionaLinia = 1;
            }
        }
        if (znalezionaLinia == 0)
            nowyPlik << linia << endl;

    }

    nowyPlik.close();
    plik.close();
    remove("KsiazkaAdresowa.txt"); // remove usuwa plik
    rename("PlikBezLinii.txt","KsiazkaAdresowa.txt");
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
                        //linieDoUsuniecia.push_back(linia);
                        break;
                    }
                    poczatek = poczatek + ileZnakowWyjac + 1;
                }
            }
        }
        plik.close();
    }
    //usunLinieZPliku(linieDoUsuniecia);
    //zapiszDaneZnajomychDoPlikuNaPoczatku(znajomi);
}

void wyswietlWszystkichZnajomych(vector <Znajomy> &znajomi)
{
    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        cout << endl;
        cout << "Numer ID Znajomego: " << itr -> numerIDZnajomego << endl;
        cout << itr -> imie << " " << itr -> nazwisko << endl;
        cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
        cout << "Mail: " << itr -> mail << endl;
        cout << "Adres: " << itr -> adres << endl;
        cout << endl;
    }
    system("pause");
}

void szukajImie(vector <Znajomy> &znajomi)
{
    string poszukiwaneImie;
    bool znalezionyZnajomy = 0;
    cout << endl << "Podaj imie znajomego, ktorego mamy wyszukac: ";
    cin >> poszukiwaneImie;

    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        if (itr -> imie == poszukiwaneImie)
        {
            znalezionyZnajomy = 1;
            cout << endl;
            cout << "Numer ID Znajomego: " << itr -> numerIDZnajomego << endl;
            cout << itr -> imie << " " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Mail: " << itr -> mail << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;
        }
    }

    if(!znalezionyZnajomy)   //jesli zmienna Znaleziony_znajomy==0
    {
        cout << endl << "Nie znaleziono osoby o tym imieniu." << endl << endl;
    }
    system("pause");
}

void szukajNazwisko(vector <Znajomy> &znajomi)
{
    string poszukiwaneNazwisko;
    bool znalezionyZnajomy = 0;
    cout << endl << "Podaj nazwisko znajomego, ktorego mamy wyszukac: ";
    cin >> poszukiwaneNazwisko;

    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        if (itr -> nazwisko == poszukiwaneNazwisko)
        {
            znalezionyZnajomy = 1;
            cout << endl;
            cout << "Numer ID Znajomego: " << itr -> numerIDZnajomego << endl;
            cout << itr -> imie << " " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Mail: " << itr -> mail << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;
        }
    }

    if(!znalezionyZnajomy)   //jesli zmienna Znaleziony_znajomy==0
    {
        cout << endl << "Nie znaleziono osoby o tym nazwisku." << endl << endl;
    }
    system("pause");
}

void edytujKontakt (vector <Znajomy> &znajomi)
{
    string numerTelefonu, mail, adres;
    char wybranaPozycjaMenu;

    int poszukiwanyNumerID;
    bool znalezionyZnajomy = 0;
    int pozycjaZnalezionejOsoby = 0;


    cout << "Wyszukanie znajomego. Podaj numer ID znajomego: ";
    cin >> poszukiwanyNumerID;

    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        if (itr -> numerIDZnajomego == poszukiwanyNumerID)
        {
            znalezionyZnajomy = 1;
            system("cls");
            cout << "Edycja kontaktu." << endl;
            cout << itr -> imie << " " << itr -> nazwisko << endl;
            cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
            cout << "Mail: " << itr -> mail << endl;
            cout << "Adres: " << itr -> adres << endl;
            cout << endl;
            cout << "1.Edytuj numer telefonu." << endl;
            cout << "2.Edytuj adres mailowy." << endl;
            cout << "3.Edytuj adres kontaktowy." << endl;
            cout << "4.Edytuj wszystkie informacje." << endl;
            cout << "9.Zakoncz edycje." << endl<<endl;
            cin>> wybranaPozycjaMenu;

            switch(wybranaPozycjaMenu)
            {
            case '1':
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin,numerTelefonu);
                znajomi[pozycjaZnalezionejOsoby].numerTelefonu = numerTelefonu;
                break;
            case '2':
                cout << "Podaj nowy adres mailowy: ";
                cin >>  mail;
                znajomi[pozycjaZnalezionejOsoby].mail = mail;
                break;
            case '3':
                cout << "Podaj nowy adres kontaktowy: ";
                cin.sync();
                getline(cin,adres);
                znajomi[pozycjaZnalezionejOsoby].adres = adres;
                break;
            case '4':
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin,numerTelefonu);
                cout << "Podaj nowy adres mailowy: ";
                cin >>  mail;
                cout << "Podaj nowy adres kontaktowy: ";
                cin.sync();
                getline(cin,adres);

                znajomi[pozycjaZnalezionejOsoby].numerTelefonu = numerTelefonu;
                znajomi[pozycjaZnalezionejOsoby].mail = mail;
                znajomi[pozycjaZnalezionejOsoby].adres = adres;
                break;
            case '9':
                system("pause");
                break;
            }
            cout << "Edycja kontaktu przebiegla pomyslnie." << endl << endl;

        }
        pozycjaZnalezionejOsoby++;
    }

    if(!znalezionyZnajomy)   //jesli zmienna Znaleziony_znajomy==0
    {
        cout << endl << "Nie znaleziono osoby o podanym: imieniu i nazwisku." << endl << endl;
        system("pause");
    }
}

void usunKontakt (vector <Znajomy> &znajomi)
{
    int poszukiwanyNumerID;


    cout << "Wyszukanie znajomego. Podaj numer ID znajomego: ";
    cin >> poszukiwanyNumerID;

    for (vector <Znajomy>::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++)
    {
        if (itr -> numerIDZnajomego == poszukiwanyNumerID)
        {
            itr = znajomi.erase(itr);
            cout << "Kontakt zostal usuniety." << endl << endl;
            system("pause");
            break;
        }
    }
}

void zapiszDaneZnajomychDoPliku(vector <Znajomy> &znajomi, int idZalogowanegoUzytkownika)
{
    fstream plik;
    string liniaZDanymiZnajomego = "";


    usunLinieZPliku(idZalogowanegoUzytkownika);

    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
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

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Znajomy> znajomi;

    int idZalogowanegoUzytkownika = 0;

    wczytajUzytkownikowZPliku(uzytkownicy);

    char wybranaPozycjaMenu;

    while(1)
    {
        wczytajUzytkownikowZPliku(uzytkownicy);
        if(idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "1.Rejestracja" << endl;
            cout << "2.Logowanie" << endl;
            cout << "9.Zamknij program" << endl;
            cin >> wybranaPozycjaMenu;

            switch(wybranaPozycjaMenu)
            {
            case '1':
                rejestracjaUzytkownika(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanieUzytkownika(uzytkownicy);
                break;
            case '9':
                exit(0);
                break;
            }
        }
        else
        {
            wczytajZnajomychZPliku(znajomi, idZalogowanegoUzytkownika);
            system("cls");
            cout<< "Ksiazka adresowa."<<endl<<endl;
            cout << "1.Zapisz nowego znajomego." << endl;
            cout << "2.Wyszukaj znajomego." << endl;
            cout << "3.Wyswietl liste znajomych." << endl;
            cout << "4.Edytuj kontakt." << endl;
            cout << "5.Usun kontakt." << endl;
            cout << "6.Zmien haslo." << endl;
            cout << "9.Wyloguj sie." << endl<<endl;
            cin>> wybranaPozycjaMenu;

            switch(wybranaPozycjaMenu)
            {
            case '1':
                zapiszNowegoZnajomego(znajomi, idZalogowanegoUzytkownika);
                break;
            case '2':

                system("cls");
                cout<< "Wyszukiwanie znajomego." <<endl<< endl;
                cout<<"1.Wyszukiwanie wg imienia." <<endl;
                cout<<"2.Wyszukiwanie wg nazwiska." <<endl;
                cout<<"9.Zakoncz wyszukiwanie."<< endl;
                cin>> wybranaPozycjaMenu;

                switch(wybranaPozycjaMenu)
                {
                case '1':
                    szukajImie(znajomi);
                    break;
                case '2':
                    szukajNazwisko(znajomi);
                    break;
                case '9':
                    system("pause");
                }
                break;
            case '3':
                wyswietlWszystkichZnajomych(znajomi);
                break;
            case '4':
                edytujKontakt(znajomi);
                zapiszDaneZnajomychDoPliku(znajomi, idZalogowanegoUzytkownika);
                break;
            case '5':
                usunKontakt(znajomi);
                zapiszDaneZnajomychDoPliku(znajomi, idZalogowanegoUzytkownika);
                break;
            case '6':
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                zapiszDaneUzytkownikowDoPliku(uzytkownicy);
                break;
            case '9':
                idZalogowanegoUzytkownika = 0;
                break;
            }
        }

    }
    return 0;
}

