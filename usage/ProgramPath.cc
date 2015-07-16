#include <iostream>

#include "ProgramPath.hh"

int main(){
  std::cout << "The executable is located in " << program_path() << std::endl;
}
