#ifndef YAAMF_TOOLS_H_
#define YAAMF_TOOLS_H_

#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <time.h>
#include <vector>

using namespace std;

// A simple timer
class Timer {
public:
  Timer() { start_ = clock(); }

  // time unit: seconds
  inline double duration() const {
    return (double)(clock() - start_) / CLOCKS_PER_SEC;
  }

  inline void end() const {
    cout << fixed << setprecision(6) << "\nTime: " << duration() << " s\n"
         << endl;
  }
  inline void end_all() const {
    cout << fixed << setprecision(6) << "\nTotal time: " << duration() << " s\n"
         << endl;
  }

  inline void reset() { start_ = clock(); }

private:
  clock_t start_;
};

#endif // YAAMF_TOOLS_H_