#include <iostream>

#include "PopenStream.hh"

int main(){
  std::string name;
  int n;

  {
    PopenStream ps("echo hi 5");
    ps >> name;
    ps >> n;
    std::cout << "Name: " << name << "\tn: " << n << std::endl;
  }

  {
    PopenStream ps("echo abcdef");
    char buf[4];
    ps.read(buf, 3);
    buf[3] = '\0';

    std::string rest;
    ps >> rest;

    std::cout << "First 3: " << buf << "\tRest: " << rest << std::endl;
  }
}
