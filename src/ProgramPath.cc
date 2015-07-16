#include "ProgramPath.hh"


#ifdef __linux__

#include <unistd.h>
#include <limits.h>

std::string program_path(){
  char buff[PATH_MAX+1];
  size_t len = readlink("/proc/self/exe", buff, sizeof(buff)-1);
  buff[len] = '\0';

  std::string exe_path = buff;
  return exe_path.substr(0, exe_path.find_last_of('/'));
}
#endif


#ifdef _win32
// Not implemented yet.
// When I need it, look at http://stackoverflow.com/questions/2647429
// Not putting it in here, because I can't test it at the moment.
#endif
