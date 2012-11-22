//============================================================================
// Name        : Uloha4.cpp
// Author      : vikturek
// Description : Uloha k procviceni ukazatelu, predavani parametru odkazem a
//               praci se staticky alokovanym polem. Reseni kontroluje vsechny
//               vstupy a zapisy v pameti mimo alokovanou oblast.
//============================================================================

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void tiskniPouziti() {
    cout << endl
            << "Pouziti: Uloha3 velikostZasobniku maxCislo prikazovySoubor"
            << endl;
}

class Number {
    int hodnota;
    bool hodnotaInicializovana;
    int binary[sizeof (int) * 8];

    void toBinary(int cislo) {
        int zbytek = cislo;

        for (unsigned int i = 0; i < sizeof (int) * 8; ++i) {
            binary[i] = 0;
        }
        for (int i = sizeof (int) * 8 - 1; zbytek > 0; --i) {
            binary[i] = zbytek % 2;
            zbytek /= 2;
        }
    }
public:

    Number() {
        hodnotaInicializovana = false;
    }

    Number(int hodnota) {
        this->hodnota = hodnota;
        hodnotaInicializovana = true;
        toBinary(hodnota);
    }

    void setHodnota(int hodnota) {
        this->hodnota = hodnota;
        hodnotaInicializovana = true;
        toBinary(hodnota);
    }

    void printBinary() {
        if (hodnotaInicializovana) {
            for (unsigned int i = 0; i < sizeof (int) * 8; ++i) {
                cout << binary[i];
            }
            cout << endl;
        } else {
            cout << endl << "Error! Number - neinicializovana hodnota" << endl;
            return;
        }

    }

    int getHodnota() {
        if (hodnotaInicializovana) {
            return this->hodnota;
        } else {
            cout << endl << "Error! Number - neinicializovana hodnota" << endl;
            exit(1);
        }
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
        cisla.resize(velikost);
        top = -1;
    }

    void push(Number *cislo) {
        if (cislo->getHodnota() <= maxCislo and top + 1 < velikost) {
            top++;
            cisla[top] = *cislo;
        }
    }

    Number pop() {
        top--;
        if (top + 1 < 0) {
            cout << "Zasobnik je prazdny. Nemohu provest POP." << endl;
            exit(1);
        }
        return cisla[top + 1];
    }

    void tiskni() {
        cout << endl << endl;
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
            cout << setw(8) << setfill('0') << cisla[i].getHodnota() << left
                    << setfill(' ') << " ";
            cisla[i].printBinary();
        }
    }
};

#define MEMORY_SIZE 1024

class Memory {
    char memo[MEMORY_SIZE];
public:

    int write(char *data, unsigned size, int address) {
        if (address < 0) {
            cout << endl << "Memory::write(): Parametr 'address' je mensi nez 0!" << endl;
            return -1;
        }
        if (address + size > MEMORY_SIZE) {
            cout << endl << "Memory::write(): Malo mista v pameti pro provedeni zapisu." << endl;
            return -2;
        }
        if (data == NULL) {
            cout << endl << "Memory::write(): Misto ukazatele na data byl predan NULL." << endl;
            return -3;
        }
        // Funkce memcpy() kopiruje z ukazatele 'data' pocet bytu o velikosti 'size' na misto
        // kam ukazuje prvni parametr. Prvni parametr je adresa prvku s indexem 'address' od
        // zacatku pameti 'memo'. Volani 'memo[address]' vrati primo prvek (= jeho hodnotu)
        // s indexem 'address'. Adresu tohoto prvku ziskame pomoci &. Oba prvni parametry musi
        // byt pretypovany na univerzalni ukazatel 'void *', ktery je vyzadovan fuknci 'memcpy'.
        memcpy((void *) &memo[address], (void *) data, size);
        return 0;
    }

    Number *getNumber(unsigned adresa) {
        if (adresa < 0 or adresa + sizeof (Number) >= MEMORY_SIZE) {
            cout << endl << "Memory::getNumber(): Cteni by skoncilo mimo alokovanou oblast." << endl;
            exit(1);
        }
        // Vracime adresu prvku s indexem 'address' z pole 'memo'. Protoze ocekavame na tomto
        // miste ulozeny objekt typu 'Number' a zaroven ukazatel na typ na 'Number' je ocekavan
        // jako navratova hodnota, tak je treba tuto adresu pretypovat, aby prosla typova
        // kontrola.
        return (Number *) &memo[adresa];
    }

    void saveToFile(const char *jmeno) {
        ofstream soubor(jmeno);
        if (!soubor.is_open()) {
            cout << "Chyba - nepodarilo se otevrit vystupni soubor: " << jmeno
                    << endl;
            exit(1);
        }
        soubor.write((const char *) memo, MEMORY_SIZE);
        if (soubor.bad()) {
            cout << "Chyba - nepodarilo se zapsat pamet do vystupniho souboru."
                    << endl;
            exit(1);
        }
        soubor.close();
    }

    void loadFromFile(const char *jmeno) {
        ifstream soubor(jmeno);
        if (!soubor.is_open()) {
            cout << "Chyba - nepodarilo se otevrit vstupni soubor: " << jmeno
                    << endl;
            exit(1);
        }
        soubor.read((char *) memo, MEMORY_SIZE);
        if (soubor.bad()) {
            cout << "Chyba - nepodarilo se zapsat pamet do vystupniho souboru."
                    << endl;
            exit(1);
        }
        soubor.close();
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
    Number number;
    Memory memory;
    string jmenoSouboru;

    while (1) {
        prikazovySoubor >> token;
        if (prikazovySoubor.fail()) {
            cout << "Parsovani souboru se nepodarilo." << endl;
            return 1;
        }
        if (token == string("PUSH")) {
            prikazovySoubor >> cislo;
            if (prikazovySoubor.fail()) {
                cout << endl
                        << "Parsovani souboru se nepodarilo. Po PUSH je ocekavano cislo."
                        << endl;
                return 1;
            }
            number.setHodnota(cislo);
            zasobnik.push(&number);
        } else if (token == string("POP")) {
            zasobnik.pop();
        } else if (token == string("STORE")) {
            number = zasobnik.pop();
            prikazovySoubor >> cislo;
            if (prikazovySoubor.fail()) {
                cout << endl
                        << "Parsovani souboru se nepodarilo. Po STORE je ocekavana adresa."
                        << endl;
                return 1;
            }
            int returnHodnota = memory.write((char *) &number, sizeof (number), cislo);
            if (returnHodnota != 0) {
                return 1;
            }
        } else if (token == string("PRINT")) {
            prikazovySoubor >> cislo;
            if (prikazovySoubor.fail()) {
                cout << endl
                        << "Parsovani souboru se nepodarilo. Po PRINT je ocekavana adresa."
                        << endl;
                return 1;
            }
            cout << "Binarni hodnota cisla ulozeneho v pameti na adrese "
                    << cislo << " je ";
            memory.getNumber(cislo)->printBinary();
        } else if (token == string("SAVE")) {
            prikazovySoubor >> jmenoSouboru;
            if (prikazovySoubor.fail()) {
                cout << endl <<
                        "Parsovani souboru se nepodarilo. Po SAVE je ocekavan nazev souboru." << endl;
                return 1;
            }
            memory.saveToFile(jmenoSouboru.c_str());
        } else if (token == string("LOAD")) {
            prikazovySoubor >> jmenoSouboru;
            if (prikazovySoubor.fail()) {
                cout << endl <<
                        "Parsovani souboru se nepodarilo. Po LOAD je ocekavan nazev souboru." << endl;
                return 1;
            }
            memory.loadFromFile(jmenoSouboru.c_str());
        } else if (token == string("EXIT")) {
            break;
        } else {
            cout << endl
                    << "Parsovani souboru se nepodarilo. Nalezl jsem radek s neznamym prikazem."
                    << endl;
            return 1;
        }
    }
    return 0;
}

