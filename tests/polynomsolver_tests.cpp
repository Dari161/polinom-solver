#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Polynom.h"
#include "PolynomSolver.h"
#include <cmath>
#include <vector>
#include <stdexcept>
#include "Constants.h"

namespace PolynomSolverTests {
    
    using Solver::Polynom;
    using Solver::PolynomSolver;
    using Solver::EPSILON;

    bool containsRoot(const std::vector<double>& roots, double expected) {
        for (double r : roots) {
            if (std::abs(r - expected) < EPSILON) return true;
        }
        return false;
    }

    TEST(PolynomSolverTest, LinearEquation) {
        // 2x - 4 = 0 => x = 2
        Polynom p({ 2.0, -4.0 });
        PolynomSolver solver(p);
        auto roots = solver.findSolutions();

        ASSERT_EQ(roots.size(), 1);
        EXPECT_TRUE(containsRoot(roots, 2.0));
    }

    TEST(PolynomSolverTest, QuadraticEquation) {
        // x^2 - 4 = 0 => x = 2, x = -2
        Polynom p({ 1.0, 0.0, -4.0 });
        PolynomSolver solver(p);
        auto roots = solver.findSolutions();

        ASSERT_EQ(roots.size(), 2);
        EXPECT_TRUE(containsRoot(roots, 2.0));
        EXPECT_TRUE(containsRoot(roots, -2.0));
    }

    TEST(PolynomSolverTest, CubicEquation) {
        // (x-1)(x-2)(x-3) = x^3 - 6x^2 + 11x - 6
        Polynom p({ 1.0, -6.0, 11.0, -6.0 });
        PolynomSolver solver(p);
        auto roots = solver.findSolutions();

        ASSERT_EQ(roots.size(), 3);
        EXPECT_TRUE(containsRoot(roots, 1.0));
        EXPECT_TRUE(containsRoot(roots, 2.0));
        EXPECT_TRUE(containsRoot(roots, 3.0));
    }

    TEST(PolynomSolverTest, NoRealRoots) {
        // x^2 + 1 = 0 => No real roots
        Polynom p({ 1.0, 0.0, 1.0 });
        PolynomSolver solver(p);
        auto roots = solver.findSolutions();

        EXPECT_TRUE(roots.empty());
    }

    TEST(PolynomSolverTest, MultipleRoot) {
        // (x-2)^2 = x^2 - 4x + 4 => x = 2
        Polynom p({ 1.0, -4.0, 4.0 });
        PolynomSolver solver(p);
        auto roots = solver.findSolutions();

        // The Bolzano/Rolle logic might pick up the single point of contact
        ASSERT_GE(roots.size(), 1);
        EXPECT_TRUE(containsRoot(roots, 2.0));
    }

    TEST(PolynomSolverTest, LeadingZerosHandling) {
        // 0*x^2 + 2x - 4 = 0 => x = 2
        Polynom p({ 0.0, 2.0, -4.0 });
        PolynomSolver solver(p);
        auto roots = solver.findSolutions();

        ASSERT_EQ(roots.size(), 1);
        EXPECT_TRUE(containsRoot(roots, 2.0));
    }
}
