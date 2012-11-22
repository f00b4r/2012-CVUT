//============================================================================
// Name        : Uloha5.cpp
// Author      : vikturek
// Description : Uloha k procviceni dynamicke alokace pameti. Navrhnete
//               tridu Pole2D, ktera v sobe bude obsahovat dynamicky alokovane
//               dvourozmerne pole objektu typu Number. Tento objekt bude mit
//               navic dve metody - store a load. Metody slouzi k ulozeni a
//               nacteni Pole2D z objektu typu Memory (vice viz kod). Opet
//               mate k dispozici prikazovy soubor, ktery obsahuje novou sadu
//               prikazu. Celou aplikaci spustite takto:
//               ./Uloha5 2488 prikazy.txt
//               Prvnim parametrem je velikost vnitrni pameti objektu Memory a
//               pri kontrole bude vyzadovana presne tato velikost pameti!

//               Dale upravte tridu Memory tak, aby bylo pole memo alokovano
//               dynamicky podle podle hodnoty z konstrukoru.

//               !!Pozor!! V kodu nesmi vzniknout memory leaky!!!

//               Nove prikazy:
//               MATRIX ALLOCATE <x-rozmer> <y-rozmer>
//               	- alokuje Pole2D pro zadane rozmery, na dalsich radcich
//               	jsou jednotlive polozky dvourozmerneho pole (x-rozmer je
//               	horizontalni a y-rozmer vertikalni)
//               MATRIX PRINT
//               	- vytiskne vsechny prvky z Pole2D ve stejnem poradi, jak
//               	byly zadany prikazovym souborem
//               MATRIX STORE <adresa>
//               	- ulozi data z Pole2D do objektu Memory na adresu 'adresa'
//               MATRIX LOAD <adresa>
//               	- nacte data z objektu Memory z adresy 'adresa' do objektu
//               	Pole2D

//               Ukazka souboru prikazy.txt:
/*
MATRIX ALLOCATE 4 3
5	8	30	23454
345	1435	24352	8576
1234 	4234	36753	0
MATRIX PRINT
MATRIX STORE 832
MATRIX ALLOCATE 4 3
0	0	0	0
0	0	0	0
0	0	0	0
MATRIX PRINT
MATRIX LOAD 832
MATRIX PRINT
MATRIX ALLOCATE 3 2
3	4	6
15	5	9
MATRIX PRINT
MATRIX STORE 0
MATRIX ALLOCATE 4 3
0	0	0	0
0	0	0	0
0	0	0	0
MATRIX LOAD 832
MATRIX PRINT
MATRIX STORE -1
MATRIX STORE 833
EXIT
 */
//               Na tento vstup by mela aplikace reagovat nasledujicim vystupem:
/*
5 8 30 23454
345 1435 24352 8576
1234 4234 36753 0

0 0 0 0
0 0 0 0
0 0 0 0

5 8 30 23454
345 1435 24352 8576
1234 4234 36753 0

3 4 6
15 5 9

5 8 30 23454
345 1435 24352 8576
1234 4234 36753 0

Nepodarilo se ulozit pole2D na adresu -1.
Nepodarilo se ulozit pole2D na adresu 833.
 */
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
    cout << endl << "Pouziti: Uloha5 velikostPameti prikazovySoubor" << endl;
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

#define MEMORY_SIZE 1024

class Memory {
    char *memo;
    int velikostPameti;

public:

    Memory() {
        velikostPameti = MEMORY_SIZE;
        memo = new char[velikostPameti];
    }

    Memory(int velikostPameti) {
        memo = new char[velikostPameti];
        this->velikostPameti = velikostPameti;
    }

    int write(char *data, unsigned size, int address) {
        if (address < 0) {
            cout << endl << "Memory::write(): Parametr 'address' je mensi nez 0!" << endl;
            return -1;
        }
        if (address + size > velikostPameti) {
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
        if (adresa < 0 or adresa + sizeof (Number) >= velikostPameti) {
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
        soubor.write((const char *) memo, velikostPameti);
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

class Pole2D {
    // Tento ukazatel by mel ukazovat na dynamicky alokovane
    // dvourozmerne pole instanci objektu typu Number
    Number **pole2D;

    unsigned x;
    unsigned y;
public:

    Pole2D() {
        x = 0;
        y = 0;
    }

    Pole2D(unsigned _size1D, unsigned _size2D) {
        x = _size1D;
        y = _size2D;
        pole2D = new Number*[_size1D];
        for (int i = 0; i < _size1D; i++) {
            pole2D[i] = new Number[_size2D];
        }

    }
    // Dynamicky alokuje pamet pro dvourozmerne pole

    void allocate(unsigned _size1D, unsigned _size2D) {
        x = _size1D;
        y = _size2D;
        pole2D = new Number*[_size1D];
        for (int i = 0; i < _size1D; i++) {
            pole2D[i] = new Number[_size2D];
        }
    }
    // Nastavi prvkek v poli na dane cislo 'number'
    // Navratova hodnota je 0, kdyz se zapis zdari, nebo
    // cokoliv jineho pokud je vstup mimo rozsah

    void set(unsigned x, unsigned y, int number) {
        pole2D[x][y] = Number(number);
    }
    // Stejne jako set, jen pro cteni prvku

    int get(unsigned x, unsigned y) {
        return pole2D[x][y].getHodnota();
    }
    // Zalohuje vsechna sva data do objektu typu Memory

    int store(Memory &memory, unsigned address) {
        if (address < 0) return -1;

        Number* n = new Number[2];
        n[0] = x;
        n[1] = y;

        memory.write((char *) n, sizeof (Number) * 2, address);
        address += sizeof (Number);
        for (int i = 0; i < y; i++) {
            memory.write((char *) pole2D[i], sizeof (Number) * x, address);
            address += sizeof (Number) * x;
        }
    }

    // Nacte vsechna zva data z objektu Memory

    int load(Memory &memory, unsigned address) {
        cout << "Nacitam data z adresy: " << address << endl;
        Number* data = memory.getNumber(address);
        address += sizeof (Number) * 2;
        cout << "Saham si pro data na adresu: " << address << endl;
        int x = data[0].getHodnota();
        int y = data[1].getHodnota();

        for (int i = 0; i <= y; i++) {
            pole2D[i] = memory.getNumber(address);
            address += sizeof (Number) * x;
        }
    }
    // Vytiskne dvourozmerne pole ve stejnem poradi, jak bylo zadano
    // v prikazovem souboru.

    void print() {
        cout << "Tisknu pole: [" << x << "," << y << "]" << endl;
        if (x > 0 && y > 0) {
            for (unsigned i = 0; i < y; i++) {
                for (unsigned j = 0; j < x; j++) {
                    cout << pole2D[i][j].getHodnota() << " ";
                }
                cout << endl;
            }
            cout << endl;
        } else {
            cout << "Velikost pole je [0,0]";
        }
    }
    // Destruktor, zde je misto pro dealokaci pameti

    ~Pole2D() {
        if (pole2D != NULL) {
            delete [] pole2D;
        }
    }
};

int main(int argc, char **argv) {
    stringstream ss;
    int velikostPameti;
    ifstream prikazovySoubor;
    string token1, token2;

    if (argc < 3) {
        tiskniPouziti();
        return 1;
    }
    ss.str(string(argv[1]));
    ss >> velikostPameti;

    if (velikostPameti != 2488) {
        cout << "Nespravna velikost pameti!" << endl;
        return 1;
    }

    if (ss.fail()) {
        tiskniPouziti();
        return 1;
    }
    ss.clear();
    prikazovySoubor.open(argv[2]);
    if (!prikazovySoubor.is_open()) {
        cout << endl << "Nemohu otevrit prikazovy soubor: " << argv[3] << endl;
        return 1;
    }

    int cislo, size1D, size2D;
    Memory memory(velikostPameti);
    Pole2D pole2D;

    /******************************************************************
     *               Parsovani souboru prikazy.txt                    *
     ******************************************************************/

    int x, y;
    int number;

    while (1) {
        if (prikazovySoubor.fail()) {
            cout << "Parsovani souboru se nepodarilo." << endl;
            return 1;
        }

        prikazovySoubor >> token1;
        prikazovySoubor >> token2;

        if (token1 == string("MATRIX") && token2 == string("ALLOCATE")) {
            prikazovySoubor >> x;
            prikazovySoubor >> y;

            //cout << "Alokuji [" << x << "," << y << "]" << endl;
            pole2D.allocate(x, y);
            for (int i = 0; i < y; i++) {
                for (int j = 0; j < x; j++) {
                    prikazovySoubor >> number;
                    //cout << "Pridavam cislo: [" << i << "," << j << "] " << number << endl;
                    pole2D.set(i, j, number);
                }
            }
        } else if (token1 == string("MATRIX") && token2 == string("PRINT")) {
            //cout << "MATRIX-PRINT" << endl;
            pole2D.print();
            //cout << "MATRIX-PRINT-END" << endl;
        } else if (token1 == string("MATRIX") && token2 == string("STORE")) {
            prikazovySoubor >> number;
            cout << "MATRIX-STORE, address = " << number << endl;

            if (number < 0) {
                cout << "Nepodarilo se ulozit pole2D na adresu " << number << endl;
                continue;
            }

            pole2D.store(memory, number);
        } else if (token1 == string("MATRIX") && token2 == string("LOAD")) {
            //cout << "MATRIX-LOAD" << endl;
            prikazovySoubor >> number;
            pole2D.load(memory, number);
        } else if (token1 == string("EXIT")) {
            cout << "EXIT" << endl;
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
