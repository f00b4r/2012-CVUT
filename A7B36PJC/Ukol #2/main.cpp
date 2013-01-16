/*
 * BinarySnakeMatrix.h
 *
 * Created on: Nov 29, 2012
 * Author: Milan Sulc <sulcmil1@fel.cvut.cz>
 */

// Tento soubor slouzi k editaci a odevdani vaseho kodu.
#ifndef BINARYSNAKEMATRIX_H_
#define BINARYSNAKEMATRIX_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

using namespace std;

// Zde je prostor pro Vas doprovodny kod
const char* INPUT_ERROR_MESSAGE = "Spatny vstup.";

class SnakeRotationMatrix {
protected:
    bool vlevo;
    bool valid;
    int bajty;
    int bity;
    const char* inp;
    const char* out;
    unsigned char zrcadlo[256];

    /**
     * @param pole
     * @param M
     */
    void prohodSudeRadky(unsigned char* pole, int M) {
        for (int radek = 1; radek < M; radek += 2) {
            for (int sloupec = 0; sloupec < M / 2; sloupec++) {
                // prohodim prvky A[radek][sloupec] a A[redek][M-sloupec-1]

                unsigned char x = pole[ radek * M + sloupec ];
                pole[ radek * M + sloupec ] = pole[ radek * M + (M - sloupec - 1) ];
                pole[ radek * M + (M - sloupec - 1) ] = x;
            }
            // prohodim bity v prohazovanem radku
            for (int sloupec = 0; sloupec < M; sloupec++)
                pole[ radek * M + sloupec ] = zrcadlo[ pole[ radek * M + sloupec ] ];
        }
    }

    /**
     * @param pole
     * @param M
     * @param bajty
     */
    void posunBajtyVlevo(unsigned char* pole, int M, int bajty) {
        int len = M * M - bajty;
        unsigned char* x = (unsigned char*) malloc(bajty);
        memcpy(x, pole, bajty);
        memmove(pole, pole + bajty, len);
        memcpy(pole + len, x, bajty);
        free(x);
    }

    /**
     * @param pole
     * @param M
     * @param bajty
     */
    void posunBajtyVpravo(unsigned char* pole, int M, int bajty) {
        int len = M * M - bajty;
        unsigned char* x = (unsigned char*) malloc(bajty);
        memcpy(x, pole + len, bajty);
        memmove(pole + bajty, pole, len);
        memcpy(pole, x, bajty);
        free(x);
    }

    /**
     * @param pole
     * @param M
     * @param bity
     */
    void posunBityVlevo(unsigned char* pole, int M, int bity) {
        int len = M * M - 1;
        int zbyle_bity = 8 - bity;
        unsigned char x = pole[0];

        for (int i = 0; i < len; i++) {
            pole[i] <<= bity; // posunu vlevo obsah policka
            pole[i] |= pole[i + 1] >> zbyle_bity; // pridam na uvolnene misto to, co preteklo zprava
        }
        // dodelam posledni policko
        pole[len] <<= bity;
        pole[len] |= x >> zbyle_bity;
    }

    /**
     * @param pole
     * @param M
     * @param bity
     */
    void posunBityVpravo(unsigned char* pole, int M, int bity) {
        int len = M * M - 1;
        int zbyle_bity = 8 - bity;
        unsigned char x = pole[len];

        for (int i = len; i > 0; i--) {
            pole[i] >>= bity; // posunu vpravo obsah policka
            pole[i] |= pole[i - 1] << zbyle_bity; // pridam na uvolnene misto to, co preteklo zleva
        }
        // dodelam posledni policko
        pole[0] >>= bity;
        pole[0] |= x << zbyle_bity;
    }

public:

    SnakeRotationMatrix(int argc, char **argv) {

        // Zde je treba doimplementovat parsovani 
        // vstupu a detekovat spatne vstupy
        if ((argc < 6)
                || (atoi(argv[3]) > 7 || atoi(argv[3]) < 0)
                || (atoi(argv[2]) < 0)) {
            valid = false;
        } else if (strcmp(argv[1], "left") == 0 || strcmp(argv[1], "right") == 0) {
            valid = true;
        } else {
            valid = false;
        }

        // bsm <left|right> bytes bites inputMatrixFile outputMatrixFile [showSpeed]
        vlevo = (argv[1][0] == 'l');
        bajty = atoi(argv[2]);
        bity = atoi(argv[3]);
        inp = argv[4];
        out = argv[5];

        // priprava zrcadla pro rychle preklapeni obsahu jednoho bajtu
        for (int i = 0; i < 256; i++) {
            unsigned char j = 0;
            j |= (i & 1) << 7;
            j |= (i & 2) << 5;
            j |= (i & 4) << 3;
            j |= (i & 8) << 1;
            j |= (i & 16) >> 1;
            j |= (i & 32) >> 3;
            j |= (i & 64) >> 5;
            j |= (i & 128) >> 7;
            zrcadlo[i] = j;
        }

    }

    void rotate() {
        try {
            if (!valid) throw 1; // osetreni chyby spatnych vstupu

            // Metoda provede rotaci matice a ulozi vyslednou matici
            FILE *fin = fopen(inp, "rb");
            if (fin == NULL) throw 2; // osetreni chyby ze input file nelze otevrit

            fseek(fin, 0, SEEK_END); // skok na konec
            int velikost = ftell(fin); // jak je soubor veliky
            fseek(fin, 0, SEEK_SET); // skok zpet na zacatek
            
            int M = (int) sqrt(velikost);
            if (bajty > (velikost - 1)) throw 3; // osetreni chyby ze M*M <> velikost
            
            // osetreni chyby ze pocet bytu matice neni druhou mocninou cisla
            if (((int) M*M) != (int) (velikost)) throw 5; 
            
            unsigned char *pole = (unsigned char*) malloc(velikost);

            fread(pole, 1, velikost, fin); // osetrit fread nevratilo velikost
            fclose(fin);

            prohodSudeRadky(pole, M); // normalizujeme pole

            if (vlevo) {
                //printf("vlevo %i\n", bajty);
                posunBajtyVlevo(pole, M, bajty);
                posunBityVlevo(pole, M, bity);
            } else {
                //printf("vpravo %i\n", bajty);
                posunBajtyVpravo(pole, M, bajty);
                posunBityVpravo(pole, M, bity);
            }

            prohodSudeRadky(pole, M); // vratime zpet

            FILE *fou = fopen(out, "wb");
            if (fou == NULL) throw 4;
            fwrite(pole, velikost, 1, fou); // zapiseme pole ven
            fclose(fou);
            free(pole);
        } catch (int e) {
            writeInvalidInput();
        }
    }

    void writeInvalidInput() {
        cout << INPUT_ERROR_MESSAGE << endl;
    }

    ~SnakeRotationMatrix() {
        // Zde po sobe muzete uklidit, pokud tak nedelate v metode rotate
    }
};

#endif /* BINARYSNAKEMATRIX_H_ */

