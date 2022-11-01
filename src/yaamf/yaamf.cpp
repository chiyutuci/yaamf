#include "yaamf/yaamf.h"

Family::Family(unsigned nint, unsigned next, unsigned nprop)
    : nint_(nint), next_(next), nprop_(nprop), props_to_sps_(nprop, nprop),
      sps_to_props_(nprop, nprop), props_constants_(nprop, 1),
      sps_constants_(nprop, 1), invs_(next * (next + 1) / 2, 1) {}

Family::~Family() {}

Yaamf::Yaamf(const string &filename) {
  parse_config_();
  parse_target_(filename);
}

void Yaamf::parse_config_() {
  // parse yaml file
  YAML::Node family_info = YAML::LoadFile("config.yaml");
  YAML::Node props = family_info["propagators"];
  YAML::Node invs = family_info["invariants"];

  unsigned nint = family_info["internals"].as<unsigned>();
  unsigned next = family_info["externals"].as<unsigned>();
  unsigned nprop = props.size();

  // init integral family
  family_.reset(new Family(nint, next, nprop));

  // fill the matrices A and B
  for (size_t i = 0; i < nprop; ++i) {
    for (size_t j = 0; j < nprop; ++j)
      family_->props_to_sps_.set(i, j, props[i][j].as<string>());
    family_->props_constants_.set(i, 0, props[i][nprop].as<string>());
  }
  // compute the matrix A^(-1)
  family_->sps_to_props_.inverse(family_->props_to_sps_);
  // compute the matrix -A^(-1).B
  family_->sps_constants_.as_mul(family_->sps_to_props_,
                                 family_->props_constants_);
  family_->sps_constants_.neg();

  // fill the vector of invariants
  for (size_t i = 0; i < invs.size(); ++i)
    family_->invs_.set(i, 0, invs[i].as<string>());
}

void Yaamf::parse_target_(const string &filename) {
  // parse yaml file
  YAML::Node targets = YAML::LoadFile(filename)["targets"];
  unsigned ntarget = targets.size();
  // check input
  if (ntarget == 0) {
    cout << "Exit: No target" << endl;
    exit(-1);
  }
  if (targets[0].size() != family_->nprop_) {
    cout << "Failed: Uncompatible target integrals size" << endl;
  }

  for (size_t i = 0; i < ntarget; ++i) {
    IntegralPtr integral(new Integral(targets[i].as<vector<int>>()));
    targets_.push_back(move(integral));
  }
}

void Yaamf::run() {}