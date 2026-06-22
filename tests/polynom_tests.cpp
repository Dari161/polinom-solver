#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Polynom.h"
#include <vector>
#include <stdexcept>
#include "test_constants.h"

namespace PolynomsolverTests {

    using Solver::Polynom;
    using ::testing::Pointwise;
    using ::testing::DoubleNear;

    // ==========================================
    // FUNCTION EVALUATION TESTS
    // ==========================================

    TEST(PolynomTest, FunctionEvaluation) {
        // 4*x^2 + 2*x + 10
        Polynom p({ 4, 2, 10 });
        // 4*3^2 + 2*3 + 10 = 52
        ASSERT_NEAR(p(3), 52, EPSILON);
    }

    TEST(PolynomTest, FunctionEvaluation0thDegree) {
        // 7.3
        Polynom p({ 7.3 });
        // 7.3 = 7.3
        ASSERT_NEAR(p(122), 7.3, EPSILON);
    }

    TEST(PolynomTest, FunctionEvaluationLong) {
        // 4.6*x^3 + 2.2*x^2 + 7.9*x + 10.4
        Polynom p({ 4.6, 2.2, 7.9, 10.4 });
        // 4.6*3.5^3 + 2.2*3.5^2 + 7.9*3.5 + 10.4 = 262.225
        ASSERT_NEAR(p(3.5), 262.225, EPSILON);
    }

    // ==========================================
    // DERIVATE TESTS
    // ==========================================

    TEST(PolynomTest, Derivate) {
        // p(x) = 4.8*x^2 + 2*x + 10
        Polynom p({ 4.8, 2, 10 });
        // p'(x) = 9.6*x + 2
        Polynom expected({ 9.6, 2 });
        ASSERT_EQ(p.derivate(), expected);
    }

    TEST(PolynomTest, Derivate0thDegree) {
        // p(x) = 5.72
        Polynom p({ 5.72 });
        // p'(x) = 0
        Polynom expected({ });
        ASSERT_EQ(p.derivate(), expected);
    }

    TEST(PolynomTest, DerivateLong) {
        // p(x) = 2.2*x^3 + 4.1*x^2 + 1.1*x + 100
        Polynom p({ 2.2, 4.1, 1.1, 100 });
        // p'(x) = 6.6*x^2 + 8.2*x + 1.1
        Polynom expected({ 6.6, 8.2, 1.1 });
        ASSERT_EQ(p.derivate(), expected);
    }

    // ==========================================
    // DIVIDE TESTS
    // ==========================================

    TEST(PolynomTest, Divide) {
        // (1*x^2 - 3.5*x + 2.5) / (x - 2.5) = 1*x - 1
        Polynom p({1, -3.5, 2.5});
        Polynom expected({ 1, -1 });
        ASSERT_EQ(p.divide(2.5), expected);
    }

    TEST(PolynomTest, Divide0thDegree) {
        // 5.72 / (x - 2.2) = 0
        Polynom p({ 5.72 });
        Polynom expected({ });
        ASSERT_EQ(p.divide(2.2), expected);
    }

    TEST(PolynomTest, DivideLong) {
        // (2*x^4 + 5*x^3 + 4*x^2 - 3*x - 9) / (x - 2) = 2*x^3 + 9*x^2 + 22*x + 41 (and there is remainder too)
        Polynom p({ 2, 5, 4, -3, -9 });
        Polynom expected({ 2, 9, 22, 41 });
        ASSERT_EQ(p.divide(2), expected);
    }
}
