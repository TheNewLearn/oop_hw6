#include <gtest/gtest.h>
#include "../src/term.h"
#include<string>
#include "../src/polynomial.h"


class PolynomialTest: public::testing::Test{
  protected:
  const double DELTA = 0.001;
    
};

TEST_F(PolynomialTest,testconstructor_sorted){
    std::vector<Term> terms2 = {Term(-5, 2), Term(4, 2), Term(2, 1)};
    std::vector<Term> terms = {Term(-3, 2), Term(3, 0), Term(6, 3)};
    Polynomial p1(terms,3);
    
    ASSERT_NEAR(6,p1.term(3).coefficient(),DELTA);
    ASSERT_THROW(Polynomial p(terms2,2),std::string);
    ASSERT_EQ(0,p1.term(1).coefficient());
}

TEST_F(PolynomialTest, test_term){
    std::vector<Term> terms = {Term(-3, 2), Term(3, 0), Term(6, 3)};
    Polynomial p1(terms,3);
    ASSERT_EQ(Term(6,3),p1.term(3));
    ASSERT_EQ(Term(0,1),p1.term(1));
}

TEST_F(PolynomialTest, test_add){
    std::vector<Term> terms = {Term(-3, 2), Term(3, 0), Term(6, 3)};
    std::vector<Term> terms2 = {Term(-5, 2), Term(5, 4), Term(2, 1)};
    Polynomial p1(terms,3);
    Polynomial p2(terms2,4);
    Polynomial p3 = p1 + p2;
    ASSERT_EQ(Term(5,4),p3.term(4));
    ASSERT_EQ(Term(6,3),p3.term(3));
    ASSERT_EQ(Term(-8,2),p3.term(2));
    ASSERT_EQ(Term(2,1),p3.term(1));
    ASSERT_EQ(Term(3,0),p3.term(0));
}

TEST_F(PolynomialTest, test_multiply_term){
    std::vector<Term> terms = {Term(-3, 2), Term(3, 0), Term(6, 3)};
    Term t1(2,1);
    Polynomial p1(terms,3);
    Polynomial p3 = p1 * t1;
    ASSERT_EQ(Term(12,4),p3.term(4));
    ASSERT_EQ(Term(-6,3),p3.term(3));
    ASSERT_EQ(Term(0,2),p3.term(2));
    ASSERT_EQ(Term(6,1),p3.term(1));
    ASSERT_EQ(Term(0,0),p3.term(0));
}

TEST_F(PolynomialTest, test_multiply){
    std::vector<Term> terms = {Term(-3, 2), Term(3, 0), Term(6, 3)};
    std::vector<Term> terms2 = {Term(-5, 2), Term(5, 4), Term(2, 1)};
    Polynomial p1(terms,3);
    Polynomial p2(terms2,4);
    Polynomial p3 = p1 * p2;
    ASSERT_EQ(Term(30,7),p3.term(7));
    ASSERT_EQ(Term(-15,6),p3.term(6));
    ASSERT_EQ(Term(-30,5),p3.term(5));
    ASSERT_EQ(Term(42,4),p3.term(4));
    ASSERT_EQ(Term(-6,3),p3.term(3));
    ASSERT_EQ(Term(-15,2),p3.term(2));
    ASSERT_EQ(Term(6,1),p3.term(1));
    ASSERT_EQ(Term(0,0),p3.term(0));
}
