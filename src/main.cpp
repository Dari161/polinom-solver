#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include "Polynom.h"
#include "PolynomSolver.h"

using namespace std;
using namespace Solver;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <c_n> <c_n-1> ... <c_0>\n";
        cerr << "Example: " << argv[0] << " 3 0 -4 2\n";
        return 1;
    }

    vector<double> coefs;
    coefs.reserve(static_cast<size_t>(argc - 1));

    try {
        for (int i = 1; i < argc; ++i) {
            coefs.push_back(stod(argv[i]));
        }
    }
    catch (const exception& e) {
        cerr << "Error: Invalid numeric argument provided.\n";
        return 1;
    }

    if (coefs.empty()) {
        cerr << "Error: No polynomial coefficients provided.\n";
        return 1;
    }

    try {
        Polynom p(coefs);

        cout << "0 = " << p.toString() << "\n";

        // Check if polynomial is identically zero
        bool is_zero = true;
        for (double c : coefs) if (std::abs(c) > 1e-9) is_zero = false;

        if (is_zero) {
            cout << "Infinitely many solutions (the polynomial is identically zero).\n";
        }
        else {
            PolynomSolver solver(p);
            vector<double> roots = solver.findSolutions();
            if (roots.empty()) {
                cout << "No real roots found.\n";
            }
            else {
                cout << "Roots found:\n";
                for (double root : roots) {
                    cout << "x = " << root << "\n";
                }
            }
        }
    }
    catch (const exception& e) {
        cerr << "\n[Runtime error]: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
