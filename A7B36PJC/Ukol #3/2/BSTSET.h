/*
 * BSTSET.h
 *
 *  Created on: 5.1.2013
 *      Author: Milan Sulc <sulcmil1@fel.cvut.cz>
 */

#ifndef BSTSET_H_
#define BSTSET_H_

#include <cstdlib>
#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

/*****************************************************
 *  Zde je misto pra vasi implementaci tridy BSTSET.  *
 *****************************************************/
template <class T> class BSTSET {
private:
    int uzel;
    T hodnota;
    int pocetvlozeni;
    T min, max;
    BSTSET *leftTree;
    BSTSET *rightTree;

public:
    class iterator;
    vector<T> v;
    int v_index;

    BSTSET() {
        uzel = 0;
        pocetvlozeni = 0;
        leftTree = 0;
        rightTree = 0;
        v_index = 0;
    };

    BSTSET(T i) {
        uzel = 0;
        hodnota = i;
        pocetvlozeni = 1;
        min = i;
        max = i;
        leftTree = 0;
        rightTree = 0;
        v_index = 0;
    };

    ~BSTSET() {
        uvolnitPamet(this);
    };

    /**
     * Czech: vycisti pamet
     * @param s
     */
    void uvolnitPamet(BSTSET<T> *s) {
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
    void vloz(T a) {
        T x1 = a;
        T x2 = hodnota;
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

    int dejVnoreni(T a) {
        int ret = _dejVnoreni(a);
        if (ret <= 0) {
            return -1;
        }
        return ret;
    }

    /**
     * Czech: pro získání informace o tom, jak hluboko je v binárním vyhledávacím stromu prvek uložen. Pokud se hodnota ve stromu nenachází, vrací -1.
     * @param a
     * @return
     */
    int _dejVnoreni(T a) {
        if (uzel == 1) {
            int ret = leftTree->dejVnoreni(a);
            if (ret <= 0) {
                ret = rightTree->dejVnoreni(a);
            }
            if (ret > 0) {
                ret = ret + 1;
            }
            return ret;
        } else {
            if (hodnota == a && pocetvlozeni > 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    int dejPocetVlozeni(T a) {
        int ret = _dejPocetVlozeni(a);
        if (ret <= 0) {
            return 0;
        }
        return ret;
    }

    /**
     * Czech: pro ziskání informace o tom, kolikrát je hodnota do množiny již vložena. Pokud se hodnota ve stromu nenachází, vrací -1.
     * @param a
     * @return
     */
    int _dejPocetVlozeni(T a) {
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
                return 0;
            }
        }
    }

    int smaz(T a) {
        int ret = 0;
        if (uzel == 1) {
            if ((!leftTree->uzel) && (leftTree->hodnota == a)) {
                if (leftTree->pocetvlozeni > 1) {
                    leftTree->pocetvlozeni -= 1;
                    return 1;
                }
                hodnota = rightTree->hodnota;
                uzel = rightTree->uzel;
                pocetvlozeni = rightTree->pocetvlozeni;
                min = rightTree->min;
                max = rightTree->max;
                delete leftTree;
                leftTree = rightTree->leftTree;
                rightTree = rightTree->rightTree;
                return 1;

            } else if ((!rightTree->uzel) && (rightTree->hodnota == a)) {
                if (rightTree->pocetvlozeni > 1) {
                    rightTree->pocetvlozeni -= 1;
                    return 1;
                }
                hodnota = leftTree->hodnota;
                uzel = leftTree->uzel;
                pocetvlozeni = leftTree->pocetvlozeni;
                min = leftTree->min;
                max = leftTree->max;
                delete rightTree;
                rightTree = leftTree->rightTree;
                leftTree = leftTree->leftTree;
                return 1;
            } else {
                if (!leftTree->smaz(a)) {
                    ret = rightTree->smaz(a);
                } else {
                    min = leftTree->min;
                    max = rightTree->max;
                    ret = 1;
                }
            }
            return ret;
        } else {
            if (hodnota == a) {
                if (pocetvlozeni > 1) {
                    pocetvlozeni -= 1;
                } else {
                    pocetvlozeni = 0;
                }
                return 1;
            }
            return 0;
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
            if (this->pocetvlozeni > 0) {
                cout << this->hodnota << endl;
            }
        }
    }

    /** Iterator **/
    class BSTSET<T>::iterator begin() {
        v.clear();
        fillVector(&v);
        v_index = 0;
        return iterator(v, 0);
    }

    class BSTSET<T>::iterator end() {
        return iterator(v, v.size() - 1);
    }

    class iterator {
    private:
        vector<T> items;
        int index;
    public:

        iterator(vector<T> _items, int _index) : items(_items), index(_index) {
        }

        iterator operator++(int) {
            index++;
            return *this;
        }

        T operator*() {
            return getValue();
        }

        T getValue() {
            if ((unsigned) index < (unsigned) items.size()) {
                return items.at(index);
            }
            return 0;
        }

        int getIndex() {
            return index;
        }

        bool operator ==(iterator other) {
            return getValue() == other.getValue();
        }

        bool operator !=(iterator other) {
            return (unsigned) getIndex() < (unsigned) items.size();
        }
    };

    void fillVector(vector<T> *xv) {
        if (this->uzel) {
            if (leftTree != 0) {
                leftTree->fillVector(xv);
            }
            if (rightTree != 0) {
                rightTree->fillVector(xv);
            }

        } else {
            if (this->pocetvlozeni > 0) {
                xv->push_back(this->hodnota);
            }
        }
    }

    /** Override operators **/

    friend std::ostream & operator <<(std::ostream &os, BSTSET<T> & set) {
        set.tisk();
        return os;
    }

    int operator()(T a) {
        return dejPocetVlozeni(a);
    }

    void operator >>(T a) {
        smaz(a);
    }

    int operator[](T a) {
        return dejVnoreni(a);
    }

    void operator<<(T a) {
        vloz(a);
    }
};

#endif /* BSTSET_H_ */
