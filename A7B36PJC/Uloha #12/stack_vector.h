//
//  stack_vector.h
//  SuperStack
//
//  Created by Pavel Strnad on 05.12.11.
//  Copyright (c) 2011 Czech Technical University in Prague. All rights reserved.
//

#ifndef SuperStack_stack_vector_h
#define SuperStack_stack_vector_h

#include <vector>
#include <iostream>
#include <iomanip>


using namespace std;

template <typename T, int size>
class StackVector {
    int velikost;
    T maxCislo;
    vector<T> cisla;
    int top;
public:

    StackVector(T _maxValue) : velikost(size), maxCislo(_maxValue) {
        cisla.resize(velikost);
        top = -1;
    }

    void push(T cislo) {
        if (cislo <= maxCislo and top + 1 < velikost) {
            top++;
            cisla[top] = cislo;
        } else {
            cout << "Zasobnik je plny. Nemohu provest PUSH." << endl;
            //throw "Error v push";
        }
    }

    T pop() {
        top--;
        if (top + 1 < 0) {
            cout << "Zasobnik je prazdny. Nemohu provest POP." << endl;
            //throw "Error v pop";
        }
        return cisla[top + 1];
    }

};


#endif 
