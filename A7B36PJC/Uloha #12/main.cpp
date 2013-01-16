//
//  main.cpp
//  SuperStack
//
//  Created by Pavel Strnad on 05.12.11.
//  Copyright (c) 2011 Czech Technical University in Prague. All rights reserved.
//
/*
Cviceni 12
 
 Pokyny
 Implementujte tridy StackArray a SuperStack tak, aby nasledujici kod sel prelozit
 a pracoval spravne. Inspirujte se tridou StackVector. 

 */

#include <iostream>
#include "super_stack.h"
#include "stack_vector.h"
#include "stack_array.h"

int main(int argc, const char * argv[]) {

    SuperStack<int, StackArray<int, 2 >, 10 > s;
    s.push(4);
    s.push(3);
    s.push(1);
    cout << "Cislo: " << s.pop() << endl;
    cout << "Cislo: " << s.pop() << endl;

    SuperStack<double, StackVector<double, 10 >, 10 > sv;
    sv.push(5);
    //sv.push(15);
    sv.push(9);
    cout << "Cislo: " << sv.pop() << endl;
    cout << "Cislo: " << sv.pop() << endl;
    
    return 0;
}

