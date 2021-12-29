#include <gtest/gtest.h>
#include "../src/term.h"

class TermTest : public ::testing::Test {
protected:
  const double DELTA = 0.001;
};

TEST_F(TermTest, DefaultConstructor){
  Term t;
  ASSERT_NEAR(0, t.coefficient(), DELTA);
  ASSERT_EQ(0, t.exponent());
}

TEST_F(TermTest, ParameterizedConstructor) {
  Term t(3.4, 2);
  ASSERT_NEAR(3.4, t.coefficient(), DELTA);
  ASSERT_EQ(2, t.exponent());

  Term param_term(3.9, 10);
  ASSERT_NEAR(3.9, param_term.coefficient(), DELTA);
  ASSERT_EQ(10, param_term.exponent());
}

TEST_F(TermTest, OperatorEqualTo) {
  Term t1(3.9, 10);
  Term t2(3.9, 10);
  Term t3(4.2, 3);
  ASSERT_TRUE(t1 == t2);
  ASSERT_FALSE(t1 == t3);
}

TEST_F(TermTest, OperatorMultiple) {
  Term multi_term = Term(3.9, 10) * Term(4.1, 5);
  ASSERT_NEAR(15.99, multi_term.coefficient(), DELTA);
  ASSERT_EQ(15, multi_term.exponent());

  Term zero_term = Term() * Term(3.9, 10);
  ASSERT_NEAR(0, zero_term.coefficient(), DELTA);
  ASSERT_EQ(10, zero_term.exponent());
}

TEST_F(TermTest, OperatorAddition) {
  Term add_term1 = Term(3.9, 5) + Term(4.1, 5);
  ASSERT_NEAR(8, add_term1.coefficient(), DELTA);
  ASSERT_EQ(5, add_term1.exponent());

  Term add_term2 = Term() + Term(3.9, 0);
  ASSERT_NEAR(3.9, add_term2.coefficient(), DELTA);
  ASSERT_EQ(0, add_term2.exponent());
}

TEST_F(TermTest, OperatorAdditionException) {
  ASSERT_THROW(Term(3.9, 2) + Term(4.1, 5), std::string);
}

TEST_F(TermTest, IsZero) {
  Term default_term;
  ASSERT_TRUE(default_term.isZero());

  Term normal_term(3.9, 10);
  ASSERT_FALSE(normal_term.isZero());
}
