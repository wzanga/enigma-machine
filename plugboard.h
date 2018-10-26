#ifndef PLUGBOARD_H
#define PLUGBOARD_H

//include the super-class
#include "component.h"

class Plugboard : public Component {
public:
	//[pb.0.0][working] default constructor
  Plugboard();

  //[pb.0.1][working] base constructor
  Plugboard(string cfl);

  //[pb.0.2][working] base destructor
	~Plugboard();

  //[pb.1.0][working] read the configuration file
  int check_configuration();
};
#endif
