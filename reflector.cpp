#include "reflector.h"

//[rf.0.0][working] default constructor
Reflector::Reflector():Component(){}

//[rf.0.1] base constructor
Reflector::Reflector(string cfl):Component(cfl){}

//[rf.0.2] base constructor
Reflector::~Reflector(){}

///[rf.1.0] check that the configuration file is well-formed
int Reflector::check_configuration(){
	//can connect to the configuration file ?
	ifstream file(location.c_str());
  if (file.fail()){
    std::cerr << "Cannot open the file:"<<location<< '\n';
    return ERROR_OPENING_CONFIGURATION_FILE;
	}

	//verification 0 : check that the number of parameters is valid
	int nbr_param = get_nbr_param(file,' ');
	if(nbr_param!=0 && nbr_param%2!=0){
		//ood number of parameters
		std::cerr << "Incorrect (odd) number of parameters in reflector file "<<location<<'\n';
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
		file.close();
	}else if(nbr_param>26){
		//too many pameters
		std::cerr << "Incorrect number of parameters in reflector file: "<<location<<'\n';
		file.close();
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	}else if (nbr_param!=26) {
		//no exacly 13 pairs
		std::cerr << "Insufficient number of mappings in reflector file: "<<location<<'\n';
		file.close();
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	}else{
		//rewind the file
		file.clear();
		file.seekg (0, ios::beg);
	}
	//read and check the configuration file
  for(file>>ws;!file.eof();file>>ws) {
		//read file
		string str_nbr;
		getline(file,str_nbr,' ');
    //handle the last character read
    if(str_nbr[(int)str_nbr.size()-1]=='\n'){
      str_nbr.resize (str_nbr.size () - 1);
    }
    int numeric = alternative_stoi(str_nbr);
		//verification 1 : reflector connection
    if (in_vector(table,numeric)){
      std::cerr << "Invalid reflector mapping in file "<<location<< '\n';
			//std::cout << "causing exit:"<<str_nbr<< '\n';
			file.close();
      return INVALID_REFLECTOR_MAPPING;
    }
		//verification 2 : is that number actually a numeric character
		if (!has_only_numeric_characters(str_nbr)){
			std::cerr << "Non-numeric character in reflector file "<<location<< '\n';
			//std::cout << "causing exit:"<<str_nbr<< '\n';
			file.close();
			return NON_NUMERIC_CHARACTER;
		}
		//verification 3 : is that number between 0 and 25
		if (numeric<0 || numeric >25){
		 	std::cerr << "Invalid index in reflector file "<<location<< '\n';
			//std::cout << "causing exit:"<<str_nbr<< '\n';
			file.close();
		 	return INVALID_INDEX;
	 	}
		//there is no error, number is added to the table
		table.push_back(numeric);
	}
  //close the ifstream check the number of parameters
	file.close();
	return NO_ERROR;
}
