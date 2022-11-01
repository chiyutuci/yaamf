#include "integral.h"

ostream &operator<<(ostream &os, const Integral &integral) {
  os << "[";
  for (size_t i = 0; i < integral.size(); ++i)
    os << integral[i] << ", ";
  os << "\b\b]" << endl;
  return os;
}