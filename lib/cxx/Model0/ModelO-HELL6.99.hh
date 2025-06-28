/*
 * Copyright (c) ghgltggamer 2025
 * This is the official library for the HELL6.99MO format, Implemented using the C++ programming language and is only for the C++ programming language
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Checkout the README.md for more information
*/

// headers
// Std Cxx 17 STL
#include <iostream>
#include  <fstream>
#include   <string>
#include   <vector>

const unsigned long long H699_UNIDEFULL = -1;
const std::string H699_UNIDEF = "unidefx" + std::to_string(H699_UNIDEFULL);

class HELL6_99MO_TYPE {
    public:
        // HELL6_99MO_TYPE (std::string VALUE, std::string TYPE){
        //     if (TYPE == "string" or TYPE == "number" or TYPE == "bool" or TYPE == "array"){
        //         type = TYPE;
        //     }
        //     else {
        //         std::cerr << "HELL6.99MO Error -> HELL6_99MO_TYPE was unknown TYPE `"<<TYPE<<"` Can't make a valid type.";
        //     }
        // }
        std::vector <std::string> array_value;
        std::string string_value = "";
        std::string string_key = "";
        std::string unidef_key = "";
        std::string unidef_value = "";
        std::string number_key = "";
        unsigned long long number_value = 0;
        std::string bool_key = "";
        bool bool_value;
        std::string array_key;
        std::string type = H699_UNIDEF;
};

class HELL6_99MO{
    private:
        std::string file_name;
    public:
        std::vector <std::vector <std::string>> string_keys = {};
        std::vector <std::vector <std::string>> array_keys = {};
        std::vector <std::vector <std::string>> number_keys = {};
        std::vector <std::vector <std::string>> unidef_keys = {};
        std::vector <std::vector <std::string>> bool_keys = {};

        HELL6_99MO (std::string file) : file_name(file) {}

        std::vector <std::vector <std::string>> Lexer (std::string file_content){
            std::vector <std::vector <std::string>> tokens = {};
            // flags
            // Comment
            bool comment_is_string_open = false,
                 comment_is_comment_open = false;

            // Syntax
            bool syntax_is_string_open = false,
                 syntax_is_comment_open = false,
                 syntax_is_line_just_started = false;

            bool attribute_is_string_open = false,
                 attribute_is_value_open = false,
                 attribute_is_data_writable = true,
                 attribute_is_attribute_open = false;

            std::vector <std::vector<std::string>> elements = {};
            std::vector <unsigned int> scopes_spacings = {};
            std::vector <std::string> attribute_import_imported_files = {};

            std::string uncommented_data;
            std::string opened_scope = "";
            // syntax annalysis
            // Before processing, inject a space after every \n
            file_content = " " + file_content;
            bool is_fixed_content_string_open = false;
            std::string fixed_content;
            bool is_string_open = false;
            char string_delim = '\0'; // Can be either `"` or '`'

            for (size_t i = 0; i < file_content.length(); ++i) {
                char ch = file_content[i];
                fixed_content += ch;
            
                if ((ch == '"') and (i == 0 or file_content[i - 1] != '\\')) {
                    if (!is_string_open) {
                        is_string_open = true;
                        string_delim = ch;
                    } else if (string_delim == ch) {
                        is_string_open = false;
                    }
                }
            
                if (ch == '\n' and !is_string_open) {
                    fixed_content += ' ';
                }
            }


            // Comment remover
            for (unsigned long long i = 0;i < fixed_content.length();i++){
                // std::cout << file_content[i] << "\n"; // for debugging only 
                if (fixed_content[i] == '"'){
                    if (comment_is_string_open and fixed_content[i-1] == '\\'){
                        uncommented_data += "\"";
                        continue;
                    }
                    comment_is_string_open = not (comment_is_string_open);
                }

                if (fixed_content[i] == '#' and not comment_is_string_open and not comment_is_comment_open)
                    comment_is_comment_open = true;

                if (fixed_content[i] == '\n' and not comment_is_string_open)
                    comment_is_comment_open = false;

                if (not comment_is_comment_open)
                    uncommented_data += fixed_content[i];
            }


            // Attribute Manager
            unsigned int total_runs = 1;
            while (total_runs != 0){
                std::string attributed_data = "";
                std::string attribute_name = "",
                            attribute_value = "";
                for (unsigned long long i = 0;i < uncommented_data.length();i++){
                    if (uncommented_data[i] == '"'){
                        if (attribute_is_string_open and uncommented_data[i-1] == '\\'){
                            attributed_data += "\"";
                            continue;
                        }
                        attribute_is_string_open = not (attribute_is_string_open);
                    }
                    if (uncommented_data[i] == '@' and not attribute_is_string_open and not attribute_is_attribute_open){
                        // std::cout << "Attribute started at : "<<i<<", Character: "<<uncommented_data[i]<<"\n\n"; // for debugging
                        attribute_is_attribute_open = true;
                        attribute_is_data_writable = false;
                        continue;
                    }
                    if (uncommented_data[i] == ' ' and not attribute_is_string_open and attribute_is_attribute_open){
                        attribute_is_value_open = true;
                        attribute_is_attribute_open = false;
                        continue;
                    }
                    if (uncommented_data[i] == '\n' and attribute_is_attribute_open){ // This meeans that attribute wasn't valued so gracefully ignore it and reset everything
                        attribute_name.clear();
                        attribute_value.clear();
                        attribute_is_data_writable = true;
                        attribute_is_value_open = false;
                        attribute_is_attribute_open = false;
                    }
                    if (uncommented_data[i] == '\n' and attribute_is_value_open){
                        // std::cout << "Attribute Name: "<<attribute_name<<"\nAttribute valyue: "<<attribute_value<<"\n\n"; // for debugging

                        // All the attributes defination will go inside this scope / if block
                        // Import! - For importing files
                        if (attribute_name == "import"){
                            // std::cout << "Importing `"<<attribute_value<<"`\n"; // for debugging
                            bool is_file_already_imported = false;
                            for (unsigned long long file_index = 0;file_index < attribute_import_imported_files.size();file_index++){
                                if (attribute_value == attribute_import_imported_files[file_index]){
                                    is_file_already_imported = true;
                                    break;
                                }
                            } // done the scanning

                            if (is_file_already_imported){
                                // Do nothing if file is already imported
                                continue;
                            }

                            else {
                                // Import the file
                                std::ifstream ifile (attribute_value);
                                if (!ifile.is_open()){
                                    std::cerr << "HELL6.99MO ERROR _> import attribute needs a valid file path to import a file,\n The file `"<<attribute_value<<"` couldn't be opened, Please make sure that the file is accessible.\n";
                                    std::exit ( 3 );
                                }

                                // Read the file
                                std::string temp, content;
                                while (std::getline(ifile, temp))
                                    content += " " + temp + "\n"; // Please do not break the format by removing the first space.

                                attributed_data += content; // finally write back to the attribute data
                                attribute_import_imported_files.push_back(attribute_value);
                            }
                            total_runs += 1;
                        }
                        // Ignore all the unknown attributes gently

                        // Just reset everything
                        attribute_name.clear();
                        attribute_value.clear();
                        attribute_is_data_writable = true;
                        attribute_is_value_open = false;
                        attribute_is_attribute_open = false;
                    }

                    if (attribute_is_attribute_open)
                        attribute_name += uncommented_data[i];
                    else if (attribute_is_value_open){
                        attribute_value += uncommented_data[i];
                    }

                    if (attribute_is_data_writable){
                        attributed_data += uncommented_data[i];
                    }
                }
                // std::cout << "After Attribution: \n" << attributed_data << "\n"; // for debugging


                // Final Comment Remover
                // Comment remover
                uncommented_data.clear();
                for (unsigned long long i = 0;i < attributed_data.length();i++){
                    // std::cout << file_content[i] << "\n"; // for debugging only 
                    if (attributed_data[i] == '"'){
                        if (comment_is_string_open and attributed_data[i-1] == '\\'){
                            uncommented_data += "\"";
                            continue;
                        }
                        comment_is_string_open = not (comment_is_string_open);
                    }

                    if (attributed_data[i] == '#' and not comment_is_string_open and not comment_is_comment_open)
                        comment_is_comment_open = true;

                    if (attributed_data[i] == '\n' and not comment_is_string_open)
                        comment_is_comment_open = false;

                    if (not comment_is_comment_open)
                        uncommented_data += attributed_data[i];
                }

                total_runs -= 1;
            }
            // std::cout << "All the comments has been removed : " << uncommented_data << "\n"; // for debugging only
            
            // Syntax Annalyser
            for (unsigned long long i = 0;i < uncommented_data.length();i++){
                if (uncommented_data[i] == '"' or uncommented_data[i] == '`')
                    syntax_is_string_open = not (syntax_is_string_open);
                
                if (uncommented_data[i] == '\n' and not syntax_is_string_open)
                    syntax_is_line_just_started = true;

                if (uncommented_data[i] == ':' and not syntax_is_string_open){
                    // std::cout << "Collision found at : "<<i<<", character: "<<uncommented_data[i]<<", prev character: "<<uncommented_data[i-1]<<"\n"; // for debugging only
                    std::string current_scope_name = "",
                                current_scope_name_correct = "",
                                current_scope_name_correctly_formatted = "";
                    bool can_count_spaces = false;
                    unsigned int current_scope_spaces_count = 0;
                    for (unsigned long long x = i;x > 0 and uncommented_data[x] != '\n';x--){
                        if (uncommented_data[x-1] != ' ' and not can_count_spaces){
                            can_count_spaces = true;
                            continue;
                        }
                        else if (uncommented_data[x] == ' ' and can_count_spaces){
                            current_scope_spaces_count += 1;
                            continue;
                        }

                        current_scope_name += uncommented_data[x];

                        if (x == 1){
                            if (uncommented_data[x-1] == ' ' and can_count_spaces)
                                current_scope_spaces_count += 1;
                            else 
                                current_scope_name += uncommented_data[x-1];
                        }
                    }

                    for (unsigned long long y = current_scope_name.length();y > 0;y--){
                        current_scope_name_correct += current_scope_name[y];
                        if (y == 1 and current_scope_name[y-1] != '=' and current_scope_name[y-1] != ' ')
                            current_scope_name_correct += current_scope_name[y-1];
                    }

                    for (unsigned long long z = 0;z < current_scope_name_correct.length();z++){
                        if (current_scope_name_correct[z] == ' ' or current_scope_name_correct[z] == ':') continue;
                        current_scope_name_correctly_formatted += current_scope_name_correct[z];
                    }

                    
                    while (1){
                        if (scopes_spacings.size() == 0){
                            opened_scope = current_scope_name_correctly_formatted;
                            scopes_spacings.push_back(current_scope_spaces_count);
                            // std::cout << "Pushed the scope spacing is : " << current_scope_spaces_count <<"\n";// for debugging
                            break;
                        }
                        else if (current_scope_spaces_count <= scopes_spacings.back()){
                            opened_scope = opened_scope.substr(0, opened_scope.rfind("."));
                            scopes_spacings.pop_back();
                            continue;
                        }
                        else if (current_scope_spaces_count > scopes_spacings.back()){
                            opened_scope += "." + current_scope_name_correctly_formatted;
                            scopes_spacings.push_back(current_scope_spaces_count);
                            // std::cout << "Pushed the scope spacing is : " << current_scope_spaces_count <<"\n"; // for debugging
                            break;
                        }
                    }

                    std::string make_spaces_correctly = "";
                    for (unsigned long long s = 0;s <= current_scope_spaces_count;s++)
                        make_spaces_correctly += " ";
                    make_spaces_correctly += " ";
                    uncommented_data = uncommented_data.insert(i+1, "\n" + make_spaces_correctly);

                    // std::cout << "A Scope name was found: "<<current_scope_name_correctly_formatted << " Space counts were: "<<current_scope_spaces_count <<"\n"; // for debugging
                    // std::cout << "The Open Scope name was found: "<<opened_scope << " Space counts were: "<<current_scope_spaces_count <<"\n"; // for debugging
                    // scopes.push_back(current_scope_name_correctly_formatted);
                    continue;
                }


                else if (uncommented_data[i] == '=' and not syntax_is_string_open) {
                    std::string current_element_name = "",
                                current_element_name_correct = "",
                                current_element_name_correctly_formatted = "";
                    std::string current_element_value = "";
                    unsigned int current_element_spaces_count = 0;
                    bool can_count_spaces = false,
                         can_break_tokens = false;
                    for (unsigned long long x = i;x > 0 and uncommented_data[x] != '\n';x--){
                        if (uncommented_data[x-1] != ' ' and not can_count_spaces){
                            can_count_spaces = true;
                            continue;
                        }
                        else if (uncommented_data[x] == ' ' and can_count_spaces){
                            current_element_spaces_count += 1;
                            continue;
                        }

                        current_element_name += uncommented_data[x];

                        if (x == 1){
                            if (uncommented_data[x-1] == ' ' and can_count_spaces)
                                current_element_spaces_count += 1;
                            else 
                                current_element_name += uncommented_data[x-1];
                        }
                    }

                    for (unsigned long long y = current_element_name.length()-1;y > 0;y--){
                        current_element_name_correct += current_element_name[y];
                        if (y == 1 and current_element_name[y-1] != '=' and current_element_name[y-1] != ' ')
                            current_element_name_correct += current_element_name[y-1];
                    }

                    for (unsigned long long z = 0;z < current_element_name_correct.length();z++){
                        if (current_element_name_correct[z] == ' ') continue;
                        current_element_name_correctly_formatted += current_element_name_correct[z];
                    }

                    while (1){
                        if (scopes_spacings.size() == 0){
                            current_element_name_correctly_formatted = current_element_name_correctly_formatted;
                            break;
                        }
                        else if (current_element_spaces_count <= scopes_spacings.back()){
                            opened_scope = opened_scope.substr(0, opened_scope.rfind("."));
                            scopes_spacings.pop_back();
                            continue;
                        }
                        else if (current_element_spaces_count > scopes_spacings.back()){
                            current_element_name_correctly_formatted = opened_scope + "." + current_element_name_correctly_formatted;
                            break;
                        }
                    }

                    // std::cout << "An Element name was found: "<<current_element_name_correctly_formatted << " Space counts were: "<<current_element_spaces_count <<"\n"; // for debugging
                    std::string value;
                    bool is_string_open = false;
                    bool is_array_open = false;
                    for (unsigned long long x = i+1;1;x++){
                        if (uncommented_data[x] != ' ' and not can_break_tokens)
                            can_break_tokens = true;
                        if (uncommented_data[x] == '"'){
                            if (is_string_open and uncommented_data[x-1] == '\\'){
                                value = value.substr(0, value.length()-1) + "\\\"";
                                continue;
                            }
                            is_string_open = not (is_string_open);
                        }
                        if (uncommented_data[x] == ']' and not is_string_open and is_array_open){
                            is_array_open = false;
                        }
                        else if (uncommented_data[x] == '[' and not is_string_open and not is_array_open){
                            is_array_open = true;
                        }
                        if (uncommented_data[x] == '\n' and not is_string_open and not is_array_open){
                            i = x;
                            break;
                        }
                        if (can_break_tokens)
                            value += uncommented_data[x];
                    }
                    // std::cout << "The Element value is :"<<value<<"\n"; // for debugging
                    elements.push_back(std::vector <std::string>{current_element_name_correctly_formatted, value});
                }
            }
            tokens = elements;
            return tokens;
        }

        void Parse (bool tracking = true){
            std::ifstream ifile (file_name);
            if (!ifile.is_open()){
                std::cerr << "HELL6.99MO Error -> Can't open the given file `" << file_name << "` Please be sure that it can be opened.";
            }

            std::string temp, content;
            while (std::getline(ifile, temp))
                content += temp + '\n';

            std::vector <std::vector<std::string>> tokens = Lexer(content);
            std::vector <std::string> keys_tracked = {};
            for (unsigned long long i = 0;i < tokens.size();i++){
                // std::cout << tokens [i][1] <<'\n'; // for debugging
                // std::cout << tokens [i][0] <<", "; // for debugging
                std::string key = "";
                for (unsigned long long z = 0;z < tokens[i][0].length();z++){
                    if (tokens[i][0][z] == '\n' or tokens[i][0][z] == '\0' or tokens[i][0][z] == '\r'){
                        continue;
                    }
                    else {
                        key += tokens[i][0][z];
                    }
                }

                if (tracking){
                    bool is_key_already_present = false;
                    for (unsigned long long trace = 0;trace < keys_tracked.size();trace++){
                        // std::cout << "Checking keys "<<key<<" with "<<keys_tracked[trace]<<"\n\n"; // for debugging
                        if (keys_tracked[trace] == key){
                            // std::cout << "Keys Collided!\n"; // for debugging
                            is_key_already_present = true;
                            break;
                        }
                    }

                    if (is_key_already_present){
                        continue;
                    }
                    else {
                        keys_tracked.push_back(key);
                    }
                }

                if (tokens[i][1] == "UNIDEF"){
                    unidef_keys.push_back({key, "UNIDEF"});
                }
                else if (tokens[i][1] == "true"){
                    bool_keys.push_back({key, "true"});
                }
                else if (tokens[i][1] == "false"){
                    bool_keys.push_back({key, "false"});
                }
                else if (tokens[i][1][0] == '\"'){
                    std::string content = tokens[i][1].substr(tokens[i][1].find("\"")+1, tokens[i][1].rfind("\"")-1);
                    std::string content_fixed = "";
                    for (unsigned long long x = 0;x < content.length();x++){
                        if (content[x] == '\\' and content[x+1] == '\"'){
                            content_fixed += "\"";
                            x+=1;
                            continue;
                        }
                        else{
                            content_fixed += content[x];
                        }
                    }
                    string_keys.push_back({key, content_fixed});
                    // std::cout << "Str Content: "<<content_fixed<<"\n\n"; // for debugging
                }
                else if (tokens[i][1][0] == '['){
                    std::vector <std::string> array = {key};
                    std::string str_current_token = "";
                    bool str_array_is_string_open = false;
                    for (unsigned long long x = 1;x < tokens[i][1].length();x++){
                        if (tokens[i][1][x] == ']' and not str_array_is_string_open){
                            array.push_back(str_current_token);
                            array_keys.push_back(array);
                            // std::cout << "New Array Value: "<<str_current_token<<", Len: "<<array.size()<<"\n\n"; // for debugging
                            str_current_token.clear();
                            break;
                        }
                        if (tokens[i][1][x] == ',' and not str_array_is_string_open){
                            array.push_back(str_current_token);
                            // std::cout << "New Array Value: "<<str_current_token<<"\n\n"; // for debugging
                            str_current_token.clear();
                            continue;
                        }
                        if (tokens[i][1][x] == '\"'){
                            if (tokens[i][1][x-1] == '\\' and str_array_is_string_open){
                                str_current_token = str_current_token.substr(0, str_current_token.length()-1) + "\"";
                                // str_current_token += "\"";
                            }
                            else {
                                str_array_is_string_open = not (str_array_is_string_open);
                            }
                            continue;
                        }
                        if (str_array_is_string_open) {
                            str_current_token += tokens[i][1][x];
                        }
                    }
                }
                else {
                    bool is_num = true;
                    for (unsigned long long x = 0;x < tokens[i][1].length();x++){
                        if (tokens[i][1][x] < '0' or tokens[i][1][x] > '9'){
                            is_num = false;
                            break;
                        }
                    }
                    if (is_num){
                        number_keys.push_back({key, tokens[i][1]});
                        // std::cout << "Current Number: "<<tokens[i][1]<<"\n\n"; // for debugging
                    }
                    else {
                        unsigned long long ascii_number_system = 0;
                        for (unsigned long long x = 0;x < tokens[i][1].length();x++){
                            ascii_number_system += int(tokens[i][1][x]);
                            continue;
                        }
                        number_keys.push_back({key, std::to_string(ascii_number_system)});
                        // std::cout << "Current Ascii Number: "<<ascii_number_system<<"\n\n"; // for debugging
                    }
                }
            }
        }


        HELL6_99MO_TYPE get (std::string key) {
            HELL6_99MO_TYPE return_value;
            bool is_assigned = false;

            for (unsigned long long i = 0; i < string_keys.size(); i++) {
                if (string_keys[i][0] == key) {
                    return_value.string_value = string_keys[i][1];
                    return_value.string_key = string_keys[i][0];
                    return_value.type = "string";
                    is_assigned = true;
                    break;
                }
            }
        
            for (unsigned long long i = 0; i < number_keys.size(); i++) {
                if (is_assigned)
                    break;
                if (number_keys[i][0] == key) {
                    return_value.number_value = std::stoull(number_keys[i][1]);
                    return_value.number_key = number_keys[i][0];
                    return_value.type = "number";
                    is_assigned = true;
                    break;
                }
            }
        
            for (unsigned long long i = 0; i < bool_keys.size(); i++) {
                if (is_assigned)
                    break;
                if (bool_keys[i][0] == key) {
                    return_value.bool_value = (bool_keys[i][1] == "true");
                    return_value.bool_key = bool_keys[i][0];
                    return_value.type = "bool";
                    is_assigned = true;
                    break;
                }
            }
        
            for (unsigned long long i = 0; i < unidef_keys.size(); i++) {
                if (is_assigned)
                    break;
                if (unidef_keys[i][0] == key) {
                    return_value.unidef_value = "unidef";
                    return_value.unidef_key = unidef_keys[i][0];
                    return_value.type = "unidef";
                    is_assigned = true;
                    break;
                }
            }
        
            for (unsigned long long i = 0; i < array_keys.size(); i++) {
                if (is_assigned)
                    break;
                if (array_keys[i][0] == key) {
                    for (unsigned long long x = 1; x < array_keys[i].size(); x++) {
                        return_value.array_value.push_back(array_keys[i][x]);
                    }
                    return_value.array_key = array_keys[i][0];
                    return_value.type = "array";
                    is_assigned = true;
                    break;
                }
            }
        
            return return_value;
        }



        void set (std::string key, std::string value) {
            bool is_assigned = false;

            for (unsigned long long i = 0; i < string_keys.size(); i++) {
                if (string_keys[i][0] == key) {
                    string_keys[i][1] = value;
                    is_assigned = true;
                    break;
                }
            }
        
            for (unsigned long long i = 0; i < number_keys.size(); i++) {
                if (is_assigned)
                    break;
                if (number_keys[i][0] == key) {
                    bool is_num = true;
                    for (unsigned long long y = 0;y < value.length();y++){
                        if (value[y] < '0' or value[y] > '9'){
                            is_num = false;
                            break;
                        }
                    }

                    if (is_num){
                        number_keys[i][1] = value;
                    }

                    else {
                        int ascii_number_system = 0;
                        for (unsigned long long z = 0;z < value.length();z++){
                            ascii_number_system += int (value[z]);
                        }
                        number_keys[i][1] = std::to_string(ascii_number_system);
                    }
                    is_assigned = true;
                    break;
                }
            }
        
            for (unsigned long long i = 0; i < bool_keys.size(); i++) {
                if (is_assigned)
                    break;
                if (bool_keys[i][0] == key) {
                    if (value == "true" or value == "false"){
                        bool_keys[i][1] = value;
                        is_assigned = true;
                        break;
                    }
                    else {
                        std::cerr << "HELL6.99MO Error _> set() can't set a boolean value to anything except for true or false.\n";
                        std::exit ( 3 );
                    }
                }
            }
        
            for (unsigned long long i = 0; i < unidef_keys.size(); i++) {
                if (is_assigned)
                    break;
                if (unidef_keys[i][0] == key) {
                    unidef_keys[i][1] = "unidef";
                    is_assigned = true;
                    break;
                }
            }
        }


        // set_array , write and write_back are going to be implemented in future

};