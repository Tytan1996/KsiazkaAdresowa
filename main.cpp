#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>


using namespace std;

int numer_Id=0;
int iloscUzytkownikow=1;

typedef struct kontakt {

    int id;
    int idUzytkownika;
    string imie;
    string nazwisko;
    string numer_telefonu;
    string email;
    string adres;

} Kontakt;

typedef struct uzytkownik {

    int id;
    string login;
    string haslo;

} Uzyktownik;

vector <kontakt> ListaKontakow;
vector <uzytkownik> ListaUzytkownikow;
void wczytac_plik(int idUzytkownika);
void wprowadz_dane_do_nowego_kontaktu();
void dodaj_nowy_kontakt_do_pamiecy_komputera(int idUzytkownika, string imie, string nazwisko,string numer_telefonu,string email,string adres);
void pokaz_cala_ksiazke_adresowa();
vector <kontakt> dodanie_wyniku_po_imieniu_do_wyszukiwarki(string szukanie_imie, int idUzytkownika);
vector <kontakt> dodanie_wyniku_po_nazwisku_do_wyszukiwarki(string szukanie_nazwisko, int idUzytkownika);
void pokaz_wyniki_wyszukiwarki(vector <kontakt> wynikiWyszukiwarki);
void usunKontakt();
void modyfikujKontakt(int idUzytkownika);
void wyswietlMenuUzytkownika(uzytkownik *zalogowanyUzytkownik);
void wczytajUzytkownikow();
void dodanieUzytkonikowDoVectora(int id, string login,string haslo);
void rejestracja();
void logowanie();
void zmianaHasla(uzytkownik *zalogowanyUzytkownik);
void zapisUzytkownikowDoPliku();
void dodajDoPlikuNowyKontakt();
void modyfikujPlikTekstowy(int numerPozycjiKontaktu);
void usunKontaktZPliku(int idUsunietegoKontaktu);
void sprawdzId();

int main() {

    int opcjaUzytkownika;
    fstream listaUzytkownikow;
    listaUzytkownikow.open("Adresaci.txt", ios::in);

    if(listaUzytkownikow.good()==true) {
        listaUzytkownikow.close();
        wczytajUzytkownikow();
    }

    do {
        cout<<"----------------"<<endl;
        cout<<"MENU"<<endl;
        cout<<"----------------\n"<<endl;
        cout<<"1 - Zaloguj sie\n";
        cout<<"2 - Rejestracja\n";
        cout<<"3 - Zakoncz program\n";
        cout<<"Twoja opcja: ";
        cin>>opcjaUzytkownika;
        switch(opcjaUzytkownika) {
        case 1:
            system("cls");
            logowanie();
            break;
        case 2:
            system("cls");
            rejestracja();
            zapisUzytkownikowDoPliku();
            break;
        case 3:
            zapisUzytkownikowDoPliku();
            return 0;
            break;
        default:
            system("cls");
            cout<<"Wybrales zla opcje!\n"<<endl;
            break;
        }
    } while(opcjaUzytkownika!=3);
    zapisUzytkownikowDoPliku();
    return 0;
}
void wczytac_plik(int idZalogowaniego) {
    fstream plik;
    plik.open("Ksiazka_adresowa.txt", ios::in);
    if (plik.good()==false) {
        return;
    }
    string linia, imie,nazwisko,numer_telefonu,email,adres;
    int nr_linii=1, id,numerek,ilosc1,idUzytkownika;
    char buffor[50];
    plik.seekg(0,ios::beg);
    while(getline(plik,linia)) {
        for(int i=0; i<7; ++i) {
            numerek=linia.find("|");
            ilosc1=linia.copy(buffor,numerek,0);
            buffor[ilosc1]='\0';
            linia.erase(0,ilosc1+1);
            switch(i) {
            case 0:
                id=atoi(buffor);
                numer_Id=id;
                break;
            case 1:
                idUzytkownika=atoi(buffor);
                break;
            case 2:
                imie=buffor;
                break;
            case 3:
                nazwisko=buffor;
                break;
            case 4:
                numer_telefonu=buffor;
                break;
            case 5:
                email=buffor;
                break;
            case 6:
                adres=buffor;
                break;
            }
        }
        if(idUzytkownika==idZalogowaniego) {
            dodaj_nowy_kontakt_do_pamiecy_komputera(idUzytkownika,imie,nazwisko,numer_telefonu,email,adres);
        }

        if(numer_Id>=1000) {
            cout<<"Masz pelna liste!"<<endl;
            plik.close();
            return;
        }
    }
    plik.close();

}
void wprowadz_dane_do_nowego_kontaktu(int idUzytkownika) {
    char znak;
    string imie,nazwisko,numer_telefonu,email,adres;
    if(numer_Id>=1000) {
        cout<<"Masz pelna liste!"<<endl;
        return;
    }

    cout<<"Podaj imie"<<endl;
    cout<<"Imie: ";
    cin>>imie;
    cout<<"Podaj nazwisko"<<endl;
    cout<<"nazwisko: ";
    cin>>nazwisko;
    cout<<"Podaj numer telefonu"<<endl;
    cout<<"Numer telefonu: ";
    cin>>numer_telefonu;
    cout<<"Podaj email"<<endl;
    cout<<"email: ";
    cin>>email;
    cout<<"Podaj adres"<<endl;
    cout<<"adres: ";
    cin.ignore();
    getline(cin,adres);
    system("cls");
    cout<<imie<<endl;
    cout<<nazwisko<<endl;
    cout<<numer_telefonu<<endl;
    cout<<email<<endl;
    cout<<adres<<endl;
    cout<<"Poprawnie sa dane i dodac je do ksiazki adresowej? <t/n>"<<endl;
    znak=getch();
    if(znak=='n') {
        system("cls");
        return;
    } else if(znak=='t') {
        system("cls");
        numer_Id++;
        dodaj_nowy_kontakt_do_pamiecy_komputera(idUzytkownika, imie, nazwisko,numer_telefonu, email, adres);
        dodajDoPlikuNowyKontakt();
    }
}
void dodaj_nowy_kontakt_do_pamiecy_komputera(int idUzytkownika, string imie, string nazwisko,string numer_telefonu, string email,string adres ) {
    kontakt NowyKontakt= {numer_Id,idUzytkownika,imie,nazwisko,numer_telefonu,email,adres};
    ListaKontakow.push_back(NowyKontakt);

}
void pokaz_cala_ksiazke_adresowa() {
    char znak;
    int opcja_uzykownika,iloscElementow;
    if(ListaKontakow.empty()) {
        system("cls");
        cout<<"Nie masz zadnych kontakow"<<endl<<endl;
        return;
    } else {

        iloscElementow=ListaKontakow.size();
        for(int i=0; i<iloscElementow; ++i) {
            cout<<ListaKontakow[i].id<<endl;
            cout<<ListaKontakow[i].imie<<endl;
            cout<<ListaKontakow[i].nazwisko<<endl;
            cout<<ListaKontakow[i].numer_telefonu<<endl;
            cout<<ListaKontakow[i].email<<endl;
            cout<<ListaKontakow[i].adres<<endl;
            cout<<endl;
        }
    }
}
vector <kontakt> dodanie_wyniku_po_imieniu_do_wyszukiwarki(string szukanie_imie, int idUzytkownika) {
    vector<kontakt>WynikiWyszukiwarki;
    int iloscElementow=ListaKontakow.size();
    for(int i=0; i<iloscElementow; ++i) {
        if(ListaKontakow[i].imie==szukanie_imie && ListaKontakow[i].idUzytkownika==idUzytkownika) {
            WynikiWyszukiwarki.push_back(ListaKontakow[i]);
        }
    }
    return WynikiWyszukiwarki;
}
vector <kontakt> dodanie_wyniku_po_nazwisku_do_wyszukiwarki(string szukanie_nazwisko, int idUzytkownika) {
    vector<kontakt>WynikiWyszukiwarki;
    int iloscElementow=ListaKontakow.size();
    for(int i=0; i<iloscElementow; ++i) {
        if(ListaKontakow[i].nazwisko==szukanie_nazwisko && ListaKontakow[i].idUzytkownika==idUzytkownika) {
            WynikiWyszukiwarki.push_back(ListaKontakow[i]);
        }
    }
    return WynikiWyszukiwarki;
}
void pokaz_wyniki_wyszukiwarki(vector <kontakt> WynikiWyszukiwarki) {
    int opcja_uzytkownika,iloscKontakow;
    if(WynikiWyszukiwarki.empty()) {
        system("cls");
        cout<<"Nie ma takich kontakow"<<endl<<endl;
        return;

    } else {
        iloscKontakow=WynikiWyszukiwarki.size();
        for(int i=0; i<iloscKontakow; ++i) {
            cout<<WynikiWyszukiwarki[i].id<<endl;
            cout<<WynikiWyszukiwarki[i].imie<<endl;
            cout<<WynikiWyszukiwarki[i].nazwisko<<endl;
            cout<<WynikiWyszukiwarki[i].numer_telefonu<<endl;
            cout<<WynikiWyszukiwarki[i].email<<endl;
            cout<<WynikiWyszukiwarki[i].adres<<endl;
            cout<<endl;
        }

    }
}
void usunKontakt() {
    char potwierdzenie='n';
    bool jestKontakt=false;
    int iloscKotanktowUzytkownika=ListaKontakow.size();
    int opcjaUzytkonika,numerekID,numerKontaktuDoUsunecia,idUsunietegoKontaktu;
    if(ListaKontakow.empty()) {
        cout<<"Nie masz zadnych kontaktow."<<endl<<endl;
        return;
    }
    cout<<"1 - usun prierwszy kontakt;"<<endl;
    cout<<"2 - usun ostatnt kontakt;"<<endl;
    cout<<"3 - usuniecie kontaktu po numeru id;"<<endl;
    cout<<"0 - powrot do menu;"<<endl;
    cout<<"Twoja opcja: ";
    cin>>opcjaUzytkonika;
    switch(opcjaUzytkonika) {
    case 1:
        numerKontaktuDoUsunecia=0;
        break;
    case 2:
        numerKontaktuDoUsunecia=iloscKotanktowUzytkownika-1;
        break;
    case 3: {
        cout<<"Podaj nume id kontaktu, ktory chcesz usunac. Od 1 do "<<numer_Id<<"."<<endl;
        cout<<"Id: ";
        cin>>numerekID;
        if(numerekID>numer_Id) {
            cout<<"Za duzy numer Id podales!."<<endl<<endl;
            return;
        }
        if(numerekID<=0) {
            cout<<"Podales zbyt maly numer ID!."<<endl<<endl;
            return;
        }
        for(int i=0; i<iloscKotanktowUzytkownika; ++i) {
            if(numerekID==ListaKontakow[i].id) {
                numerKontaktuDoUsunecia=i;
                jestKontakt=true;
                break;
            }
        }
        if(!jestKontakt) {
            cout<<"Tego kontaktu nie mozesz usunac.\n"<<endl;
            return;
        }
        break;
    }
    default:
        cout<<"Wybrano zla opcje!"<<endl<<endl;
        return;
        break;
    }
    cout<<ListaKontakow[numerKontaktuDoUsunecia].id<<endl;
    cout<<ListaKontakow[numerKontaktuDoUsunecia].imie<<endl;
    cout<<ListaKontakow[numerKontaktuDoUsunecia].nazwisko<<endl;
    cout<<ListaKontakow[numerKontaktuDoUsunecia].numer_telefonu<<endl;
    cout<<ListaKontakow[numerKontaktuDoUsunecia].email<<endl;
    cout<<ListaKontakow[numerKontaktuDoUsunecia].adres<<endl;
    potwierdzenie=='n';
    cout<<"Czy jestes pewny ze ten kontakt chcesz usunac? Potwierdz guzikem 't'"<<endl;
    potwierdzenie=getch();
    if(potwierdzenie!='t') {
        system("cls");
        cout<<"Nie usuneto elementu"<<endl<<endl;
        return;
    }

    idUsunietegoKontaktu=ListaKontakow[numerKontaktuDoUsunecia].id;
    system("cls");
    switch(opcjaUzytkonika) {
    case 0:
        return;
        break;
    case 1:
        cout<<"usunales priewszy element."<<endl<<endl;
        if(ListaKontakow[0].id==numer_Id) {
            numer_Id--;
        }
        ListaKontakow.erase(ListaKontakow.begin());
        break;
    case 2:
        cout<<"usunales ostatni element."<<endl<<endl;
        if(ListaKontakow[iloscKotanktowUzytkownika-1].id==numer_Id) {
            numer_Id--;
        }
        ListaKontakow.pop_back();

        break;
    case 3:
        cout<<"usunety element o id "<<numerekID<<endl<<endl;
        if(ListaKontakow[numerKontaktuDoUsunecia].id==numer_Id) {
            numer_Id--;
        }
        ListaKontakow.erase(ListaKontakow.begin()+numerKontaktuDoUsunecia);
        break;
    default:
        cout<<"wybrales zla opcje"<<endl;
        break;
    }
    usunKontaktZPliku(idUsunietegoKontaktu);
    sprawdzId();

}
void modyfikujKontakt(int idUzytkownika) {
    bool jestKontakt=false;
    int opcjaUzytkonika,numerUzytkownika,iloscKontaktowZalogowaniego=ListaKontakow.size();
    char znakk;
    kontakt ZmanaKontaktu;
    string imie, nazwisko, email, adres, numerTelefonu;
    system("cls");
    if(ListaKontakow.empty()) {
        cout<<"Nie masz zadnych kontaktow."<<endl<<endl;
        return;
    } else {
        cout<<"Podaj nume id kontaktu, ktory chcesz usunac. Od 1 do "<<numer_Id<<"."<<endl;
        cout<<"Id: ";
        cin>>numerUzytkownika;
        if(numerUzytkownika>numer_Id) {
            cout<<"Za duzy numer Id podales!."<<endl<<endl;
            return;
        }
        if(numerUzytkownika<=0) {
            cout<<"Podales zbyt maly numer ID!."<<endl<<endl;
            return;
        }
        for(int i=0; i<iloscKontaktowZalogowaniego; ++i) {
            if(numerUzytkownika==ListaKontakow[i].id) {
                numerUzytkownika=i;
                jestKontakt=true;
                break;
            }
        }
        if(!jestKontakt) {
            cout<<"Tego Kontaktu nie mozesz edytowac."<<endl;
            return;
        }
        system("cls");
        cout<<ListaKontakow[numerUzytkownika].id<<endl;
        cout<<ListaKontakow[numerUzytkownika].imie<<endl;
        cout<<ListaKontakow[numerUzytkownika].nazwisko<<endl;
        cout<<ListaKontakow[numerUzytkownika].numer_telefonu<<endl;
        cout<<ListaKontakow[numerUzytkownika].email<<endl;
        cout<<ListaKontakow[numerUzytkownika].adres<<endl;
        cout<<"Ktore dane chcesz zmienic?"<<endl;
        cout<<"0 - powrot;"<<endl;
        cout<<"1 - imie;"<<endl;
        cout<<"2 - nazwisko;"<<endl;
        cout<<"3 - numer telefonu;"<<endl;
        cout<<"4 - email;"<<endl;
        cout<<"5 - adres;"<<endl;
        cout<<"6 - wszystkie dane;"<<endl;
        cout<<"Twoja opcja: ";
        cin>>opcjaUzytkonika;
        switch(opcjaUzytkonika) {
        case 0:
            return;
            break;
        case 1:
            cout<<"Podaj imie."<<endl;
            cout<<"Imie: ";
            cin>>imie;
            ZmanaKontaktu= {ListaKontakow[numerUzytkownika].id,idUzytkownika,imie,ListaKontakow[numerUzytkownika].nazwisko,ListaKontakow[numerUzytkownika].numer_telefonu,ListaKontakow[numerUzytkownika].email,ListaKontakow[numerUzytkownika].adres};
            break;
        case 2:
            cout<<"Podaj nazwisko."<<endl;
            cout<<"Nazwisko: ";
            cin>>nazwisko;
            ZmanaKontaktu= {ListaKontakow[numerUzytkownika].id,idUzytkownika,ListaKontakow[numerUzytkownika].imie,nazwisko,ListaKontakow[numerUzytkownika].numer_telefonu,ListaKontakow[numerUzytkownika].email,ListaKontakow[numerUzytkownika].adres};
            break;
        case 3:
            cout<<"Podaj numer telefonu."<<endl;
            cout<<"Numer telefonu: ";
            cin>>numerTelefonu;
            ZmanaKontaktu= {ListaKontakow[numerUzytkownika].id,idUzytkownika,ListaKontakow[numerUzytkownika].imie,ListaKontakow[numerUzytkownika].nazwisko,numerTelefonu,ListaKontakow[numerUzytkownika].email,ListaKontakow[numerUzytkownika].adres};
            break;
        case 4:
            cout<<"Podaj email."<<endl;
            cout<<"Email: ";
            cin>>email;
            ZmanaKontaktu= {ListaKontakow[numerUzytkownika].id,idUzytkownika,ListaKontakow[numerUzytkownika].imie,ListaKontakow[numerUzytkownika].nazwisko,ListaKontakow[numerUzytkownika].numer_telefonu,email,ListaKontakow[numerUzytkownika].adres};
            break;
        case 5:
            cout<<"Podaj adres."<<endl;
            cout<<"Adres: ";
            cin>>adres;
            ZmanaKontaktu= {ListaKontakow[numerUzytkownika].id,idUzytkownika,ListaKontakow[numerUzytkownika].imie,ListaKontakow[numerUzytkownika].nazwisko,ListaKontakow[numerUzytkownika].numer_telefonu,ListaKontakow[numerUzytkownika].email,adres};
            break;
        case 6:
            cout<<"Prosze podac poprawnie informacje."<<endl;
            cout<<"Imie: ";
            cin>>imie;
            cout<<"Nazwisko: ";
            cin>>nazwisko;
            cout<<"Numer telefonu: ";
            cin>>numerTelefonu;
            cout<<"Email: ";
            cin>>email;
            cout<<"Adres: ";
            cin>>adres;
            ZmanaKontaktu= {numer_Id,idUzytkownika,imie,nazwisko,numerTelefonu,email,adres};
        default:
            cout<<"Wybrano zla opcje!"<<endl;
            return;
        }
        cout<<"Czy chcesz dokonac zmian? Potwierdz: 't'"<<endl;
        znakk=getch();
        if(znakk=='t') {
            ListaKontakow.erase(ListaKontakow.begin()+numerUzytkownika);
            ListaKontakow.insert(ListaKontakow.begin()+numerUzytkownika,ZmanaKontaktu);
        }
        system("cls");
        cout<<"Prowadzono zmane!"<<endl<<endl;
        modyfikujPlikTekstowy(numerUzytkownika);
    }

}
void wyswietlMenuUzytkownika(uzytkownik *zalogowanyUzytkownik) {

    fstream plik;
    plik.open("Ksiazka_adresowa.txt", ios::in);

    if (plik.good()==true) {
        plik.close();
        wczytac_plik(zalogowanyUzytkownik->id);
    }
    int opcja_uzytkownika;
    string SzukanieImie, SzukanieNazwisko;
    do {
        cout<<"1 - dodanie nowego kontaktu;"<<endl;
        cout<<"2 - wyszukiwanie kontaktu po imieniu;"<<endl;
        cout<<"3 - wyszukiwanie kontaktu po nazwisku;"<<endl;
        cout<<"4 - wyswietlenie wszystkich kontaktow:"<<endl;
        cout<<"5 - usun kontakt;"<<endl;
        cout<<"6 - edytuj kontakt;"<<endl;
        cout<<"7 - zmiana hasla;"<<endl;
        cout<<"9 - wyloguj sie;"<<endl;
        cout<<"Twoja opcja: ";
        cin>>opcja_uzytkownika;
        system("cls");
        switch(opcja_uzytkownika) {
        case 1:
            system("cls");
            wprowadz_dane_do_nowego_kontaktu(zalogowanyUzytkownik->id);
            break;
        case 2:
            system("cls");
            cout<<"Po jakim imieniu szukasz."<<endl;
            cout<<"Imie: ";
            cin>>SzukanieImie;
            pokaz_wyniki_wyszukiwarki(dodanie_wyniku_po_imieniu_do_wyszukiwarki(SzukanieImie,zalogowanyUzytkownik->id));
            break;
        case 3:
            system("cls");
            cout<<"Po jakim nazwisku szukasz."<<endl;
            cout<<"Nazwisko: ";
            cin>>SzukanieNazwisko;
            pokaz_wyniki_wyszukiwarki(dodanie_wyniku_po_nazwisku_do_wyszukiwarki(SzukanieNazwisko,zalogowanyUzytkownik->id));
            break;

        case 4:
            system("cls");
            pokaz_cala_ksiazke_adresowa();
            break;
        case 5:
            system("cls");
            usunKontakt();
            break;
        case 6:
            system("cls");
            modyfikujKontakt(zalogowanyUzytkownik->id);
            break;
        case 7:
            zmianaHasla(zalogowanyUzytkownik);
            zapisUzytkownikowDoPliku();
            break;
        case 9:
            system("cls");
            cout<<"Wylogowales sie.\n"<<endl;
            ListaKontakow.clear();
            return;
            break;

        default:
            cout<<"Podales zla opcje!"<<endl<<endl;
            break;
        }
    } while(opcja_uzytkownika!=9);
    ListaKontakow.clear();
}
void wczytajUzytkownikow() {
    fstream plik;
    plik.open("Adresaci.txt", ios::in);
    if (plik.good()==false) {
        return;
    }
    string linia, login,haslo;
    int nr_linii=1, id,numerek,ilosc1;
    char buffor[50];
    plik.seekg(0,ios::beg);
    while(getline(plik,linia)) {
        for(int i=0; i<3; ++i) {
            numerek=linia.find("|");
            ilosc1=linia.copy(buffor,numerek,0);
            buffor[ilosc1]='\0';
            linia.erase(0,ilosc1+1);
            switch(i) {
            case 0:
                iloscUzytkownikow=atoi(buffor);
                break;
            case 1:
                login=buffor;
                break;
            case 2:
                haslo=buffor;
                break;
            }
        }
        dodanieUzytkonikowDoVectora(iloscUzytkownikow,login,haslo);
        iloscUzytkownikow++;
    }
    plik.close();

}
void dodanieUzytkonikowDoVectora(int id, string login,string haslo) {

    uzytkownik nowyUzytkownik= {id,login,haslo};
    ListaUzytkownikow.push_back(nowyUzytkownik);

}
void rejestracja() {

    string login,haslo,haslo2;
    int rozmarVectora=ListaUzytkownikow.size();
    cout<<"Login: ";
    cin>>login;
    cout<<"Haslo: ";
    cin>>haslo;
    cout<<"Powtorz haslo: ";
    cin>>haslo2;

    system("cls");

    if(haslo!=haslo2) {
        cout<<"Hasla nie sa takie same!\n"<<endl;
        return;
    }
    if(!ListaUzytkownikow.empty()) {
        for(int i=0; i<rozmarVectora; ++i) {
            if(ListaUzytkownikow[i].login==login) {
                cout<<"Juz istnieje uzytkonik o tym loginie\n"<<endl;
                return;
            }
        }
    }
    dodanieUzytkonikowDoVectora(iloscUzytkownikow,login,haslo);
    iloscUzytkownikow++;
    cout<<"Udalo sie! Mozesz teraz sie zalogowac.\n"<<endl;
}
void logowanie() {

    if(ListaUzytkownikow.empty()) {
        cout<<"Nie ma zadnych uzytkonwikow zarejestrowanych.\n"<<endl;
        return;
    }
    string login,haslo;
    int rozmiarVectora=ListaUzytkownikow.size();
    uzytkownik *zalogowanyUzytkownik;
    cout<<"logowanie\n"<<endl;
    cout<<"Login: ";
    cin>>login;
    cout<<"Haslo: ";
    cin>>haslo;
    system("cls");

    for(int i=0; i<rozmiarVectora; ++i) {
        if(ListaUzytkownikow[i].login==login) {
            if(ListaUzytkownikow[i].haslo==haslo) {
                cout<<"Witaj "<<login<<".\n"<<endl;
                zalogowanyUzytkownik=&ListaUzytkownikow[i];
                wyswietlMenuUzytkownika(zalogowanyUzytkownik);
                return;
            }
        }
    }
    cout<<"Zly login lub haslo!\n"<<endl;
}
void zmianaHasla(uzytkownik *zalogowanyUzytkownik) {

    string haslo, haslo2;
    uzytkownik ZmanaUzytkownika;
    int iloscKont=ListaUzytkownikow.size();
    cout<<"podaj nowe haslo: ";
    cin>>haslo;
    cout<<"powtorz haslo: ";
    cin>>haslo2;

    system("cls");
    if(haslo!=haslo2) {
        cout<<"Hasla nie sa takie same!";
        return;
    }
    ZmanaUzytkownika= {zalogowanyUzytkownik->id,zalogowanyUzytkownik->login,haslo};
    for(int i=0; i<iloscKont; ++i) {
        if(zalogowanyUzytkownik->id==ListaUzytkownikow[i].id) {
            ListaUzytkownikow.erase(ListaUzytkownikow.begin()+i);
            ListaUzytkownikow.insert(ListaUzytkownikow.begin()+i,ZmanaUzytkownika);
            cout<<"Haslo zostalo zmienione.\n"<<endl;
            return;
        }
    }
}
void zapisUzytkownikowDoPliku() {


    ofstream plik;
    plik.open("Adresaci.txt", ios::out);
    for(int i=0; i<iloscUzytkownikow-1; ++i) {

        plik<<ListaUzytkownikow[i].id<<"|";
        plik<<ListaUzytkownikow[i].login<<"|";
        plik<<ListaUzytkownikow[i].haslo<<"|"<<endl;

    }
    plik.close();
}
void dodajDoPlikuNowyKontakt() {

    ofstream plik;
    plik.open("Ksiazka_adresowa.txt", ios::app);
    int numerOstatniegoKontaktu=ListaKontakow.size()-1;
    plik<<ListaKontakow[numerOstatniegoKontaktu].id<<"|";
    plik<<ListaKontakow[numerOstatniegoKontaktu].idUzytkownika<<"|";
    plik<<ListaKontakow[numerOstatniegoKontaktu].imie<<"|";
    plik<<ListaKontakow[numerOstatniegoKontaktu].nazwisko<<"|";
    plik<<ListaKontakow[numerOstatniegoKontaktu].numer_telefonu<<"|";
    plik<<ListaKontakow[numerOstatniegoKontaktu].email<<"|";
    plik<<ListaKontakow[numerOstatniegoKontaktu].adres<<"|"<<endl;


    plik.close();
}
void modyfikujPlikTekstowy(int numerPozycjiKontaktu) {

    fstream plik,plikTymcasowy;
    string linia;
    char buffor[50];
    int idKontaktuZPliku,numerek,ilosc1;
    plik.open("Ksiazka_adresowa.txt", ios::in);
    plikTymcasowy.open("Adresaci_tymczasowy.txt",ios::out);
    plik.seekg(0,ios::beg);
    while(getline(plik,linia)) {
        numerek=linia.find("|");
        ilosc1=linia.copy(buffor,numerek,0);
        buffor[ilosc1]='\0';
        idKontaktuZPliku=atoi(buffor);
        if(idKontaktuZPliku==ListaKontakow[numerPozycjiKontaktu].id) {
            plikTymcasowy<<ListaKontakow[numerPozycjiKontaktu].id<<"|";
            plikTymcasowy<<ListaKontakow[numerPozycjiKontaktu].idUzytkownika<<"|";
            plikTymcasowy<<ListaKontakow[numerPozycjiKontaktu].imie<<"|";
            plikTymcasowy<<ListaKontakow[numerPozycjiKontaktu].nazwisko<<"|";
            plikTymcasowy<<ListaKontakow[numerPozycjiKontaktu].numer_telefonu<<"|";
            plikTymcasowy<<ListaKontakow[numerPozycjiKontaktu].email<<"|";
            plikTymcasowy<<ListaKontakow[numerPozycjiKontaktu].adres<<"|"<<endl;
        } else {
            plikTymcasowy<<linia<<endl;
        }

    }
    plik.close();
    remove("Ksiazka_adresowa.txt");
    plikTymcasowy.close();
    rename("Adresaci_tymczasowy.txt", "Ksiazka_adresowa.txt");
    plik.close();

}
void usunKontaktZPliku(int idUsunietegoKontaktu) {

    int idKontaktu,numerek,ilosc1;
    string linia;
    char buffor[50];
    fstream plik,plikTymcasowy;
    plik.open("Ksiazka_adresowa.txt", ios::in);
    plikTymcasowy.open("Adresaci_tymczasowy.txt",ios::out);
    plik.seekg(0,ios::beg);

    while(getline(plik,linia)) {
        numerek=linia.find("|");
        ilosc1=linia.copy(buffor,numerek,0);
        buffor[ilosc1]='\0';
        idKontaktu=atoi(buffor);
        if(idKontaktu!=idUsunietegoKontaktu) {
            plikTymcasowy<<linia<<endl;
        }
    }

    plik.close();
    remove("Ksiazka_adresowa.txt");
    plikTymcasowy.close();
    rename("Adresaci_tymczasowy.txt", "Ksiazka_adresowa.txt");

}
void sprawdzId() {

    fstream plik;
    plik.open("Ksiazka_adresowa.txt", ios::in);
    if (plik.good()==false) {
        numer_Id=0;
        return;
    }
    string linia;
    char buffor[50];
    int numerek,ilosc1,id;
    plik.seekg(0,ios::beg);
    while(getline(plik,linia)) {
        numerek=linia.find("|");
        ilosc1=linia.copy(buffor,numerek,0);
        buffor[ilosc1]='\0';
        id=atoi(buffor);
        numer_Id=id;
    }
    plik.close();
}
