#ifndef YAAMF_INTEGRAL_H_
#define YAAMF_INTEGRAL_H_

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// basic integral class
// only contains a vector of propagator indices
class Integral {
public:
  explicit Integral(size_t n) : indices_(n) {}
  explicit Integral(const vector<int> &indices) : indices_(indices) {}
  ~Integral() {}

  // get the index of a specified position
  int &operator[](size_t i) { return indices_[i]; }
  const int &operator[](size_t i) const { return indices_[i]; }

  // get the size(number of propagators) of the integral
  size_t size() const { return indices_.size(); }

  // print an integral
  friend ostream &operator<<(ostream &os, const Integral &integral);

private:
  vector<int> indices_;
};

typedef unique_ptr<Integral> IntegralPtr;

#endif // YAAMF_INTEGRAL_H_