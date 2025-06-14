/*
 * Copyright (c) ghgltggamer 2025
 * This is the official library for the HELL6.99MO format, Implemented using the C++ programming language and is only for the C++ programming language
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Checkout the README.md for more information
*/

// This is the test file for testing the official library for the HELL6.99MO
#include "../lib/cxx/Model0/ModelO-HELL6.99.hh"

int main (){
    HELL6_99MO myfile ("stresstest/level1.h669");
    myfile.Parse();
}