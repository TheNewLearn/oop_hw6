#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <vector>

#include "term.h"

class Polynomial {
public:
  Polynomial(std::vector<Term> terms, int degree) {
    for(int i=0 ; i< terms.size(); i++){
      if(std::count(terms.begin(),terms.end(),terms.at(i)) > 1){
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
    _degree = _terms.at(0).exponent();
    
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
    if(_terms.at(0).exponent() == q._terms.at(0).exponent()){
      for(int i=0; i< _terms.size();i++){
        int a = _terms.at(i).coefficient();
        int b = q._terms.at(i).coefficient();
        addpoly.push_back(Term(a+b,_terms.at(i).exponent()));
      }
      return Polynomial(addpoly,_terms.at(0).exponent());
    }
    else if(_terms.at(0).exponent() > q._terms.at(0).exponent()){
      for(int i=0; i< _terms.size();i++){
        int a = term(i).coefficient();
        int b = q.term(i).coefficient();
        addpoly.push_back(Term(a+b,term(i).exponent()));
      }
       return Polynomial(addpoly,_terms.at(0).exponent());
    }
    else if(_terms.at(0).exponent() < q._terms.at(0).exponent()){
      for(int i=0; i< q._terms.size();i++){
        int a = term(i).coefficient();
        int b = q.term(i).coefficient();
        addpoly.push_back(Term(a+b,q.term(i).exponent()));
      }
      return Polynomial(addpoly,q._terms.at(0).exponent());
    }
    
  }

  // multiply by a term
  Polynomial operator* (Term t) const {
    std::vector<Term> mulityp;
    int min = 0;
    for(int i=0; i< _terms.size();i++){
      int a = _terms.at(i).coefficient();
      int b = t.coefficient();
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
          int a = q._terms.at(i).coefficient();
          int b = _terms.at(j).coefficient();
          mulityp.push_back(Term(a*b,q._terms.at(i).exponent() + _terms.at(j).exponent() ));
        }
        else{
          int a = q._terms.at(i).coefficient();
          int b = _terms.at(j).coefficient();
          
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

public:
  std::vector<Term> _terms;
  int _degree;

};

#endif
