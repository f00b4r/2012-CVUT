//============================================================================
// Name        : Uloha2.cpp
// Author      : vikturek
// Popis       : Program nacita cela cisla dokud nedostane spatny vstup, nebo
//				 nenajde konec souboru. Potom vytiskne serazena cisla, kazde
//				 na jednom radku.
// Ukol        : Doplnte kod tak, aby na soubor vstupnich dat "vstup.txt"
// 				 vypsal naprosto presne nasledujici tabulku:
/*
Dec        Hex      HexRight HexFill  Binary
----------------------------------------------------------------------
5          5               5 00000005 00000000000000000000000000000101
6          6               6 00000006 00000000000000000000000000000110
23         17             17 00000017 00000000000000000000000000010111
45         2d             2d 0000002d 00000000000000000000000000101101
89         59             59 00000059 00000000000000000000000001011001
2147483647 7fffffff 7fffffff 7fffffff 01111111111111111111111111111111
 */
//				 Vstupni data jsou i zde:
/*
2147483647
23 45 6


89    5


 */
// Napoveda    : Podivejte se na cinnost manipulatoru setw(), setfill(), right,
//               left, hex, dec. Pro vypis binarni hodnoty upravte svuj kod
//               z ulohy 1.
//============================================================================

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Tabulka {
public:

    static string printBinary2(int hodnota) {
        unsigned mask = 0x80000000;
        bool skipZeros = true;
        string r;
        for (unsigned i = 0; i < sizeof (int) * 8; ++i) {
            if ((mask & hodnota) == 0) {
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

    static void delimiter(int size) {
        for (int i = 0; i < size; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }

    static void word(string s, int size) {
        std::cout << s;
        for (int i = 0; i < (size - s.length()); i++) {
            std::cout << " ";
        }
    }

    static string right(string s, int size) {
        string result;
        for (int i = 0; i < (size - s.length()); i++) {
            result.append(" ");
        }
        result.append(s);
        return result;
    }

    static void printTable(vector<Number> cisla) {
        Tabulka::word("Dec", 11);
        Tabulka::word("Hex", 9);
        Tabulka::word("HexRight", 9);
        Tabulka::word("HexFill", 9);
        Tabulka::word("Binary", 32);

        std::cout << std::endl;

        Tabulka::delimiter(70);
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
            cout << Tabulka::printBinary2(cisla.at(i).get());
            cout << setfill(' ');

            cout << endl;
        }

    }

};

int main() {
    vector<int> cisla;
    int cislo;

    string s;
    cin >> s;
    while (!cin.eof() && cin.good()) {
        cin >> s;

        cisla.push_back(cislo);
        cin >> cislo;
    };
    sort(cisla.begin(), cisla.end());

    Tabulka::word("Dec", 11);
    Tabulka::word("Hex", 9);
    Tabulka::word("HexRight", 9);
    Tabulka::word("HexFill", 9);
    Tabulka::word("Binary", 32);

    std::cout << std::endl;

    Tabulka::delimiter(70);
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
        cout << left << cisla[i];

        // Mezera
        cout << " ";

        // Hex
        cout.width(8);
        cout << left << hex << cisla[i];

        // Mezera
        cout << " ";

        // HexRight
        cout << setw(8);
        cout << right << hex << cisla[i];

        // Mezera
        cout << " ";

        // HexFill
        cout << setfill('0') << setw(8);
        cout << hex << cisla[i];
        cout << setfill(' ');

        // Mezera
        cout << " ";

        // Binary
        cout << setfill('0') << setw(32);
        cout << Tabulka::printBinary2(cisla[i]);
        cout << setfill(' ');

        cout << endl;
    }

    return 0;
}
