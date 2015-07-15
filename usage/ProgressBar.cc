#include <chrono>
#include <thread>

#include "ProgressBar.hh"

int main(){
  int n = 1e4;

  ProgressBar prog(n, 100);
  for(int i=0; i<n; i++){
    prog.Show(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
