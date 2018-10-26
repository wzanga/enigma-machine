#ifndef AUXILIARIES_H
#define AUXILIARIES_H

#include "used_libraries.h"

//function [0.0.4][]: return true if the string is in q string vector
bool in_vector(const vector<string>& str_vect, string str);

//function [0.0.5][]: return true if an int is in a int vector
bool in_vector(const vector<int>& int_vect, int& n);

//function [0.0.6][] : return the symbol after the separator
string get_extension(const char str[], char separator);

//function [0.0.7][] : convert a lower-case
//ASCII char into the 0-based alphabet
int ascii_to_alphabet(char& c);

///function [0.0.8][] : inverse function of [0.0.7]
char alphabet_to_ascii(int& n);

///function [0.0.9][] : check that enough parameters are provided
bool enough_parameters(int& argc, char const *argv[]);

///function [0.0.10][] : same result as stoi() since stoi() requires c++11
int alternative_stoi(const string& str);

///function [0.0.11][] : return true only if a string made up
// of numeric characters only
bool has_only_numeric_characters(string& str);

///function [0.0.12][] : get the number of parameters in a file
int get_nbr_param(ifstream& file, char separator);

#endif
