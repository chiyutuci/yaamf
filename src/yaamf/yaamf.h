#ifndef YAAMF_H_
#define YAAMF_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "yaml-cpp/yaml.h"

#include "yaamf/integral.h"
#include "yaamf/mathtypes.h"
#include "yaamf/tools.h"

using namespace std;

class Yaamf;

// integral family
class Family {
public:
  explicit Family(unsigned nint, unsigned next, unsigned nprop);
  ~Family();

private:
  friend class Yaamf;

  // number of internal momenta, external momenta
  unsigned nint_, next_;
  // number of propagators;
  unsigned nprop_;

  // kinematics invariants in this family
  // ext_vars[i] * ext_vars[j] = invs[(2*next-i-1)*i/2+j]
  RatMatrix invs_;

  // props = A . sps + B, A matrix and B column vector
  // sps = A^(-1) . props - A^(-1) . B
  // A(n*n): represent propagators by scalar products
  RatMatrix props_to_sps_;
  // B(n*1): a column vector constant terms
  RatMatrix props_constants_;
  // A^(-1)(n*n) represent scalar products by propagators
  RatMatrix sps_to_props_;
  // A^(-1).B(n,1):
  RatMatrix sps_constants_;
};

typedef unique_ptr<Family> FamilyPtr;

class Yaamf {
public:
  explicit Yaamf(const string &filename);

  ~Yaamf() {}

  // execute jobs
  void run();

private:
  // parse config file (config.yaml)
  void parse_config_();
  // parse target file
  void parse_target_(const string &filename);

private:
  // the initial integral family
  FamilyPtr family_;

  // the target integtals to be computed
  vector<IntegralPtr> targets_;
};

#endif // YAAMF_H_