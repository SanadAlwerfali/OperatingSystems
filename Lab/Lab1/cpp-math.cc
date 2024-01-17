#include <iostream>
#include "cpp-math.h"

// PART 1: Symbols and Polymorphism

// functions decelrations 
int add(int, int);
float add(float, float);

int add(int a, int b) {
    return a + b;
}

float add(float a, float b) {
    return a + b;
}

