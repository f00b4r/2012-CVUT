//============================================================================
// Name        : Uloha3.cpp
// Author      : vikturek
// Description : Reseni ulohy 3. Slozitejsi verze s kontrolou vstupnich hodnot
//             : a vsech argumentu predanych z prikazove radky.
//============================================================================

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void tiskniPouziti() {
    cout << endl << "Pouziti: Uloha3 velikostZasobniku maxCislo prikazovySoubor" << endl;
}

// Trida pouzita z predchozich cviceni

class Number {
    int hodnota;
    bool hodnotaInicializovana;
public:

    Number() {
        hodnotaInicializovana = false;
    }

    Number(int hodnota) {
        this->hodnota = hodnota;
        hodnotaInicializovana = true;
    }

    void printBinary() {
        if (hodnotaInicializovana) {
            // Pole pro ulozeni binarnih cifer, jeho velikost je pocet bitu v datovem typu int
            int binar[sizeof (int) * 8];
            int zbytek = hodnota;
            int i;
            // Cyklus vypocita jednotilive rady binarniho reprezentace cisla
            for (i = 0; zbytek > 0; i++) {
                binar[i] = zbytek % 2;
                zbytek /= 2;
            }
            // Doplneneni na nuly zleva na delku datoveho typu int
            for (int j = 0; j < (sizeof (int) * 8) - i; ++j) {
                cout << "0";
            }
            // Tisk samotneho binarniho cisla
            for (i--; i >= 0; i--) {
                std::cout << binar[i];
            }
            std::cout << std::endl;
        } else {
            std::cout << "Error! Number - neinicializovana hodnota" << std::endl;
            exit(1);
        }

    }

    int getHodnota() {
        return hodnota;
    }

};

class Zasobnik {
    int velikost;
    int maxCislo;
    vector<Number> cisla;
    int top;
public:

    Zasobnik(int _velikost, int _maxCislo) {
        velikost = _velikost;
        maxCislo = _maxCislo;
        // Pro zasobik pouziji stalou velikost vektoru cisla.
        // Neni to nutne, ale pridavani a odebirani prvku se 
        // pak musi vyresit dynamicky (pouziti push_back() a
        // pop_back()).
        cisla.resize(velikost);
        top = -1;
    }

    void push(Number cislo) {
        if (cislo.getHodnota() <= maxCislo and top + 1 < velikost) {
            top++;
            cisla[top] = cislo;
        }
    }

    Number pop() {
        top--;
        return cisla[top + 1];
    }
    // Vnitrek metody obsahuje upraveny kod z predchoziho cviceni

    void tiskni() {
        cout << setw(11) << left << "Dec";
        cout << setw(9) << "Hex";
        cout << setw(9) << "HexRight";
        cout << setw(9) << "HexFill";
        cout << "Binary" << endl;
        cout << setw(70) << setfill('-') << "-" << setfill(' ') << endl;
        for (int i = 0; i < top + 1; ++i) {
            cout << setw(10) << dec << cisla[i].getHodnota() << " ";
            cout << setw(8) << hex << cisla[i].getHodnota() << " ";
            cout << setw(8) << right << cisla[i].getHodnota() << " ";
            cout << setw(8) << setfill('0') << cisla[i].getHodnota() << left << setfill(' ') << " ";
            cisla[i].printBinary();
        }
    }
};

int main(int argc, char **argv) {
    stringstream ss;
    int velikost;
    int maxCislo;
    ifstream prikazovySoubor;
    string radek, token;

    if (argc < 4) {
        tiskniPouziti();
        return 1;
    }
    ss.str(string(argv[1]));
    ss >> velikost;
    if (ss.fail()) {
        tiskniPouziti();
        return 1;
    }
    ss.clear();
    ss.str(string(argv[2]));
    ss >> maxCislo;
    if (ss.fail()) {
        tiskniPouziti();
        return 1;
    }
    prikazovySoubor.open(argv[3]);
    if (!prikazovySoubor.is_open()) {
        cout << endl << "Nemohu otevrit prikazovy soubor: " << argv[3] << endl;
        return 1;
    }

    Zasobnik zasobnik(velikost, maxCislo);
    int cislo;

    while (1) {
        // Vstup je nacitan radek po radku. V tomto pripade to neni nutne, 
        // protoze potrebne hodnoty lze nacitat primo ze souboru 
        // prikazovySoubor (viz reseni ulohy 4). getline() je zde pouzita
        // pouze z demonstracnich duvodu.
        getline(prikazovySoubor, radek);
        if (prikazovySoubor.fail()) {
            cout << endl << "Parsovani souboru se nepodarilo." << endl;
            return 1;
        }
        ss.clear();
        ss.str(radek);
        ss >> token;
        if (ss.fail()) {
            cout << endl << "Parsovani souboru se nepodarilo kvuli prazdnemu radku." << endl;
            return 1;
        }
        if (token == string("PUSH")) {
            ss >> cislo;
            if (ss.fail()) {
                cout << endl << "Parsovani souboru se nepodarilo. Po PUSH je ocekavano cislo." << endl;
                return 1;
            }
            zasobnik.push(cislo);
        } else if (token == string("POP")) {
            zasobnik.pop();
        } else if (token == string("EXIT")) {
            break;
        } else {
            cout << endl << "Parsovani souboru se nepodarilo. Nalezl jsem radek s neznamym prikazem." << endl;
            return 1;
        }

    }
    zasobnik.tiskni();

    return 0;
}
