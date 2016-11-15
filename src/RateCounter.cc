#include "RateCounter.hh"

#include <algorithm>
#include <iostream>

namespace chr = std::chrono;

RateCounter::RateCounter(time_duration recent_period)
  : total_counted(0), start_time(now()),
    interval_length(chr::milliseconds(100)),
    current_interval_start(start_time-interval_length),
    recent_period(recent_period) { }

size_t RateCounter::TotalCounted() const {
  return total_counted;
}

double RateCounter::AverageRate() const {
  chr::duration<double> seconds = now() - start_time;
  return total_counted / seconds.count();
}

double RateCounter::RecentRate() const {
  auto time_since_period_end = now() - (current_interval_start + interval_length);
  auto valid_time = recent_period - time_since_period_end;
  int num_entries = std::min<int>(valid_time / interval_length,
                                  counts_per_interval.size());
  if(num_entries <= 0) {
    return 0;
  }

  size_t recent_counts = 0;
  for(auto it = counts_per_interval.end() - num_entries;
      it != counts_per_interval.end(); it++) {
    recent_counts += *it;
  }

  chr::duration<double> seconds = std::min(recent_period,
                                           now() - start_time);
  return recent_counts / seconds.count();
}

chr::time_point<chr::steady_clock> RateCounter::now() const {
  return chr::steady_clock::now();
}

void RateCounter::AddToCounter(size_t quantity) {
  allocate_recent_points();

  total_counted += quantity;
  counts_per_interval.back() += quantity;
}

void RateCounter::allocate_recent_points() {
  // Check whether we need to start a new interval, and if so, how many.
  int intervals_advancing = (now() - current_interval_start) / interval_length;

  if(intervals_advancing > 0) {
    // First, drop any time periods that are no longer "recent"
    int max_size = recent_period / interval_length;
    int to_drop = std::min(int(counts_per_interval.size()) + intervals_advancing - max_size,
                           int(counts_per_interval.size()));
    if(to_drop > 0) {
      counts_per_interval.erase(counts_per_interval.begin(),
                              counts_per_interval.begin() + to_drop);
    }

    // Make the new time periods.
    // If we don't have any current intervals, then no need to fill it with zeros.
    if(counts_per_interval.size()) {
      counts_per_interval.resize(counts_per_interval.size() + intervals_advancing);
    } else {
      counts_per_interval.resize(1);
    }

    // Keep track of the time of the latest interval.
    current_interval_start += intervals_advancing*interval_length;
  }
}
