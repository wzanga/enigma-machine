#include "enigma.h"

//[enig.0.0] base constructor
Enigma::Enigma(int argc, char const *argv[]){
  //the position 0 is ./enigma
  for (int i = 1; i < argc; i++){
    string x = get_extension(argv[i],'.');
    if (x==".pb"){
      Plugboard* temp_pb = new Plugboard(argv[i]);
      pb = *temp_pb;
      delete(temp_pb);
    }else if(x==".rf"){
      Reflector* temp_rf = new Reflector(argv[i]);
      rf = *temp_rf;
      delete(temp_rf);
    }else if(x==".rot"){
      Rotor* temp_rot = new Rotor(argv[i]);
      rot_array.push_back(*temp_rot);
      delete(temp_rot);
    }else if(x==".pos"){rot_init_file_location = argv[i];}
  }
}

//[enig.0.1] base destructor
Enigma::~Enigma(){}

//[enig.1.0] print rot_init_position
void Enigma::print_rot_init_pos(){
  for (int i = 0; i < (int)rot_init_position.size(); i++) {
    if (i==0) {
    }else if (i==(int)rot_init_position.size()-1){
      std::cout <<rot_init_position[i]<<"}" << '\n';
    }else{
      std::cout <<rot_init_position[i]<<",";
    }
  }
}

//[enig.1.2] check that initial rotor positions are well defined
int Enigma::check_rotor_init_file(){
  //can connect to the configuration file ?
  ifstream file(rot_init_file_location.c_str());
  if (file.fail()){
    std::cerr << "Cannot open the file "<<rot_init_file_location<< '\n';
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  //verification 0 : check that the number of parameters is valid
	int nbr_param = get_nbr_param(file,' ');
	if(nbr_param<(int)rot_array.size()){
    std::cerr << "No starting position for rotor "<<(int)rot_init_position.size()<<" in rotor position file: "<<rot_init_file_location<<'\n';
    file.close();
    return NO_ROTOR_STARTING_POSITION;
	}else{
		//rewind the file
		file.clear();
		file.seekg (0, ios::beg);
	}
  //read and check the configuration file
  for(file>>ws;!file.eof();file>>ws) {
    string str_nbr;
    getline(file,str_nbr,' ');
    //handle the last character read
    if(str_nbr[(int)str_nbr.size()-1]=='\n'){
      str_nbr.resize (str_nbr.size () - 1);
    }
    int numeric = alternative_stoi(str_nbr);
    //verification 1 : is that number actually a numeric character
    if (!has_only_numeric_characters(str_nbr)){
      std::cerr << "Non-numeric character in rotor positions file "<<rot_init_file_location<< '\n';
      //std::cout << "causing exit : " <<str_nbr<< '\n';
      file.close();
      return NON_NUMERIC_CHARACTER;
    }
    //verification 2 : is that number between 0 and 25
    if (numeric<0 || numeric >25){
      std::cerr << "Invalid index in rotor positions file:"<<rot_init_file_location<< '\n';
      //std::cout << "causing exit : " <<str_nbr<< '\n';
      file.close();
      return INVALID_INDEX;
    }
    //there is no error, number is added to the table
    rot_init_position.push_back(numeric);
  }
  //close the ifstream check the number of parameters
  file.close();
  return NO_ERROR;
}

//[enig.1.3] check that all key components and
// the rotors initial position file are well defined
int Enigma::check_configuration(){
  int output=0;
  //check the plugboard
  output = pb.check_configuration();
  if (output!=NO_ERROR){return output;}
  //check the reflector
  output = rf.check_configuration();
  if (output!=NO_ERROR){return output;}
  //check the rotors
  for (int i = 0; i<(int)rot_array.size(); i++) {
    output = rot_array[i].check_configuration();
    if (output!=NO_ERROR){return output;}
  }
  //check rotors initial positions if needed
  if (rot_array.size()!=0) {
    output = check_rotor_init_file();
    if (output!=NO_ERROR){return output;}
  }
  //No error encountered
  return NO_ERROR;
}

//[enig.1.4] check and initialize the components
int Enigma::initialize(){
  //check the check_configuration
  int n = check_configuration();
  if (n!=NO_ERROR) {return n;}
  //Plugboard
  pb.restructure_table();
  //reflector
  rf.restructure_table();
  //rotor(s)
  for (int i = 0; i < (int)rot_array.size(); i++) {
    rot_array[i].set_position(rot_init_position[i]);
  }
  //end
  return NO_ERROR;
}

//[enig.1.7] cypher the character
void Enigma::cipher(char& c){
  //convert to alphabet
  int c1 = ascii_to_alphabet(c);
  //std::cout << "|>:"<<c1;
  //swith the letter with the plugboard
  pb.encode(c1);
  //std::cout << "|pb1:"<<c1;
  //pass through the rotors right-to-left
  if ((int) rot_array.size()>0) {
  rotor_pb_to_rf(c1);
  }
  //reflect the letter with the reflector
  rf.encode(c1);
  //std::cout << "|rf:"<<c1;
  //pass through the rotors left-to-right
  if ((int) rot_array.size()>0) {
  rotor_rf_to_pb(c1);
  }
  //swith the letter with the plugboard
  pb.encode(c1);
  //std::cout << "|pb2:"<<c1;
  //convert to ascii and return
  c = alphabet_to_ascii(c1);
}

//[enig.1.5] get the ouput of an after passing through the rotors
//from the plugboard to the reflector
void Enigma::rotor_pb_to_rf(int& c){
  //except for the first one, a rotor moves if all the rotors
  //prior to it are going to hit their notches
  for (int i = 0; i < (int)rot_array.size()-1; i++){
    bool increment=true;
    for (int j = i+1; j < (int)rot_array.size(); j++){
      increment = increment & rot_array[j].next_position_is_notch();
    }
    if (increment==true){
      rot_array[i].rotate();
    }
  }
  //increment the right rotor and encrypt
  rot_array[(int)rot_array.size()-1].rotate();
  //encode the character
  for (int i = (int)rot_array.size()-1; i >=0; i--){
    rot_array[i].encode(c);
    //std::cout << "|rotor"<<i<<":"<<c;
  }
}

//[enig.1.6] get the ouput of an after passing through the rotors
//from the reflector to the plugboard
void Enigma::rotor_rf_to_pb(int& c){
  for (int i = 0; i < (int)rot_array.size(); i++) {
    rot_array[i].decode(c);
    //std::cout << "|xrotor"<<i<<":"<<c;
  }
}
