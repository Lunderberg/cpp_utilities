#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "RateCounter.hh"

int main() {
  RateCounter counter;
  for(int i=0; i<1000; i++) {
    counter.AddToCounter();
    std::cout << std::string(75, ' ') << "\r"
              << "Count: " << counter.TotalCounted() << "\t"
              << "Avg Rate: " << counter.AverageRate() << "\t"
              << "Recent Rate: " << counter.RecentRate() << "\r"
              << std::flush;

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  std::cout << std::endl;
}
