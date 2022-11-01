#ifndef YAAMF_MATHTYPES_H_
#define YAAMF_MATHTYPES_H_

#include <flint/fmpq_mat.h>
#include <string>

using namespace std;

// rational number
class Rational {
public:
  // default constructor
  Rational() { fmpq_init(rat_); }
  // copy constructor
  Rational(const Rational &other) {
    fmpq_init(rat_);
    fmpq_set(rat_, other.rat_);
  }
  // copy assignment
  Rational &operator=(const Rational &other) {
    fmpq_set(rat_, other.rat_);
    return *this;
  }
  // move constructor
  Rational(Rational &&other) {
    fmpq_init(rat_);
    fmpq_swap(rat_, other.rat_);
  }
  // move assignment
  Rational &operator=(Rational &&other) {
    fmpq_swap(rat_, other.rat_);
    return *this;
  }

  // from a native flint raional number
  Rational(const fmpq_t other) {
    fmpq_init(rat_);
    fmpq_set(rat_, other);
  }
  Rational &operator=(const fmpq_t other) {
    fmpq_set(rat_, other);
    return *this;
  }

  // from an integer
  explicit Rational(int num) {
    fmpq_init(rat_);
    fmpq_set_si(rat_, num, 1);
  }
  Rational &operator=(int num) {
    fmpq_set_si(rat_, num, 1);
    return *this;
  }

  // from a string (used for input)
  explicit Rational(const string &str) {
    fmpq_init(rat_);
    fmpq_set_str(rat_, str.c_str(), 10);
    canomicalise_();
  }
  Rational &operator=(const string &str) {
    fmpq_set_str(rat_, str.c_str(), 10);
    canomicalise_();
    return *this;
  }

  // destructor
  ~Rational() { fmpq_clear(rat_); }

  // return ther underline flint rational number
  fmpq_t &rat() { return rat_; }
  const fmpq_t &rat() const { return rat_; }

  // print a rational number
  friend ostream &operator<<(ostream &os, const Rational &rat);

private:
  // reduce the num and den to lowest terms
  void canomicalise_() { fmpq_canonicalise(rat_); }

private:
  // the underline flint rational number
  fmpq_t rat_;
};

inline ostream &operator<<(ostream &os, const Rational &rat) {
  fmpq_print(rat.rat_);
  return os;
}

// rational matrix
class RatMatrix {
public:
  // init a row * col matrix with zero entries
  explicit RatMatrix(unsigned row, unsigned col) {
    fmpq_mat_init(mat_, row, col);
  }
  // copy constructor
  RatMatrix(const RatMatrix &other) { fmpq_mat_init_set(mat_, other.mat_); }
  // copy assignment, assuming the two matrices have the same dimensions
  RatMatrix &operator=(const RatMatrix &other) {
    fmpq_mat_set(mat_, other.mat_);
    return *this;
  }
  // move constructor
  RatMatrix(RatMatrix &&other) {
    fmpq_mat_init(mat_, 1, 1);
    fmpq_mat_swap(mat_, other.mat_);
  }
  // move assignment, the dimensions are allowed to be different
  RatMatrix &operator=(RatMatrix &&other) {
    fmpq_mat_swap(mat_, other.mat_);
    return *this;
  }

  // destructor
  ~RatMatrix() { fmpq_mat_clear(mat_); }

  // return the underline fline rational matrix
  fmpq_mat_t &mat() { return mat_; }
  const fmpq_mat_t &mat() const { return mat_; }

  // set an entry to a rational number
  void set(unsigned row, unsigned col, const Rational &rat) {
    fmpq_set(fmpq_mat_entry(mat_, row, col), rat.rat());
  }
  void set(unsigned row, unsigned col, const fmpq_t rat) {
    fmpq_set(fmpq_mat_entry(mat_, row, col), rat);
  }
  // set an entry to a string (used for input)
  void set(unsigned row, unsigned col, const string &str) {
    fmpq_set_str(fmpq_mat_entry(mat_, row, col), str.c_str(), 10);
  }

  // set this matrix to the negative of itself
  void neg() { fmpq_mat_neg(mat_, mat_); }

  // inverse this matrix
  void inverse() { fmpq_mat_inv(mat_, mat_); }
  // set this matrix to be the inverse of another matrix
  // assuming the two matrices have the same dimensions
  void inverse(const RatMatrix &other) { fmpq_mat_inv(mat_, other.mat_); }

  // set this matrix to be the multiple of matrices A and B
  // assuming the dimensions are compatible
  void as_mul(const RatMatrix &matA, const RatMatrix &matB) {
    fmpq_mat_mul(mat_, matA.mat_, matB.mat_);
  }

  // print a rational matrix
  friend ostream &operator<<(ostream &os, const RatMatrix &mat);

private:
  // the underline flint rational matrix
  fmpq_mat_t mat_;
};

inline ostream &operator<<(ostream &os, const RatMatrix &mat) {
  fmpq_mat_print(mat.mat_);
  return os;
}

#endif // YAAMF_MATHTYPES_H_