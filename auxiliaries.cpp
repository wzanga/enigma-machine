#include "auxiliaries.h"

//function [0.0.4]: return true if the string is in a string vector
bool in_vector(const vector<string>& str_vect, string str){
	for (int i = 0; i < (int) str_vect.size(); i++) {
		if ( str_vect[i]==str) {
			return true;
		}
	}
	return false;
}

//function [0.0.5][]: return true if an int is in a int vector
bool in_vector(const vector<int>& int_vect, int& n){
	for(int i=0; i<(int)int_vect.size();i++){
		if (int_vect[i]==n) {
			return true;
		}
	}
	return false;
}

//function [0.0.6][] : return the symbol after the separator
string get_extension(const char str[], char separator){
	int index=0;
	for (; index< (int)strlen(str) && str[index]!=separator ;index++) {
	}
	return str+index;
}

//function [0.0.7][] : convert a lower-case
//ASCII char into the 0-based alphabet
int ascii_to_alphabet(char& c){
	return int(c)-int('A');
}

///function [0.0.8][] : inverse of function [0.0.7]
char alphabet_to_ascii(int& n){
	return char(n + int('A'));
}

///function [0.0.9][] : check that enough parameters are provided
bool enough_parameters(int& argc, char const *argv[]){
	//first read all the extensions
	vector<string> ext_holder;
	for (int i = 1; i < argc; i++) {//the position 0 is ./enigma
		ext_holder.push_back(get_extension(argv[i],'.'));
	}
	//is there at least one rotor ?
	if (in_vector(ext_holder, ".rot")){
		string ext_base[3] = {".pb",".rf",".pos"};
		for (int i = 0; i < 3; i++) {
			if (!in_vector(ext_holder, ext_base[i])){return false;}
		}
	}else{
		//in_vector(ext_holder,".pos")|| taken out because it does not matter
		//for the good functionning of the machine
		if (!in_vector(ext_holder,".pb") || !in_vector(ext_holder,".rf")){
			return false;
		}
	}
	return true;
}


///function [0.0.10][] : same result as stoi()
int alternative_stoi(const string& str){
	int n=0;
	for (int i = 0; i < (int) str.size(); i++) {
		if (str[i]>= '0' && str[i] <= '9') {
			n=n*10 + str[i] -'0';
		}else{ return -1;}
	}
	return n;
}

///function [0.0.11][] : return true only if a string made up
// of numeric characters only
bool has_only_numeric_characters(string& str){
	for (int i = 0; i < (int)str.size(); i++) {
		if ( str[i]<'0' || str[i]>'9') {return false;}
	}
	return true;
}

///function [0.0.12][] : get the number of parameters in a file
int get_nbr_param(ifstream& file, char separator){
	int n=0;
	//read and check the configuration file
	for(file>>ws;!file.eof();file>>ws) {
		string str;
		getline(file,str,separator);
		n++;
	}
	return n;
}
