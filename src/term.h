#ifndef TERM_H
#define TERM_H
#include <string>
class Term {
public:
  Term() {
    _coef = 0;
    _exp = 0;
  }

  Term(double coef, int exp) {
    _coef = coef;
    _exp = exp;
  }

  double coefficient() const {
    return _coef;
  }

  int exponent() const {
    return _exp;
  }

  bool operator== (Term const & t) const {
    return (_coef == t.coefficient()) && (_exp == t.exponent());
  }

  Term operator* (Term const & t) const {
    return Term(_coef * t.coefficient(), _exp + t.exponent());
  }

  Term operator+ (Term const & t) const {
    if (_exp != t.exponent()) {
      throw std::string("Exponent not match");
    }
    return Term(_coef + t.coefficient(), _exp);
  }

  bool isZero() const {
    return _coef == 0;
  }

private:
  double _coef;
  int _exp;
};

#endif
