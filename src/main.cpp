
#include <iostream>
#include <vector>
#include <algorithm>

/*
using namespace std;

double tolerance = 10e-6;

// coefficients are reversed, for example a+bx+cx^2 = 0
double f(vector<double> coefs, double x) {
    double ret = 0;
    for (int i = 0; i < coefs.size(); ++i) {
        ret += coefs[i] * pow(x, i);
    }
    return ret;
}

// example (a+bx+cx^2+dx^3)' = b+2cx+3dx^2
vector<double> derivate(vector<double> coefs) {
    vector<double> ret;
    for (int i = 1; i < coefs.size(); ++i) {
        ret.push_back(coefs[i] * i);
    }
    return ret;
}

vector<double> solveEq(vector<double> coefs) {
    if (coefs.size() == 2) {
        double a = coefs[1];
        double b = coefs[0];
        return { -b / a};
    } else if (coefs.size() == 3) { // quadratic
        double a = coefs[2];
        double b = coefs[1];
        double c = coefs[0];
        double h = pow(b, 2);
        double D = pow(b, 2) - 4 * a * c; // discriminant
        if (D < 0) {
            return {}; // no real solution
        } else if (D == 0) {
            return { -b / (2 * a) };
        } else if (D > 0) {
            double sqrtD = sqrt(D);
            return { (-b - sqrtD) / (2 * a), (-b + sqrtD) / (2 * a) };
        }
    }
}

// return found and value
pair<bool, double> approxSolution(vector<double> coefs, double A, double B) { // find solution on the interval if [A; B] is monotonous; the solution can be outside [A; B]
    int maxIterations = 5000;

    double x0 = (2 * A + B) / 3; // A-hoz közelebbi harmadolópont
    double x1 = (A + 2 * B) / 3; // B-hez közelebbi harmadolópont

    for (int i = 0; i < maxIterations; ++i) {
        
        double y0 = f(coefs, x0);
        double y1 = f(coefs, x1);

        if (abs(y1) < tolerance) {
            return { true, x1 };
        }

        // secant methos formula
        double x2 = x0 - y0 * (x1 - x0) / (y1 - y0);

        x0 = x1;
        x1 = x2;
    }

    return { false, x1 }; // x1 is no solution here
}

// only gets real solutions, no complexes
vector<double> solvePolinom(vector<double> coefs) {
    if (coefs.size() <= 3) { // base case
        return solveEq(coefs);
    }

    // get derivative to find infexion, minimum and maximum points
    vector<double> der = derivate(coefs);

    // find infexion, minimum and maximum points: they are there when the derivative is 0
    vector<double> points = solvePolinom(der); // recursive call

    vector<double> ret;

    // if a point is 0 than it is a solution 
    for (auto it = points.begin(); it != points.end(); ++it) {
        if (abs(f(coefs, *it)) < tolerance) {
            ret.push_back(*it);
            it = points.erase(it); // idk if its good
        }
    }

    // if the sign changes between 2 points, than there is a solution between them
    for (int i = 1; i < points.size(); ++i) {
        double A = points[i - 1];
        double B = points[i];

        if (f(coefs, A) * f(coefs, B) < 0) { // if f(A) * f(B) is negative, than f(A) and f(B) has different signs
            ret.push_back(approxSolution(coefs, A, B).second); // no need to check if solution exists, cuz we are sure that it does
        }
    }

    pair<bool, double> leftSolution = approxSolution(coefs, points[0] - 10, points[0]);
    pair<bool, double> rightSolution = approxSolution(coefs, points[points.size() - 1], points[points.size() - 1] + 10);

    if (leftSolution.first) {
        ret.push_back(leftSolution.second);
    }
    if (rightSolution.first) {
        ret.push_back(rightSolution.second);
    }

    sort(ret.begin(), ret.end());
    return ret;
}
*/

int main() {
    //vector<double> solutions = solvePolinom({-4, 7, -10, -8, 1, 1});
    //vector<double> solutions =  derivate({3, 4, 2, 5});
    //vector<double> solutions = solveEq({ -48, 24, 60 });

    /*vector<double> solutions = solvePolinom({8, 7, -10, -8, 1, 1});
    for (double s : solutions) {
        cout << s << endl;
    }*/

    std::cout << "Hello word";
}