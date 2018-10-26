#ifndef MACHINE_H
#define MACHINE_H

#include "used_libraries.h"
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "component.h"
#include "auxiliaries.h"

class Enigma{
public:
 Plugboard pb;
 Reflector rf;
 vector<Rotor> rot_array;
 std::vector<int> rot_init_position;
 string rot_init_file_location;
public:
  //[enig.0.0] base constructor
  Enigma(int argc, char const *argv[]);

  //[enig.0.1] base destructor
  ~Enigma();

  //[enig.1.0] print rot_init_position
  void print_rot_init_pos();

  //[enig.1.2] check that initial rotor positions are well defined
  int check_rotor_init_file();

  //[enig.1.3] check that all key components and
  // the rotors initial position file are well defined
  int check_configuration();

  //[enig.1.4] check and initialize the the components
  int initialize();

  //[enig.1.5] get the ouput of an after passing through the rotors
  //from the plugboard to the reflector
  void rotor_pb_to_rf(int& c);

  //[enig.1.6] get the ouput of an after passing through the rotors
  //from the reflector to the plugboard
  void rotor_rf_to_pb(int& c);

  //[enig.1.7] cipher the character
  void cipher(char& c);


};
#endif
