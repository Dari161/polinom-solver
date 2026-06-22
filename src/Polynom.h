#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>

namespace Solver{
	class Polynom {
	private:
		const std::vector<double> coefs; // coefficients are stored in order, so the first double is the coefficient of the highest degree element, and the last coefficient is the constant (zeroth degree)
	public:
		Polynom(const std::vector<double> coefs) : coefs(coefs) {}
		bool operator== (const Polynom& other) const;
		double operator() (const double x) const;
		const Polynom derivate() const;
		const Polynom divide(const double x0) const;
	};
}

#endif // POLYNOM_H
