#ifndef _RATECOUNTER_HH_
#define _RATECOUNTER_HH_

#include <chrono>
#include <deque>

class RateCounter {
public:
  typedef std::chrono::time_point<std::chrono::steady_clock> time_point;
  typedef decltype(time_point() - time_point()) time_duration;

  /// Construct a
  /**
     @param recent_period The length of time to average when returning the recent rate.
   */
  RateCounter(time_duration recent_period = std::chrono::seconds(5));

  /// Set the duration that is averaged over when determining the RecentRate.
  void SetRecentLength(time_duration duration) { recent_period = duration; }

  void AddToCounter(size_t quantity = 1);

  size_t TotalCounted() const;
  double AverageRate() const;
  double RecentRate() const;

private:
  time_point now() const;
  void allocate_recent_points();

  size_t total_counted;
  time_point start_time;

  std::deque<size_t> counts_per_interval;
  time_duration interval_length;
  time_point current_interval_start;
  time_duration recent_period;
};


#endif /* _RATECOUNTER_HH_ */
