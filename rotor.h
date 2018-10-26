#ifndef ROTOR_H
#define ROTOR_H

//include the super-class
#include "component.h"

class Rotor : public Component {
public:
  vector<int> notch;
  int position;
public:
  //[rot.0.0][working] default constructor
  Rotor();

	//[rot.0.1][working] base constructor
  Rotor(string cfl);

  //[rot.0.2][working] base constructor
  ~Rotor();

  //[rot.1.0][working] print the notch position
  void print_notch();

  //[rot.1.1][working] set the position of the rotor to the value entered
  void set_position(int& p);

  //[rot.1.2][working] rotate a rotor
  void rotate();

  ///[rot.1.3][--] check that the configuration file is well-formed
  int check_configuration();

  //[rot.1.4][--] return true if the next position of the rotor if a notch
  bool next_position_is_notch();

  //[rot.1.5][--] going right to left on the rotor
  void encode(int& c);

  //[rot.1.6][--] going left to right on the rotor
  void decode(int& c);

  //[rot.1.7][--] read the notches in the configuration file
  int read_the_notch(ifstream& file);
};
#endif
