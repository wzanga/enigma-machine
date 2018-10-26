#include "component.h"

//[comp.0.0][working] default constructor
Component::Component(): location(""){}

//[comp.0.1] base constructor
Component::Component(string cfl): location(cfl){}

//[comp.0.2][working] base destructor
Component::~Component(){}

//[comp.1.0] print the mapping table
void Component::print_table(){
  for (int i = 0; i < (int)table.size(); i++) {
    if (i==0) {
      std::cout << "table = {"<<table[i]<<",";
    }else if (i==(int)table.size()-1){
      std::cout <<table[i]<<"}" << '\n';
    }else{
      std::cout <<table[i]<<",";
    }
  }
}

//[comp.1.1][working] print the location of the configuration file
void Component::print_location(){
  std::cout << "cf_location: "<<location<< '\n';
}

//[comp.1.3][--] check if the configuration is well-formed
int Component::check_configuration(){return 0;}

//[comp.1.4] if i and j are linked then table[i]=j and table[j]=i
void Component::restructure_table(){
  int n=table.size();
  //create table with 0,1....24,25 in this order
  int tab[26];
  for (int i=0; i<26; i++){ tab[i]=i;}
  //pair the letters which are swichted
  for(int i=0; i<=n-2;){
    tab[table[i]]=table[i+1];
    tab[table[i+1]]=table[i];
    i+=2;
  }
  //augment the size of table
  for (int i=0; i < 26-n;i++){ table.push_back(0);}
  //transfer the information of tab to table
  for (int i=0; i < 26; i++) { table[i]=tab[i]; }
}

//[component.1.4] switch the interger according to the table
void Component::encode(int& c){ c=table[c];}

//[com.1.5]
// in case a letter is already mapped, get relevant info
void Component::case_already_mapped(ifstream& file, int& input_to_map, int& output, int& input_mapped){
  //The ouput is already mapped with a previous number
  for (int i = 0; i < (int) table.size(); i++) {
    if (table[i]==output){
      input_mapped = table[i-1];
    }
  }
  //get the next number to map
  string str_nbr;
  getline(file,str_nbr,' ');
  input_to_map = alternative_stoi(str_nbr);
  return;
}
