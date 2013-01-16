/*
 * BSTSET.h
 *
 *  Created on: 28.12.2012
 *      Author: Milan Sulc <sulcmil1@fel.cvut.cz>
 */

#ifndef BSTSET_H_
#define BSTSET_H_

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

/*****************************************************
 *  Zde je misto pra vasi implementaci tridy BSTSET.  *
 *****************************************************/

class BSTSET {
private:
    int uzel;
    int hodnota;
    int pocetvlozeni;
    int min, max;
    BSTSET *leftTree;
    BSTSET *rightTree;

public:

    BSTSET() {
        uzel = 0;
        hodnota = 0;
        pocetvlozeni = 0;
        min = 0;
        max = 0;
        leftTree = 0;
        rightTree = 0;
    };

    BSTSET(int i) {
        uzel = 0;
        hodnota = i;
        pocetvlozeni = 1;
        min = i;
        max = i;
        leftTree = 0;
        rightTree = 0;
    };

    ~BSTSET() {
        uvolnitPamet(this);
    };

    /**
     * Czech: vycisti pamet
     * @param s
     */
    void uvolnitPamet(BSTSET *s) {
        if (s->leftTree) {
            delete s->leftTree;
        }
        if (s->rightTree) {
            delete s->rightTree;
        }
    }

    /**
     * Czech: pro vkládání hodnot
     * @param a
     * @return
     */
    void vloz(int a) {
        int x1 = a;
        int x2 = hodnota;
        if (a > hodnota) {
            x1 = hodnota;
            x2 = a;
        }

        if (!this->uzel) {
            if (pocetvlozeni <= 0) {
                this->hodnota = a;
                this->pocetvlozeni = 1;
                this->min = a;
                this->max = a;
            } else if (this->hodnota == a) {
                this->pocetvlozeni += 1;
            } else {
                this->uzel = 1;
                this->hodnota = INT_MIN;
                this->leftTree = new BSTSET(x1);
                this->rightTree = new BSTSET(x2);
                if (x2 == a) {
                    this->leftTree->pocetvlozeni = pocetvlozeni;
                } else {
                    this->rightTree->pocetvlozeni = pocetvlozeni;
                }
                if (x1 < this->min) {
                    this->min = x1;
                }
                if (x2 > this->max) {
                    this->max = x2;
                }
            }
        } else {
            if (a >= rightTree->min) {
                if (a > max) {
                    max = a;
                }
                this->rightTree->vloz(a);
                return;

            } else if (a < min) {
                min = a;
            }

            this->leftTree->vloz(a);
        }
    }

    /**
     * Czech: pro získání informace o tom, jak hluboko je v binárním vyhledávacím stromu prvek uložen. Pokud se hodnota ve stromu nenachází, vrací -1.
     * @param a
     * @return
     */
    int dejVnoreni(int a) {
        if (uzel == 1) {
            int ret = leftTree->dejVnoreni(a);
            if (ret == 0) {
                ret = rightTree->dejVnoreni(a);
            }
            if (ret > 0) {
                ret = ret + 1;
            }
            return ret;
        } else {
            if (hodnota == a) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    /**
     * Czech: pro ziskání informace o tom, kolikrát je hodnota do množiny již vložena. Pokud se hodnota ve stromu nenachází, vrací -1.
     * @param a
     * @return
     */
    int dejPocetVlozeni(int a) {
        if (uzel == 1) {
            int ret = leftTree->dejPocetVlozeni(a);
            if (ret > 0) {
                return ret;
            } else {
                return rightTree->dejPocetVlozeni(a);
            }
        } else {
            if (hodnota == a) {
                return pocetvlozeni;
            } else {
                return -1;
            }
        }
    }

    /**
     * Czech: vytiskne strom
     */
    void tisk() {
        if (this->uzel) {
            if (leftTree != 0) {
                leftTree->tisk();
            }
            if (rightTree != 0) {
                rightTree->tisk();
            }

        } else {
            cout << this->hodnota << endl;
        }
    }

    /** Override operators **/

    friend std::ostream & operator <<(std::ostream &os, BSTSET & set);

    int operator()(int a) {
        return dejPocetVlozeni(a);
    }

    int operator[](int a) {
        return dejVnoreni(a);
    }

    void operator<<(int a) {
        vloz(a);
    }
};

/**
 * @param os
 * @param set
 * @return 
 */
std::ostream & operator<<(std::ostream &os, BSTSET &set) {
    set.tisk();
    return os;
}

#endif /* BSTSET_H_ */
