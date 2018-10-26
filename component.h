#ifndef COMPONENT_H
#define COMPONENT_H

#include "auxiliaries.h"
#include "used_libraries.h"

class Component{
	//attributes for the subclasses
protected:
	string location;
	vector<int> table;
public:
	//[comp.0.0][working] default constructor
	Component();

	//[comp.0.1][working] base constructor
	Component(string cfl);

	//[comp.0.2][working] base destructor
	virtual ~Component();

	//[comp.1.0][working] print the mapping table
	void print_table();

	//[comp.1.1][working] print the location of the configuration file
	void print_location();

	//[comp.1.2][--] check if the configuration is well-formed
  virtual int check_configuration()=0;

	//[comp.1.3][working]restructure the table attatribute
	//such that if i and j are linked then table[i]=j and table[j]=i
	//mainly used for the plugboard and the reflector
	void restructure_table();

	//[com.1.4][working] encode an int according to the table
	//(a redefinition will be done in the Rotor Class)
	void encode(int& c);

	//[com.1.5]
	// in case a letter is already mapped, get relevant info
	void case_already_mapped(ifstream& file, int& input_to_map, int& output, int& input_mapped);

};
#endif
