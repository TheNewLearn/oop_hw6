#include <gtest/gtest.h>
#include "../src/term.h"
#include "../src/polynomial.h"

TEST(polytest,poly){
std::vector<Term> terms = {Term(-3, 2), Term(3, 0), Term(6, 3)};
std::vector<Term> terms2 = {Term(-5, 2), Term(4, 0), Term(2, 1)};
std::vector<Term> terms3 = {Term(-6, 3), Term(4, 0), Term(2, 1)};
Polynomial p(terms,3);
Polynomial p2(terms3,3);
Term t1(2,3);
Polynomial p3 = p + p2;
ASSERT_EQ(12,p3._terms.at(0).exponent());


}