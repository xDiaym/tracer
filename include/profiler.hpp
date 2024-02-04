#pragma once

#include <chrono>


struct ProfilingScope {
  std::string_view name, file;
  size_t line;
};

struct ProfilerTrait {
  using clock_t = std::chrono::steady_clock;
  using time_point_t = clock_t::time_point;

  static void log(const ProfilingScope &scope, time_point_t start, time_point_t end) {
    using namespace std::chrono;

    const auto duration = duration_cast<milliseconds>(end - start);
    constexpr auto fmt = "[Profiling \"{}\"]\n"
                         "duration={}.{}s\n"
                         "file={} line={} start={} end={}\n";
    std::cout << std::format(fmt, scope.name, duration.count() / 1000, duration.count() % 1000, scope.file, scope.line,
                             start.time_since_epoch().count(), end.time_since_epoch().count());
  }
};

template<typename Trait = ProfilerTrait>
class Profiler {
  using time_point_t = Trait::time_point_t;
  using clock_t = Trait::clock_t;

  ProfilingScope scope_;
  time_point_t start_;

public:
  Profiler(std::string_view name, std::string_view file, size_t line)
      : scope_(name, file, line), start_(clock_t::now()) {}

  ~Profiler() {
    const time_point_t end = clock_t::now();
    Trait::log(scope_, start_, end);
  }
};

#define _CONCAT_IMPL(a, b) a##b
#define _CONCAT(a, b) _CONCAT_IMPL(a, b)
#define PROFILE_SCOPE(name) Profiler _CONCAT(__profiler, __LINE__)(name, __FILE__, __LINE__)
