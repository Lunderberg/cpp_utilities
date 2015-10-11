#include <iostream>
#include <string>

#include "FullPath.hh"

int main(int argc, char** argv){
  if(argc > 1){
    std::string path = full_path(argv[1]);
    std::cout << "Relative path: " << argv[1] << std::endl;
    std::cout << "Full path: " << path << std::endl;
  }
}
