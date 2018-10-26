#ifndef REFLECTOR_H
#define REFLECTOR_H

//include the super-class
#include "component.h"

class Reflector : public Component {
public:
  //[rf.0.0][working] default constructor
  Reflector();

	//[rf.0.1][working] base constructor
  Reflector(string cfl);

  //[rf.0.2][working] base constructor
  ~Reflector();

  ///[rf.1.0] check that the configuration file is well-formed
  int check_configuration();
};
#endif
