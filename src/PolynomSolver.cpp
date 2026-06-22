#include "PolynomSolver.h"
#include <vector>
#include <algorithm>

namespace Solver {
    using Polynom = std::vector<double>;

    // coefficients are reversed, for example a+bx+cx^2 = 0
    double PolynomSolver::calcVal(const Polynom& coefs, const double x) {
        double ret = 0;
        for (int i = 0; i < coefs.size(); ++i) {
            ret += coefs[i] * pow(x, i);
        }
        return ret;
    }

    // example (a+bx+cx^2+dx^3)' = b+2cx+3dx^2
    Polynom PolynomSolver::derivate(const Polynom& coefs) {
        Polynom ret;
        for (int i = 1; i < coefs.size(); ++i) {
            ret.push_back(coefs[i] * i);
        }
        return ret;
    }

    void PolynomSolver::getDerivatives() {
        der1 = derivate(coefs); // first derivative
        der2 = derivate(der1);  // second derivative
    }


    // return found and value
    std::pair<bool, double> PolynomSolver::approxSolution(const double A, const double B) const { // find solution on the interval if [A; B] is monotonous; the solution can be outside [A; B]

        double x = (A + B) / 2; // TODO: IS this good?

        // TODO: ez lehet nem jó
        for (int i = 0; i < maxIterations; ++i) {
            if (abs(calcVal(coefs, x)) < tolerance) {
                return { true, x };
            }

            x -= (calcVal(coefs, x) * calcVal(der1, x)) /
                 (pow(calcVal(der1, x), 2) - 0.5 * calcVal(coefs, x) * calcVal(der2, x));
        }

        return { false, x }; // x is no solution here
    }

    void PolynomSolver::divideBy(const double x) {
        // this uses Horner's method
        //TODO: divide only coefs and than in the caller function of this, call getDerivatives
    }
}

// TODO: write tests
// maybe it wont find all solutions, like it wont converge, but then we would pick a random new x, and see if it converges
