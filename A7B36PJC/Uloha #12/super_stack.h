//
//  super_stack.h
//  SuperStack
//
//  Created by Pavel Strnad on 05.12.11.
//  Copyright (c) 2011 Czech Technical University in Prague. All rights reserved.
//

#ifndef SuperStack_super_stack_h
#define SuperStack_super_stack_h

using namespace std;

template <typename TItem, typename TStack, int max_value>
class SuperStack {
    TStack *stack;

public:

    SuperStack() {
        stack = new TStack(max_value);
    }

    TItem pop() {
        return stack->pop();
    }

    void push(TItem item) {
        try {
            stack->push(item);
        } catch (string s) {
        };
    }

    ~SuperStack() {
        delete stack;
    }
};


#endif 
