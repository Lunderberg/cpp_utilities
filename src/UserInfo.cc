#include "UserInfo.hh"

#ifdef __linux__

#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

std::string username() {
  {
    const char* user = getenv("USER");
    if(user){
      return user;
    }
  }

  {
    auto bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
    passwd user_info;
    passwd* result;
    std::vector<char> buffer(bufsize);
    getpwuid_r(getuid(),
               &user_info,
               buffer.data(), bufsize,
               &result);
    if(result){
      return user_info.pw_name;
    }
  }

  return "";
}

std::string home_directory() {
  {
    const char* user = getenv("HOME");
    if(user){
      return user;
    }
  }

  {
    auto bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
    passwd user_info;
    passwd* result;
    std::vector<char> buffer(bufsize);
    getpwuid_r(getuid(),
               &user_info,
               buffer.data(), bufsize,
               &result);
    if(result){
      return user_info.pw_dir;
    }
  }

  return "";
}


#endif


#ifdef _WIN32

#include <windows.h>

// NOT IMPLEMENTED YET
// Use http://stackoverflow.com/questions/1607271/how-do-you-find-the-current-user-in-a-windows-environment

#endif
