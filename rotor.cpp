#include "rotor.h"

//[rot.0.0][working] default constructor
Rotor::Rotor():Component(){}

//[rot.0.0] base constructor
Rotor::Rotor(string cfl):Component(cfl){}

//[rot.0.1][working] base constructor
Rotor::~Rotor(){}

//[rot.1.0][working] print notch array
void Rotor::print_notch(){
  if ((int)notch.size()==1) {
    std::cout << "notch_array ={"<<notch[0]<<"}"<< '\n';
    return;
  }
  for (int i = 0; i < (int)notch.size(); i++) {
    if (i==0) {
      std::cout << "notch array = {"<<notch[i]<<",";
    }else if (i==(int)notch.size()-1){
      std::cout <<notch[i]<<"}" << '\n';
    }else{
      std::cout <<notch[i]<<",";
    }
  }
}

//[rot.1.1][working] set the position of the rotor to the value entered
void Rotor::set_position(int& p){
  position =p;
}

///[rot.1.3][--] check that the configuration file is well-formed
int Rotor::check_configuration(){
  //can connect to the configuration file ?
	ifstream file(location.c_str());
  if (file.fail()){
    std::cerr << "Cannot open the file "<<location<< '\n';
    return ERROR_OPENING_CONFIGURATION_FILE;
	}

  //verification 0 : check that the number of parameters is valid
  int nbr_param = get_nbr_param(file,' ');
  if(nbr_param<26){
    //not all input mapped
    std::cerr << "Not all inputs mapped in rotor file: "<<location<< '\n';
    file.close();
    return INVALID_ROTOR_MAPPING;
  }else{
    //rewind the file
    file.clear();
    file.seekg (0, ios::beg);
  }

	//read and check the configuration file
  for(file>>ws;!file.eof();file>>ws) {
    //verification 1 : check if the pgrm starts reading the notches
    if (table.size()==26){
      int n =read_the_notch(file);
      if (n!=NO_ERROR) { return n;}
      break; //the scope is the for() loop
    }
    //otherwise read the file
		string str_nbr;
		getline(file,str_nbr,' ');
    if(str_nbr[(int)str_nbr.size()-1]=='\n'){
      str_nbr.resize (str_nbr.size () - 1);
    }
    int numeric = alternative_stoi(str_nbr);
		//verification 2 : rotor connection
    if (in_vector(table,numeric)){
      int input_to_map = 0;
      int output = numeric;
      int input_mapped =0;
      case_already_mapped(file,input_to_map,output,input_mapped);
      //prof:Invalid mapping of input 13 to output 3 (output 3 is already mapped to from input 6)
      std::cerr << "Invalid mapping of input (ouput "<<output<<" is already mapped to from input "<<input_mapped<<")"<<'\n';
      //std::cout << "causing exit:"<<str_nbr<< '\n';
      file.close();
      return INVALID_ROTOR_MAPPING;
    }
		//verification 3 : is that number actually a numeric character
		if (!has_only_numeric_characters(str_nbr)){
			std::cerr << "Non-numeric character for mapping in rotor file "<<location<< '\n';
      //std::cout << "causing exit:"<<str_nbr<< '\n';
      file.close();
			return NON_NUMERIC_CHARACTER;
		}
		//verification 4 : is that number between 0 and 25
		if (numeric<0 || numeric >25){
		 	std::cerr << "Invalid index in rotor file "<<location<< '\n';
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

//[rot.1.2][working] rotate a rotor
void Rotor::rotate(){
  position = (position + 1)%26;
}

//[rot.1.4][--] return true if the next position of the rotor if a notch
bool Rotor::next_position_is_notch(){
  int next = (position + 1)%26;
  if (in_vector(notch,next)){return true;}
  return false;
}

//[rot.1.7][--] read the notches in the configuration file
int Rotor::read_the_notch(ifstream& file){
  for(file>>ws;!file.eof();file>>ws) {
		string str_nbr;
		getline(file,str_nbr,' ');
    //handle the last character read
    if(str_nbr[(int)str_nbr.size()-1]=='\n'){
      str_nbr.resize (str_nbr.size () - 1);
    }
    int numeric = alternative_stoi(str_nbr);
    //verification 3 : is that number actually a numeric character
		if (!has_only_numeric_characters(str_nbr)){
			std::cerr << "Non-numeric character  for mapping in rotor file "<<location<< '\n';
      //std::cout << "causing exit:"<<str_nbr<< '\n';
      file.close();
			return NON_NUMERIC_CHARACTER;
		}
		//verification 4 : is that number between 0 and 25
		if (numeric<0 || numeric >25){
		 	std::cerr << "Error : there is a number not between 0 and 25 in the file "<<location<< '\n';
      //std::cout << "causing exit:"<<str_nbr<< '\n';
      file.close();
		 	return INVALID_INDEX;
	 	}
    //add the notch to the notch array
    notch.push_back(numeric);
  }
  return NO_ERROR;
}

//[rot.1.6][--] going left to right on the rotor
void Rotor::decode(int& c){
  //convert absolute to relative position
  c = (c+position)%26;
  //use the map to ge back t the corresponding code
  for (int i = 0; i < (int) table.size(); i++) {
    if (table[i]==c){
      c=i;
      break;
    }
  }
  //convert from relative to absolute position
  c = (c - position + 26)%26;
  return;
}

//[rot.1.5][--] going right to left on the rotor
void Rotor::encode(int& c){
  //convert absolute to relative position
  c = (c+position)%26;
  //use the map to get the corresponding code
  c = table[c];
  //convert from relative to absolute position
  c = (c - position + 26)%26;
  //std::cout << "absolute out c:"<<c<< '\n';
  return;
}
