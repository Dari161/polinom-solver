#ifndef POLYNOMSOLVER_H
#define POLYNOMSOLVER_H

namespace Solver {
    using Polynom = std::vector<double>;

    class PolynomSolver
    {
    private:
        Polynom coefs, der1, der2;

        double tolerance = 10e-6;

        int maxIterations = 50;

        // coefficients are reversed, for example a+bx+cx^2 = 0
        static double calcVal(const Polynom& coefs, const double x);

        // example (a+bx+cx^2+dx^3)' = b+2cx+3dx^2
        static Polynom derivate(const Polynom& coefs);

        void getDerivatives();

        // return found and value
        std::pair<bool, double> approxSolution(const double A, const double B) const;

        void divideBy(const double x);
    };
}

#endif // POLYNOMSOLVER_H
