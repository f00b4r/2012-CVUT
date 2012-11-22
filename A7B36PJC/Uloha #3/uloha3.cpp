//============================================================================
// Name        : Uloha3.cpp
// Author      : vikturek
// Zadani      : Dokoncete zdrojovy kod. Trida Zasobnik implementuje zasobnik
//               na kladna cela cisla mensi nez _maxCislo a cely zasobnik ma
//               hloubku _hloubka. Do zasobniku se ukladaji cisla pomoci tridy 
//               Number z ulohy 2. Zasobnik ma navic metodu tiskni(), ktera
//               cely zasobnik vytiskne v tabulce z ulohy 2. Funkce main() prebira
//               z prikazove radky tri parametry. Prvnim je hloubka zasobniku,
//               druhym maximalni hodnota v zasobniku a tretim je soubor
//               s prikazy. Prikazy jsou dohromady tri a kazdy lezi vzdy na
//               jednom radku. Prvni je ve tvaru "PUSH cislo". Misto "cislo"
//               je uvedena samozrejme ciselna hodnota a prikaz rika, ze se ma
//               do zasobniku vlozit ono cislo. Druhy prikaz je "POP". Ten
//               pouze vytahne hodnotu z vrcholu zasobniku. Posledni prikaz je
//               "EXIT" a znamena konec prikazu.
//
//               Pri testovani spoustejte aplikaci s parametry:
//               ./Uloha3 5 20 prikazy.txt
/*               Soubor s prikazy prikazy.txt vypada takto:
PUSH 1
PUSH 30
PUSH 20
PUSH 3
PUSH 8
PUSH 19
PUSH 11
PUSH 13
POP
PUSH 13
POP
POP
POP
PUSH 18
EXIT
 *//*            Na tento vstup by mela aplikace reagovat takto:

Dec        Hex      HexRight HexFill  Binary
----------------------------------------------------------------------
1          1               1 00000001 00000000000000000000000000000001
20         14             14 00000014 00000000000000000000000000010100
18         12             12 00000012 00000000000000000000000000010010

*/
//============================================================================

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void tiskniPouziti() {
    cout << endl << "Pouziti: Uloha3 velikostZasobniku maxCislo prikazovySoubor" << endl;
}

class Number {
public:

    int number;
    int setted;

    Number() {
        this->setted = 0;
    }

    Number(int number) {
        this->number = number;
        this->setted = 1;
    }

    void plus(Number other) {
        if (setted == 0) {
            std::cout << "Error" << std::endl;
        } else {
            std::cout << number + other.number << std::endl;
        }
    }

    string printBinary() {
        unsigned mask = 0x80000000;
        bool skipZeros = true;
        string r;
        for (unsigned i = 0; i < sizeof (int) * 8; ++i) {
            if ((mask & this->number) == 0) {
                if (!skipZeros) {
                    r.append("0");
                }
            } else {
                skipZeros = false;
                r.append("1");
            }
            mask = mask >> 1;
        }
        return r;
    }

    void set(int number) {
        this->number = number;
        this->setted = 1;
    }

    int get() {
        return this->number;
    }
};

class Tabulka {
public:

    void delimiter(int size) {
        for (int i = 0; i < size; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }

    void word(string s, int size) {
        std::cout << s;
        for (int i = 0; i < (size - s.length()); i++) {
            std::cout << " ";
        }
    }

    void printTable(vektor<Number> cisla) {
        this->word("Dec", 11);
        this->word("Hex", 9);
        this->word("HexRight", 9);
        this->word("HexFill", 9);
        this->word("Binary", 32);

        std::cout << std::endl;

        this->delimiter(70);
        /**************************************
         * 	Zde doplnte kod pro vypis hlavicky
         **************************************/
        for (unsigned int i = 0; i < cisla.size(); ++i) {

            /*******************************************************
             * 	Zde doplnte kod pro vytisknuti jednoho radku tabulky
             *
             *******************************************************/

            // Dec
            cout.width(10);
            cout << left << cisla.at(i).get();

            // Mezera
            cout << " ";

            // Hex
            cout.width(8);
            cout << left << hex << cisla.at(i).get();

            // Mezera
            cout << " ";

            // HexRight
            cout << setw(8);
            cout << right << hex << cisla.at(i).get();

            // Mezera
            cout << " ";

            // HexFill
            cout << setfill('0') << setw(8);
            cout << hex << cisla.at(i).get();
            cout << setfill(' ');

            // Mezera
            cout << " ";

            // Binary
            cout << setfill('0') << setw(32);
            cout << (cisla.at(i).printBinary());
            cout << setfill(' ');

            cout << endl;
        }

    }

};

/****************************************************************************
 *  Tridu zasobnik dokoncete dle pokynu v zadani.
 ****************************************************************************/

class Zasobnik {
    vektor<Number> cisla;
    int _hloubka;
    int _maxCislo;
    int _cursor;
public:

    Zasobnik(int _hloubka, int _maxCislo) {
        this->_hloubka = _hloubka;
        this->_maxCislo = _maxCislo;
        this->_cursor = -1;
    }

    void push(Number cislo) {
        if (cislo.get() > _maxCislo || _cursor >= _hloubka - 1) {
            //cout << "Uz neberu cislo: " << cislo.get() << endl;
            return;
        }

        //cout << "Vkladam : " << cislo.get() << endl;
        _cursor++;
        cisla.push_back(cislo);
    }

    Number pop() {
        Number n = cisla[_cursor];
        _cursor--;
        cisla.pop_back();
        return n;
    }

    void tiskni() {
        for (int i = 0; i < cisla.size(); i++) {
            cout << "Cislo = " << cisla.at(i).get() << endl;
        }

        Tabulka t;
        t.printTable(cisla);
    }
};

int main(int argc, char **argv) {
    stringstream ss;
    int hloubka;
    int maxCislo;
    ifstream prikazovySoubor;

    if (argc < 4) {
        tiskniPouziti();
        return 1;
    }

    // Cteni parametru
    ss << argv[1];
    ss >> hloubka;
    ss.clear();

    ss << argv[2];
    ss >> maxCislo;
    ss.clear();

    prikazovySoubor.open(argv[3]);


    // Print
    //    std::cout << "Pocet parametru: " << argc << endl;
    //    std::cout << "Param 0 " << argv[0] << endl;
    //    std::cout << "Param 1 " << argv[1] << endl;
    //    std::cout << "Param 2 " << argv[2] << endl;
    //    std::cout << "Param 3 " << argv[3] << endl;
    //    
    //    std::cout << "Hloubka: " << hloubka << endl;
    //    std::cout << "Max cislo: " << maxCislo << endl;


    /*************************************************************************
     *  Zde je treba zpracovat argumenty, tedy prvni dva prevest na cislo
     *  typu integer a pomoci tretiho otevrit soubor se vstupnimi daty.
     *************************************************************************/

    Zasobnik zasobnik(hloubka, maxCislo);

    string line;
    string toks[3];
    string sep;
    if (prikazovySoubor.is_open()) {
        cout << "Oteviram soubor";
        while (prikazovySoubor.good()) {
            getline(prikazovySoubor, line);
            stringstream ss(line);
            ss >> toks[0] >> sep >> toks[1] >> sep >> toks[2] >> sep;
            cout << "Radek " << line << endl;
            cout << "Token 0 = " << toks[0] << " token 1 = " << toks[1] << " token 2 = " << toks[2] << endl;
            if (toks[0] == "PUSH") {
                zasobnik.push(Number(8));
            } else if (toks[0] == "POP") {
                zasobnik.pop();
            }
        }
        prikazovySoubor.close();
        cout << "Zaviram soubor";
    }

    //    zasobnik.push(Number(1));
    //    zasobnik.push(Number(30));
    //    zasobnik.push(Number(20));
    //    zasobnik.push(Number(3));
    //    zasobnik.push(Number(8));
    //    zasobnik.push(Number(19));
    //    zasobnik.push(Number(11));
    //    zasobnik.push(Number(13));
    //    zasobnik.pop();
    //    zasobnik.push(Number(13));
    //    zasobnik.pop();
    //    zasobnik.pop();
    //    zasobnik.pop();
    //    zasobnik.push(Number(18));
    zasobnik.tiskni();

    /*************************************************************************
     *  Zde je treba zpracovat soubor s prikazy
     *************************************************************************/

    return 0;
}
