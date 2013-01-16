//
//  stack_array.h
//  SuperStack
//
//  Created by Pavel Strnad on 05.12.11.
//  Copyright (c) 2011 Czech Technical University in Prague. All rights reserved.
//

#ifndef SuperStack_stack_array_h
#define SuperStack_stack_array_h

#include <vector>
#include <iostream>
#include <iomanip>


using namespace std;

template <typename T, int size>
class StackArray {
    int velikost;
    T maxCislo;
    T* cisla;
    int pointer;
public:

    StackArray(T _maxValue) : velikost(size), maxCislo(_maxValue) {
        cisla = new T[velikost];
        pointer = -1;
    }

    void push(T cislo) {
        if (cislo <= maxCislo and pointer + 1 < velikost) {
            pointer++;
            cisla[pointer] = cislo;
        } else {
            cout << "Zasobnik je plny. Nemohu provest PUSH." << endl;
            //throw "Error v push";
        }
    }

    T pop() {
        pointer--;
        if (pointer + 1 < 0) {
            cout << "Zasobnik je prazdny. Nemohu provest POP." << endl;
            //throw "Error v pop";
        }
        return cisla[pointer + 1];
    }
};


#endif 
