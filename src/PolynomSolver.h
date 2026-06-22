#ifndef POLYNOMSOLVER_H
#define POLYNOMSOLVER_H

#include "Polynom.h"
#include <vector>
#include <utility>

namespace Solver {
    class PolynomSolver {
    private:
        Polynom p;
        static constexpr std::size_t MAX_ITERATIONS = 100;

        // Halley's method
        std::pair<bool, double> approxSolution(double guess, const Polynom& current_p,
            const Polynom& d1, const Polynom& d2) const;

    public:
        explicit PolynomSolver(const Polynom& p) : p(p) {}

        // finds discrete roots (so if the polynom is 0, which has infinite many solutions, it will return zero solutions)
        std::vector<double> PolynomSolver::findSolutions() const;
    };
}

#endif // POLYNOMSOLVER_H
