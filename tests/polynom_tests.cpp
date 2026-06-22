#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Polynom.h"
#include <vector>
#include <stdexcept>
#include "Constants.h"

namespace PolynomTests {

    using Solver::Polynom;
    using Solver::EPSILON;

    // ==========================================
    // TOSTRING TESTS
    // ==========================================

    TEST(Polynom_ToString, PositiveCoefficients_ReturnsFormattedString) {
        Polynom p({ 1, 2, 3 });
        EXPECT_EQ(p.toString(), "1*x^2 2*x 3 ");
    }

    TEST(Polynom_ToString, ZeroCoefficients_ReturnsZeroString) {
        Polynom p({ 0.0, 0.0 });
        EXPECT_EQ(p.toString(), "0");
    }

    TEST(Polynom_ToString, MixedCoefficients_SkipsZerosAndFormatsNegatives) {
        Polynom p({ 1.5, 0.0, -4.25 });
        EXPECT_EQ(p.toString(), "1.5*x^2 -4.25 ");
    }

    TEST(Polynom_ToString, IntegerCoefficients_OmitsTrailingZeros) {
        Polynom p({ 10.0, 5.0 });
        EXPECT_EQ(p.toString(), "10*x 5 ");
    }

    TEST(Polynom_ToString, FloatCoefficients_KeepsSignificantDecimals) {
        Polynom p({ 0.1, 0.2 });
        EXPECT_EQ(p.toString(), "0.1*x 0.2 ");
    }

    // ==========================================
    // EQUALITY TESTS
    // ==========================================

    TEST(Polynom_Equality, IdenticalCoefficients_ReturnsTrue) {
        Polynom p1({ 1.0, 2.0, 3.0 });
        Polynom p2({ 1.0, 2.0, 3.0 });
        ASSERT_EQ(p1, p2);
    }

    TEST(Polynom_Equality, DifferentCoefficients_ReturnsFalse) {
        Polynom p1({ 1.0, 2.0, 3.0 });
        Polynom p3({ 1.0, 2.0, 4.0 });
        ASSERT_NE(p1, p3);
    }

    TEST(Polynom_Equality, DifferentDegrees_ReturnsFalse) {
        Polynom p1({ 1.0, 2.0, 3.0 });
        Polynom p4({ 1.0, 2.0 });
        ASSERT_NE(p1, p4);
    }

    TEST(Polynom_Equality, DifferenceWithinEpsilon_ReturnsTrue) {
        Polynom p1({ 1.0, 2.0, 3.0 });
        Polynom p5({ 1.0, 2.0, 3.0 + (EPSILON / 2.0) });
        ASSERT_EQ(p1, p5);
    }

    TEST(Polynom_Equality, DifferenceOutsideEpsilon_ReturnsFalse) {
        Polynom p1({ 1.0, 2.0, 3.0 });
        Polynom p6({ 1.0, 2.0, 3.0 + (EPSILON * 2.0) });
        ASSERT_NE(p1, p6);
    }

    TEST(Polynom_Inequality, DifferentPolynomials_ReturnsTrue) {
        Polynom p1({ 1.0, 2.0 });
        Polynom p2({ 1.0, 2.0 });
        Polynom p3({ 1.0, 3.0 });

        EXPECT_FALSE(p1 != p2);
        EXPECT_TRUE(p1 != p3);
    }

    // ==========================================
    // FUNCTION EVALUATION TESTS
    // ==========================================

    TEST(Polynom_Evaluate, QuadraticPolynomial_ReturnsCorrectValue) {
        // 4*x^2 + 2*x + 10
        Polynom p({ 4, 2, 10 });
        // 4*3^2 + 2*3 + 10 = 52
        ASSERT_NEAR(p(3), 52, EPSILON);
    }

    TEST(Polynom_Evaluate, ConstantPolynomial_ReturnsConstantValue) {
        // 7.3
        Polynom p({ 7.3 });
        // 7.3 = 7.3
        ASSERT_NEAR(p(122), 7.3, EPSILON);
    }

    TEST(Polynom_Evaluate, CubicPolynomial_ReturnsCorrectValue) {
        // 4.6*x^3 + 2.2*x^2 + 7.9*x + 10.4
        Polynom p({ 4.6, 2.2, 7.9, 10.4 });
        // 4.6*3.5^3 + 2.2*3.5^2 + 7.9*3.5 + 10.4 = 262.225
        ASSERT_NEAR(p(3.5), 262.225, EPSILON);
    }

    // ==========================================
    // DERIVATE TESTS
    // ==========================================

    TEST(Polynom_Derivate, QuadraticPolynomial_ReturnsLinearDerivative) {
        // p(x) = 4.8*x^2 + 2*x + 10
        Polynom p({ 4.8, 2, 10 });
        // p'(x) = 9.6*x + 2
        Polynom expected({ 9.6, 2 });
        ASSERT_EQ(p.derivate(), expected);
    }

    TEST(Polynom_Derivate, ConstantPolynomial_ReturnsEmptyPolynomial) {
        // p(x) = 5.72
        Polynom p({ 5.72 });
        // p'(x) = 0
        Polynom expected({ });
        ASSERT_EQ(p.derivate(), expected);
    }

    TEST(Polynom_Derivate, CubicPolynomial_ReturnsQuadraticDerivative) {
        // p(x) = 2.2*x^3 + 4.1*x^2 + 1.1*x + 100
        Polynom p({ 2.2, 4.1, 1.1, 100 });
        // p'(x) = 6.6*x^2 + 8.2*x + 1.1
        Polynom expected({ 6.6, 8.2, 1.1 });
        ASSERT_EQ(p.derivate(), expected);
    }

    // ==========================================
    // DIVIDE TESTS
    // ==========================================

    TEST(Polynom_Divide, QuadraticByRoot_ReturnsLinearQuotient) {
        // (1*x^2 - 3.5*x + 2.5) / (x - 2.5) = 1*x - 1
        Polynom p({ 1, -3.5, 2.5 });
        Polynom expected({ 1, -1 });
        ASSERT_EQ(p.divide(2.5), expected);
    }

    TEST(Polynom_Divide, ConstantByRoot_ReturnsEmptyPolynomial) {
        // 5.72 / (x - 2.2) = 0
        Polynom p({ 5.72 });
        Polynom expected({ });
        ASSERT_EQ(p.divide(2.2), expected);
    }

    TEST(Polynom_Divide, QuarticByRoot_ReturnsCubicQuotient) {
        // (2*x^4 + 5*x^3 + 4*x^2 - 3*x - 9) / (x - 2) = 2*x^3 + 9*x^2 + 22*x + 41 (and there is remainder too)
        Polynom p({ 2, 5, 4, -3, -9 });
        Polynom expected({ 2, 9, 22, 41 });
        ASSERT_EQ(p.divide(2), expected);
    }
}
