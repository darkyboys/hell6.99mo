/*
 * Copyright (c) ghgltggamer 2025
 * This is the official library for the HELL6.99MO format, Implemented using the C++ programming language and is only for the C++ programming language
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Checkout the README.md for more information
*/

// This is the test file for testing the official library for the HELL6.99MO
#include "../lib/cxx/Model0/ModelO-HELL6.99.hh"
// #include <cstddef>

int main (){
    HELL6_99MO myfile ("stresstest/level3.h699");
    myfile.Parse();

    // for (size_t i = 0;i < myfile.string_keys.size();i++){
    //     std::cout << "Key: "<<myfile.string_keys[i][0]<<", ";
    //     std::cout << "Value: "<<myfile.string_keys[i][1]<<"\n";
    //     std::cout << "Key(raw): [" << myfile.string_keys[i][0] << "] len=" << myfile.string_keys[i][0].length() << "\n";
    //     std::cout << "Ref(raw): [" << "system.logging.level" << "] len=" << std::string("system.logging.level").length() << "\n";

    //     if (myfile.string_keys[i][0] == "system.logging.level"){
    //         std::cout << myfile.string_keys[i][1]<<"\n";
    //     }
    // }
    // std::cout << myfile.get("system.logging.level").string_value<<"\n\n";
    // myfile.set("system.logging.level", "Hello world 2024");
    // std::cout << myfile.get("system.logging.level").string_value<<"\n\n";
    // std::cout << myfile.get("database.port").number_value<<"\n\n";
    // myfile.set("database.port", "Hello world 2024");
    // std::cout << myfile.get("database.port").number_value<<"\n\n";
    // std::cout << myfile.get("system.logging.enabled").bool_value<<"\n\n";
    // myfile.set("system.logging.enabled", "false");
    // std::cout << myfile.get("system.logging.enabled").bool_value<<"\n\n";
    // std::cout << myfile.get("def.UNIDEF").unidef_value<<"\n\n";
    // myfile.set("def.UNIDEF", "Hello world 2024");
    // std::cout << myfile.get("def.UNIDEF").unidef_value<<"\n\n";
    std::cout <<myfile.get("database.port").type<<"\n";
}