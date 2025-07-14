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
    HELL6_99MO myfile ("configs/strconfig.config");
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
    // std::cout <<myfile.get("database.port").type<<"\n";
    // std::cout <<myfile.get("root_scope.flag").type<<"\n";
    // std::cout <<myfile.get("user.fruits").type<<"\n";
    // std::cout <<myfile.get("user.fruits").array_value[0]<<"\n";
    // std::cout <<myfile.get("user.fruits").array_value[1]<<"\n";
    // std::cout <<myfile.get("user.fruits").array_value[2]<<"\n";

    // std::cout <<myfile.get("user.str").type<<"\n";
    // std::cout <<myfile.get("user.str").array_value[0]<<"\n";
    // std::cout <<myfile.get("user.str").array_value[1]<<"\n";
    // std::cout <<myfile.get("user.str").array_value[2]<<"\n";

    // std::cout <<myfile.get("system.logging.enabled").bool_value<<"\n";
    // std::cout <<myfile.get("config.libinfo.author").type<<"\n";
    // std::cout <<myfile.get("config.append").type<<"\n";

    // myfile.write("stdl.jh699");


    // HELL6_99MO new_config ("NewConfig");
    // new_config.new_key("user.name", "string");
    // new_config.new_key("user.age", "number");
    // new_config.new_key("user.boolean", "bool");
    // new_config.new_key("user.array", "array");
    // new_config.new_key("user.unidef", "unidef");

    // new_config.set("user.name", "Andrew");
    // new_config.set("user.age", "10");
    // new_config.set("user.boolean", "true");
    // new_config.set_array("user.array", std::vector <std::string> ({"Apple", "Mango", "Banana"}));

    // new_config.write("new_config.cfg");

    for (unsigned long long x = 0;x < myfile.scopes.size();x++){
        std::cout << myfile.scopes[x]<<" "<<myfile.scopes[x].length()<<"\n";
    }

    // std::cout <<myfile.get("config.UNIDEF").type<<"\n";

} 