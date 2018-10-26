#include "used_libraries.h"
#include "auxiliaries.h"
#include "enigma.h"

int main(int argc, char const *argv[]) {
  //check that enough parameters are passed
  if (!enough_parameters(argc,argv)){
    std::cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << '\n';
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  //ENIGMA SET UP
  Enigma enigma(argc,argv);
  int n = enigma.initialize();
  if (n!=NO_ERROR) {return n;}

  //START CIPHERING
  char c;
  while(cin>>c){
    if(c<'A' || c>'Z'){
      std::cerr <<c<<" is not a valid input character (input characters must be upper case letters A-Z)!"<< '\n';
      return INVALID_INPUT_CHARACTER;
    }else{
      enigma.cipher(c);
      std::cout <<c;
    }
  }

  //END OF MAIN PGRM
  return NO_ERROR;
}
