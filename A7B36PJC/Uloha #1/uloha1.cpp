//============================================================================
// Jmeno       : Uloha1.cpp
// Author      : vikturek
// Popis       : Uloha na procviceni trid a zakladnich rysu jazyka C++
//============================================================================

/*
 * Zadani ulohy
 *
 * Vasim ukolem je doplnit kod tridy Number tak, aby sel prelozit
 * a vypsal nasledujici vystup:
 *
 * Cvicna aplikace pro cviceni 3
 *
 * Error!
 * Error!
 * Binarni hodnota cisla 3000 je 101110111000
 * Binarni hodnota cisla 1000 je 1111101000
 *
 */


#include <iostream>	// Hlavickovy soubor potrebny pro praci se vstupem a vystupem

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

    void printBinary() {
        if (setted == 0) {
            std::cout << "Error" << std::endl << std::endl;
        } else {
            int code[32];
            int rest = 0;
            int tn = number;
            int pos = 0;

            // vydelit
            while (tn > 0) {
                rest = tn % 2;
                tn = tn / 2;
                code[pos++] = rest;
            }

            // otocit posloupnost
            for (int i = pos - 1; i >= 0; i--) {
                std::cout << code[i];
            }

            // odradkovani
            std::cout << std::endl;


        }
    }

    void _printBinary() {
        int code[32];
        int tn = number;
        int pos = 0;
        int mask = 1;

        // vydelit
        while (tn > 0) {
            code[pos++] = ((tn & mask) == 0 ? 0 : 1);
            tn = tn >> mask; // alias tn%2
        }

        // otocit posloupnost
        for (int i = pos - 1; i >= 0; i--) {
            std::cout << code[i];
        }

        // odradkovani
        std::cout << std::endl;
    }

    void set(int number) {
        this->number = number;
        this->setted = 1;
    }
};

// Zde schvalne chybi strednik, aby bylo videt jakou chybu to zpusobi

int main() {

    std::cout << "Cvicna aplikace pro cviceni 3" << std::endl << std::endl;

    Number n1; // Vytvori novou instanci tridy Number

    // ****************************************************************
    // Zbyle zakomentovane radky odkomentovavejte postupne, podle toho
    // jak budete postupovat v impementaci tridy Number.
    // ****************************************************************

    Number n2(1000); // Vytvori dalsi instanci tridy Number, tentokrat s konstruktorem
    n1.plus(n2); // Vypise chybovou hlasku "Error!", protoze v n1 neni zatim zadna hodnota
    n1.printBinary(); // Vypise chybovou hlasku "Error!", protoze v n1 neni zatim zadna hodnota
    n1.set(2000); // Do n1 je vlozena hodnota 1000
    n1.plus(n2); // K hodnote v n1 se pricte hodnota z n2
    n1.printBinary(); // Vytiskne hodnotu ulozenou v n1 v binarni podobe
    n1._printBinary(); // Vytiskne hodnotu ulozenou v n1 v binarni podobe
    n2.printBinary(); // Vytiskne hodnotu ulozenou v n2 v binarni podobe
    n2._printBinary(); // Vytiskne hodnotu ulozenou v n2 v binarni podobe

    return 0;
} 