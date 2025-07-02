# HELL6.99MO - High Emmision Lite Level 6.99% Model O
`HELL6.99MO` is a modern data storing format made to allow storage of complex data with a robust and easy to understand , write and flexible syntax. `HELL6.99MO` was orignally based on the **ghgltggamer's Model O** Syntax which allows you use any amount of indentation unless the indentation level matches the level of the opened scope.

## Let's understand the GTG's MODEL O in depth
**Model O** is a syntax/rule which allows you to write a text in different - different indentation levels unless they match there current scope.

**Scope** is nothing but the identifier of the currently opened scope and is the address of the childern of the scope.

**Children** are the elements which are inside any scope , Even a scope can become the parent of other children and children of it's parent scope.

For Example:
```ascii
SCOPE1
 - SCOPE2
 - - SCOPE3
 - - - Children of scope 3
 - - Children of the scope 2
 - Children of the scope 1
Outside of the SCOPE1
```

*Here the Model O says that the children can only be formed when the indentation level of an element is greater than the indentation level of current scope, And how many level up don't matters.*

For Example:
```ascii
scope
    a
    b
   c
  d
 e
f
```

*Here, According to the GTG's Model O, all the a to e are the children of the scope because they have higher indentation level than what of scope, but f is having same indentation level and even if less , f won't be a part of scope as f it self is a parent different from scope.*


## HELL6.99MO's Config format
`HELL6.99MO` has different specs , This covers the very first specs of the format.

### Basics of HELL6.99MO
The most basic thing in `HELL6.99MO` we can learn is that it's just a Model O based Key = Value pair collection. Means we will always be defining a key with a value like `<key> symbol <value>`. `HELL6.99MO` as a Model O based format supports the Comments , Comments are completely ignored by the `HELL6.99MO` Parsers / Lexers because comments are written to notify something to us humans but not to the computers, and anything starting with a `#` becomes a comment.

### How to define a scope
In `HELL6.99MO` any key with `:` becomes a scope for example.
```hell6.99mo
scope1:
    # This comment is even inside the scope1 but will be ignored
```

*Note: Anything inside a scope becomes it's children.*

### How to make key/value pairs
In `HELL6.99MO` you can define a key/value pair by defining a key with `=` symbol and it's value right next to it. 

For example:
```hell6.99mo
key = "value"
```

### Attributes in HELL6.99MO
`HELL6.99MO` gives you attributes to do some specific programmable task like importing another HELL6.99MO Config file , Etc. Please note that different parsers may provide different attributes. We will be using the official specs of the format by GTG.

**Defining The Attributes**: Anything starts with the `@` symbol is an attribute and the attribute names are seperated by the a ` ` character and right side of the ` ` character is the value of the attribute , (e.g. `@import myfile.h699`)

**Known Attributes**: These attributes are defined in the specification.
 - - import : Imports another h699 config file and prevent duplications. (File name is given as the attribute value).

*Note you don't need to use ',' like symbols to end the line , HELL6.99MO uses \n for line termination automatically.*

### Datatypes in HELL6.99MO
Datatypes are the structure and a way to define different - different values to any key.
Similar to other languages the `HELL6.99MO` has several datatypes:-

 - Keys : These are standard datatypes to define values
 - Values : These are the dynamic datatype who changes itself based on the data.

*Value Datatype*
Value datatype are the types which changes the type of value and makes it globally accessible. 
These includes :-

 - Number : These are the most complex datatype of the HELL6.99MO as they are not the direct integers of any of the programming language, Instead they are 2 differnet things. 
 - - Ranged Numbers : These are the commonly accessible numbers ranging from 0 to 9, and can be a collection for example `5` is a normal number as it's a single character in between the range of 0 to 9, and `56` is also a number because when we break that into characters then we have `5` and `6` and both are in range of 0 to 9.
 - - Encoded Numbers : These are the addition of the encoding values specific to the characters. For example `AB` in `HELL6.99MO` is also a number because now it's an Encoded Number wher each character will be turned into the encoded code of your encoding and then be added to form a normal numbers , If we look them from ASCII then we get `A` = `65` and `B` = `66` and adding both gives `131` means it will become `131` in `HELL6.99MO` if your encoding is ASCII, As it varies on encoding to encoding, Therefore for common use cases, Normal integers are often recommended. (Also note that 0x1 like digits in `HELL6.99MO` will be taken as Ecoded number not as hex digits)

 - Strings : These are just characters nothing else , Which are stored inside 2 double-quotes. (e.g. "Hello world 2025")
 - Boolean : These just returns true or false and are written in same way (e.g. true).
 - UNIDEF  : This datatype is often compared to NULL but it is not NULL or undefined , It stands for `Universal Defination` which will work everywhere , With any language and is not null or undefined , But when you have no value to define to a key and you just want the key to be created but later shouldn't be changed then you can assign `UNIDEF` but remember later you can't set it to any other value except for unidef , even if you try your parser will likely turn it into `UNIDEF` automatically as trying to change `UNIDEF` may have fatal consequences. Because `UNIDEF` is meant to tell you that "Hey this is the universal defination with no such datatype and this shouldnot be changed later".
 - Array : Array are just collection of the semi string datatypes. Means you can only store strings only , and you can just store strings but very minimal strings not fully loaded string types. Usually array starts with `[` and ends with `]` and after each string a `,` is placed to seperate them , And if your array is multi-linear but have no multi-linear strings then it will be trimed to one line.

 For example :
 ```hell6.99mo
scope:
    array = ["Hello", "world, "2024"] # This is valid
    array2 = ["Hello
    world
    2024", "Hi"] # This is valid
    array3 = ["Hello world 2025",
              "hi there"] # This is also valid 
 ```

*Note: Strings with "" can be multiline with a new line but inside the string and \" can be used to inject additional " coat inside a string.*


---

### Reflector 
`HELL6.99MO` provides the reflectors which are used to instantly reflect an element / config scope in another scope for example.
```hell6.99mo
scope1:
    version = 1
    author = "You"

scope2 > scope1
scope2:
    license = "MIT License"
```
Here the `scope2` has `scope1` as child scope means `scope2.scope1.version` is completely valid, But in case if you provide wrong scope or it doesn't exist before the reflector then it will add `UNIDEF=UNIDEF` as the children. Also remember for creating the reflector we uses `scope name` and then `>` symbol and then the `existing scope name`. It means you want to point your scope to another scope and make the another scope easily accessible from the another scope.

Also remember! Variation matters, What do i mean from that is:
```hell6.99mo
scope1:
    version = 1
    author = "You"

scope2 > scope1
scope2:
    license = "MIT License" # fine scope 2 will have scope1

scope3 > scope4 # This is not invalid but wrong as scope4 is not processed when scope3 is in the entry , Leaving the lexer to instead return UNIDEF=UNIDEF

scope4:
    number = 9
```

*Note: if you @import any config before a reflector , It will process it But if you do it after a reflector , It will throw UNIDEF=UNIDEF instead*
---


## Implementation of HELL6.99MO
There is no fixed amount of implementation of the `HELL6.99MO` but the most mature implementation is the official implementation for the `C++` Programming Language , Defining all the format structure and required lexer / parsers. So here we will be learning the `HELL6.99MO` Official C++ Implementation as an Open Source MIT Licensed Library.

### Basics
Before you do anything , Please install the `HELL6.99MOCC` Library which is inside this repository inside directory `/lib/cxx/ModelO/` as the file named `ModelO-HELL6.99.hh`, Now this is a C++ only library which shouldn't be used with the C Programming Language, As the library itself uses the `C++ STL Headers` only which C's STDLIB don't supports.

### Structure
The `HELL6.99MOCC` Library is structured in 4 Areas.
 - HELL6_99MO_TYPE : This is the type which the library uses to store data in.
 - HELL6_99MO      : This is a class containing the lexer and parser and other utilities which we will be using later and this is also most important thing.
 - Lexer           : This is a full fledged unit the breaking down the complex `HELL6.99MO` input file into what we can understand as a human while programming (But this still gives the low level things like raw tokens with different unimplemented datatypes and right now there is no value type only 2 types , key and value but no other types and lexer implements these types, And these are implementes as a token and each token is differently structured so it becomes very hard as a human to work with this level of data but not impossible , yet risky).
 - Parser          : This is the unit which is important for us humans because it takes the tokens by the lexer and understands there structure and then implements the value types like , Number , String , Array etc. Without it we would have to work with the lexer raw tokens which is too hard and parser simplifies everything and we don't need anything else but still for more convenience we have out helper functions.
 - Helper functions : These are the highest level of abstractions on top of the lexer and parser as they allows you to tell what what you want and they will give you that exactly.

### API
The libaray has the human focused flexible and powerfull API which gives you:
`HELL6_99MO_TYPE` : This is just a datatype for C++ as a Class just defining the key values of different - differnet datatype and this is purely for the helper functions, As it looks like:
```cxx
class HELL6_99MO_TYPE{
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
    std::string type = "string";
}
```

Nothing else , Just holding variables for different datatypes.

---

`HELL6_99MO` : This class is most important class as it contains the lexer , parser and helperfunctions for everything you will need.

`HELL6_99MO::Lexer` : This is the lexer of the `HELL6.99MOCC` Library which takes the raw code and return the tokens in return , These tokens are `std::vector <std::vector <std::string>>` type.

`HELL6_99MO::Parse` : This function is exactly what we will call when ever we want to execute a `HELL6.99MO` File. This function just asks us the file name we want to execute and then automatically read it and call lexer to tokenise it and it also has a dedicated parser to then parse the lexer tokens into what we later can use , Now C++ is a statically typed language means we have to be in limits of the datatype defination so this function writes tokens into the `std::vector` Standard vector multidimmensional array where `{0={0="key", 1="value"}, 1={0="key", 1="value"}}` tokens are stored as first array and then children array holding the key/value pairs in std::string but in a specific type , For example `Parse` writes the different types in these different multidimmensional standard vectors:-

```cxx
std::vector <std::vector <std::string>> string_keys = {};
std::vector <std::vector <std::string>> array_keys = {};
std::vector <std::vector <std::string>> number_keys = {};
std::vector <std::vector <std::string>> unidef_keys = {};
std::vector <std::vector <std::string>> bool_keys = {};
```

You can access these as `HELL6_99MO::string_keys` etc.
Now Let suppose you want to check the first token's name and it's value and you know that it's a string you can just say `yourinit.string_keys[0][0]` here the first 0 tells the token number which in our case was `1` for `2` we use `1` because indexing starts from `0` and no matter the type the first index (0) of any token number will be always it's key and rest values , For most type the max size per token number of a Standard vector is 2 where 0 is the key and 1 is the value but for arrays first index (0) is still the key but the size can be anything depending on the array size of the config for example array of 5 tokens in config will result in 6 as the size of token because 0 is reserved for the key and rest are tokens means for accessing arrays we say `array = ["Apple", "Mango", "Banana"]` in the config and in programming we access it with `yourinit.array_value[0][1]` here the output will be `Apple` because `0` is for the key which is `array` and rest is for the indexing means `1` for Apple , `2` for mango and `3` for Banana. Hope that clarifies a lot.

---
(Helper Functions)

`HELL6_99MO::get` : This function just takes the key as `std::string` and then returns the `HELL6_99MO_TYPE` value with it's respective type and respective value according to the type , and if nothing found in any of the vector written by the parser then it will return `H699_UNIDEF` constant instead in the type which means no key was even found. 

`HELL6_99MO::set` : This function just takes the key and it's value both as `std::string` and find the key form all the vectors written by the parser and applies it's values (Note this doesn't say anything even if the key isn't present so use get to check if it is othervise it won't say anything itself as it is a void function, Also set don't supports arrays so it will not even search for arrays so be sure of what you are doing in your program).

`HELL6_99MO::set_array` : This function just takes the key and it's value, The key is `std::string` and value is `std::vector <std::string>` and sets the value to an array key (Note this doesn't say anything even if the key isn't present so use get to check if it is othervise it won't say anything itself as it is a void function).

`HELL6_99MO::new_key` : This function just takes the key and it's type both as `std::string` and defines that key with that type, But the value is default to use `set()` in order to set it's value(Note this doesn't say anything even if the key isn't present so use get to check if it is othervise it won't say anything itself as it is a void function).

`HELL6_99MO::write` : This function just takes a file name as `std::string` and writes the defined configuration to that file with optimisations.(Note this doesn't say anything even if the key isn't present so use get to check if it is othervise it won't say anything itself as it is a void function), Also remember this function will write optimised config means it's structure may be entirely changed so please don't directly write the human written configs with this, use this if the config is already generated by a program (Recommended).


This was the official API for the `HELL6.99MOCC 1` Library and in this version of the library future helper functions are set on goals `set_array` , `write` , `write_back`.

## Accessing Keys in API
When you want to access keys in the api you can use just the key name with it's address for example a scoped key like:
```hell6.99mo
scope:
    key = value
    scope2:
        hello = world
scope3:
    cstdio:
        version = 1
```

you can access any scope key like `<scope name>.<key>` eg `scope.key`, even nesting like `scope.scope2.hello`, another example `scope3.cstdio.version` and these are lexer tokens means these will work even before you use parser.

## Simple Exercise Of What We Have Learns
Let's write our simple config file and save it as `.h699` file extension (Chose what ever you want , h699 is recommended anyway, Althought it won't change any output).

```hell6.99mo
user:
    name = "Emily"
    sex = "female"
    age = 24
    skills = ["Web Development", "Game Development", "Python", "Cloud Management"]
    projects = ["MyWebsite", "MyGame", "MyMonsterMonkey_In_python"]
    project_meta_data:
        MyWebsite = "A Simple Fullstack website showcasing Node.JS Skills"
        MyGame    = "A Simple 2d Game Made with Godot"
        MyMonsterMonkey_In_python = UNIDEF
```

Let's write the simple C++ program to parse this!

```cxx
#include "path/to/hell6.99mocc library"
#include <iostream>

int main(){

    HELL6_99MO File("path/to/config.h699");
    File.Parse(); 
    
    std::string user_name = File.get ("user.name").string_value;
    std::cout << "User Name: "<<user_name<<"\n\n";

}
```

*Note: You can also use inline scopes in config like scope: value = 1, you can later access this as scope.value because sometimes we only need one value in scope so we does this and later you can append more children to scope by scope: blah-blah-blah, As scopes can be re-opened.*

---

*Fun Fact: HELL6.99MO has 6.99% in between because lol it's not pure Model O , It's 6.99% in Model O in the most accurate sence because Model O also allows flexible Arrays which HELL6.99MO don't, But it's still Model O based but now pure Model O by GTG.*

---

## Efficient Use Of UNIDEF - Example
This Example shows one of the most efficient use of `UNIDEF` to tell that these settings in config must exist.

```hell6.99mo
global_settings:
    resolution = UNIDEF
    graphics_preset = UNIDEF

mygame_settings:
    resolution = 1080
    graphics_preset = "High"
```

*mygame_settings is a different scope from the global_settings so values are also different.*

---

## Contributing ?
Checkout the [contribution guidelines](CONTRIBUTING.md).

---

Thanks for reading! Have a nice day by ghgltggamer at 3:36 PM , 6/25/25
