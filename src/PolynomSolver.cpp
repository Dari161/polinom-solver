#include "PolynomSolver.h"
#include "Constants.h"
#include <cmath>
#include <algorithm>

namespace Solver {

    // Halley's method
    std::pair<bool, double> PolynomSolver::approxSolution(double x, const Polynom& current_p,
        const Polynom& d1, const Polynom& d2) const {
        for (std::size_t i = 0; i < MAX_ITERATIONS; ++i) {
            const double px = current_p(x);
            const double d1x = d1(x);
            const double d2x = d2(x);

            // found a root
            if (std::abs(px) < EPSILON) return { true, x };

            double denominator = (d1x * d1x) - (0.5 * px * d2x);
            if (std::abs(denominator) < pow(EPSILON, 2)) return { false, x };

            x -= (px * d1x) / denominator;
        }
        return { false, x };
    }

    // finds discrete roots (so if the polynom is 0, which has infinite many solutions, it will return zero solutions)
    std::vector<double> PolynomSolver::findSolutions() const {
        std::vector<double> roots;

        auto coefs = p.getCoefs();

        // Safety protocol: Strip leading zeros to prevent division by zero in Cauchy's bound
        // and to guarantee strictly decreasing polynomial degrees to prevent infinite recursion.
        while (!coefs.empty() && std::abs(coefs.front()) < EPSILON) {
            coefs.erase(coefs.begin());
        }

        // Base cases: 0th or 1st degree polynomial
        if (coefs.size() <= 1) {
            // Constant polynomial: inherently lacks discrete roots or represents an identity (infinitely many roots).
            return roots;
        }

        if (coefs.size() == 2) {
            // Linear equation: ax + b = 0
            // Safe to divide, leading zeros are already stripped.
            const double root = -coefs[1] / coefs[0];
            roots.push_back(root);
            return roots;
        }

        // Cauchy's bound theorem: For a polynomial c_n*x^n + ... + c_0 = 0, 
        // all real roots are guaranteed to be in the interval [-R, R], 
        // where R = 1 + max(|c_0|, ..., |c_{n-1}|) / |c_n|.
        double max_coef = 0.0;
        for (std::size_t i = 1; i < coefs.size(); ++i) {
            if (std::abs(coefs[i]) > max_coef) {
                max_coef = std::abs(coefs[i]);
            }
        }
        const double cauchy_bound = 1.0 + (max_coef / std::abs(coefs.front()));

        const double min = -cauchy_bound;
        const double max = cauchy_bound;

        // Isolate roots using Rolle's theorem:
        // The roots of the first derivative represent the critical points (extrema) of the polynomial.
        // Between any two consecutive critical points, the polynomial is strictly monotonic.
        Polynom d1 = p.derivate();
        PolynomSolver deriv_solver(d1);
        const std::vector<double> critical_points = deriv_solver.findSolutions();

        Polynom d2 = d1.derivate();

        // Iterate through the strictly monotonic intervals defined by [min, cp_1, cp_2, ..., max]
        auto check_interval = [&](const double x1, const double x2) {
            const double y1 = p(x1);
            const double y2 = p(x2);

            // Handle roots exactly on the left boundary (captures extrema touching the x-axis)
            if (std::abs(y1) < EPSILON) {
                if (roots.empty() || std::abs(roots.back() - x1) > EPSILON) {
                    roots.push_back(x1);
                }
                return;
            }

            // Apply Bolzano's theorem on the guaranteed strictly monotonic interval
            // Bolzano's theorem: If a continuous function has values of opposite sign inside an interval, then it has a root in that interval.
            if (y1 * y2 < 0.0) {
                auto res = approxSolution((x1 + x2) / 2.0, p, d1, d2);
                if (res.first) {
                    // Guard against numerical instability causing Halley's method to jump outside valid bounds
                    if (res.second >= min && res.second <= max) {
                        if (roots.empty() || std::abs(roots.back() - res.second) > EPSILON) {
                            roots.push_back(res.second);
                        }
                    }
                }
            }
            };

        if (critical_points.empty()) {
            check_interval(min, max);
        }
        else {
            check_interval(min, critical_points.front());
            for (std::size_t i = 0; i < critical_points.size() - 1; ++i) {
                check_interval(critical_points[i], critical_points[i + 1]);
            }
            check_interval(critical_points.back(), max);
        }

        // Explicit check for the rightmost boundary to prevent edge-case omissions
        if (std::abs(p(max)) < EPSILON) {
            if (roots.empty() || std::abs(roots.back() - max) > EPSILON) {
                roots.push_back(max);
            }
        }

        std::sort(roots.begin(), roots.end());

        return roots;
    }
}
