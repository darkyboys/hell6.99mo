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

class HELL6_99MO_TYPE {
    public:
        HELL6_99MO_TYPE (std::string VALUE, std::string TYPE){
            if (TYPE == "string" or TYPE == "number" or TYPE == "bool" or TYPE == "array"){
                type = TYPE;
            }
            else {
                std::cerr << "HELL6.99MO Error -> HELL6_99MO_TYPE was unknown TYPE `"<<TYPE<<"` Can't make a valid type.";
            }
        }
        std::vector <std::string> array_value;
        std::string value = "";
        std::string type = "string";
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

            std::vector <std::vector<std::string>> elements = {};
            std::vector <unsigned int> scopes_spacings = {};
            
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
                if (fixed_content[i] == '"' or fixed_content[i] == '`'){
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
                        if (uncommented_data[x] == '\n' and not is_string_open){
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

        void Parse (){
            std::ifstream ifile (file_name);
            if (!ifile.is_open()){
                std::cerr << "HELL6.99MO Error -> Can't open the given file `" << file_name << "` Please be sure that it can be opened.";
            }

            std::string temp, content;
            while (std::getline(ifile, temp))
                content += temp + '\n';

            std::vector <std::vector<std::string>> tokens = Lexer(content);
            for (unsigned long long i = 0;i < tokens.size();i++){
                // std::cout << tokens [i][0] <<", "; // for debugging
                // std::cout << tokens [i][1] <<'\n'; // for debugging
                bool is_line_started = false;
                for (unsigned long long x = 0;x < tokens[i][1].length();x++){
                    if (tokens[i][1][x] != ' ' and not is_line_started)
                        is_line_started = true;
                    if (tokens[i][1][x] == '[' and is_line_started){
                        array_keys.push_back({tokens[i][0]});
                        bool is_array_string_open = false;
                        std::string array_string_data = "";

                        for (unsigned long long y = x;y < tokens[i][1].length()-x;y++){
                            if (tokens[i][1][y] == '"'){
                                if (is_array_string_open and tokens[i][1][y-1] == '\\')
                                    array_string_data = array_string_data.substr(0, array_string_data.length()-1),
                                    array_string_data += "\"";
                                else 
                                    is_array_string_open = not (is_array_string_open);
                                continue;
                            }

                            if (tokens[i][1][y] == ']'){
                                 array_keys[array_keys.size()-1].push_back(array_string_data);
                                 x = y;
                                 break;
                            }

                            if (tokens[i][1][y] == ','){
                                 array_keys[array_keys.size()-1].push_back(array_string_data);
                                 array_string_data.clear();
                                 continue;
                            }

                            if (is_array_string_open)
                                array_string_data += tokens[i][1][y];
                        }

                        // std::cout << "Key: "<<array_keys[0][0]<<"\n";
                        // for (unsigned long long z = 1;z < array_keys[0].size();z++){
                        //     std::cout << "Value: "<<array_keys[0][z]<<"\n";
                        // } // for debugginh only
                    }


                    else if (tokens[i][1][x] == '"' and is_line_started){
                        string_keys.push_back({tokens[i][0]});
                        bool is_string_string_open = true;
                        std::string string_string_data = "";
                        
                        for (unsigned long long y = x+1;y < tokens[i][1].length()-x;y++){
                            if (tokens[i][1][y] == '"'){
                                if (is_string_string_open and tokens[i][1][y-1] == '\\')
                                    string_string_data = string_string_data.substr(0, string_string_data.length()-1),
                                    string_string_data += "\"";
                                else 
                                    is_string_string_open = not (is_string_string_open);
                                continue;
                            }


                            if (is_string_string_open)
                                string_string_data += tokens[i][1][y];
                        }
                        string_keys[string_keys.size()-1].push_back(string_string_data);

                        // std::cout << "Key: "<<string_keys[0][0]<<"\n";
                        // for (unsigned long long z = 1;z < string_keys[0].size();z++){
                        //     std::cout << "Value: "<<string_keys[0][z]<<"\n";
                        // } // for debugginh only
                    }
                }
            }
        }
};