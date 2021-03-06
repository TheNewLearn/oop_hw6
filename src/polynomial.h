#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <vector>

#include "term.h"

class Polynomial {
public:
  Polynomial(std::vector<Term> terms, int degree) {
    for(int i=0 ; i< terms.size(); i++){
      int count = 0;
      for(int j=0; j< terms.size(); j++){
        if(terms.at(i).exponent() == terms.at(j).exponent()){
          count += 1;
        }
      }
      if(count > 1){
        throw std::string("duplicate terms");
      }
    }
    _terms.assign(terms.begin(),terms.end());
    for(int i=0 ;i<=degree;i++){
      if(std::count(_terms.begin(),_terms.end(),term(i)) == 0){
        _terms.push_back(Term(0,i));
      }
    }

    std::stable_sort(_terms.begin(),_terms.end(),mycom);
    _degree = degree;
    
  }

  static bool mycom(Term t1, Term t2){
    return t1.exponent() > t2.exponent();
  }

  // get a term by exponent
  // If the term does not exist, return the term (0, exponent)
  Term term(int exponent) const {
    bool finded = false;
    for(int i=0; i< _terms.size(); i++){
      if(_terms.at(i).exponent() == exponent){
        return _terms.at(i);
        finded = true;
      }
    }
    if(finded == false){
      return Term(0,exponent);
    }
  }

  // get the degree
  int degree() const {
    return _degree;
  }

  // add two polynomials
  Polynomial operator+ (const Polynomial & q) const {
    std::vector<Term> addpoly;
    std::vector<Term> sorted;
    sorted.assign(q._terms.begin(),q._terms.end());
    std::stable_sort(sorted.begin(),sorted.end(),mycom);
    int min = 0;
    int a = _terms.at(0).exponent();
    int b = sorted.at(0).exponent();
    if(a==b){
      for(int i=0; i<= _terms.at(0).exponent();i++){
        double sum = term(i).coefficient() + q.term(i).coefficient();
        if(sum != 0){
          addpoly.push_back(Term(sum,term(i).exponent()));
          if(min < term(i).exponent()){
            min = term(i).exponent();
          }
        }
        
      }
      return Polynomial(addpoly,min);
    }else if(a > b){
      for(int i=0; i<= _terms.at(0).exponent();i++){
        double sum = term(i).coefficient() + q.term(i).coefficient();
        if(sum != 0){
          addpoly.push_back(Term(sum,term(i).exponent()));
          if(min < term(i).exponent()){
            min = term(i).exponent();
          }
        }
      }
      return Polynomial(addpoly,min);
    }
    else if(b > a){
      for(int i=0; i<= q._terms.at(0).exponent();i++){
        double sum = term(i).coefficient() + q.term(i).coefficient();
        if(sum != 0){
          addpoly.push_back(Term(sum,term(i).exponent()));
          if(min < term(i).exponent()){
            min = term(i).exponent();
          }
        }
      }
      return Polynomial(addpoly,min);
    }
    
  }

  // multiply by a term
  Polynomial operator* (Term t) const {
    std::vector<Term> mulityp;
    int min = 0;
    for(int i=0; i< _terms.size();i++){
      double a = _terms.at(i).coefficient();
      double b = t.coefficient();
      mulityp.push_back(Term(a*b, (int)(_terms.at(i).exponent() + t.exponent())));
      if(min < _terms.at(i).exponent() + t.exponent() ){
        min = _terms.at(i).exponent() + t.exponent();
      }
    }
    return Polynomial(mulityp,min);
  }

  // multiply by another Polynomial
  Polynomial operator* (const Polynomial & q) const {
    std::vector<Term> mulityp;
    int min=0;
    for(int i=0 ; i< q._terms.size();i++){
      for(int j=0 ; j< _terms.size();j++){
        if(i == 0){
          double a = q._terms.at(i).coefficient();
          double b = _terms.at(j).coefficient();
          mulityp.push_back(Term(a*b,q._terms.at(i).exponent() + _terms.at(j).exponent() ));
        }
        else{
          double a = q._terms.at(i).coefficient();
          double b = _terms.at(j).coefficient();
          
          int c = q._terms.at(i).exponent() + _terms.at(j).exponent();
          bool finded = false;
          for(int k=0; k< mulityp.size();k++){
            if(mulityp.at(k).exponent() == c){
              mulityp.at(k) = Term(mulityp.at(k).coefficient() + (a*b), c);
              finded = true;
            }
          }
          if(finded == false){
            mulityp.push_back(Term(a*b,c));
          }  
        }
        
        if(min < q._terms.at(i).exponent() + _terms.at(j).exponent()){
          min = q._terms.at(i).exponent() + _terms.at(j).exponent();
        }
        
      }
    }

    return Polynomial(mulityp,min);

  }

private:
  std::vector<Term> _terms;
  int _degree;

};

#endif
