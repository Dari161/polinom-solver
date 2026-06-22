#include "Polynom.h"
#include <vector>
#include "Constans.h"
#include <cmath>

namespace Solver {

	bool Polynom::operator== (const Polynom& other) const {
		if (coefs.size() != other.coefs.size()) return false;
		for (std::size_t i = 0; i < coefs.size(); ++i) {
			if (std::abs(coefs[i] - other.coefs[i]) >= EPSILON) {
				return false;
			}
		}
		return true;
	}

	bool Polynom::operator!=(const Polynom& other) const {
		return !(*this == other);
	}

	double Polynom::operator() (const double x) const {
		double ret = 0;
		for (int i = 0; i < coefs.size(); ++i) {
			ret *= x;
			ret += coefs[i];
		}
		return ret;
	}

	const Polynom Polynom::derivate() const {
		std::vector<double> ret(coefs.size() - 1);
		for (int i = 0; i < coefs.size() - 1; ++i) {
			ret[i] = coefs[i] * (coefs.size() - 1 - i);
		}
		return Polynom(ret);
	}

	const Polynom Polynom::divide(const double x0) const {
		// divides the polynom by (x - x0) using Horner's method, without calculating the remainder
		std::vector<double> ret(coefs.size() - 1);
		double tmp = 0;
		for (int i = 0; i < coefs.size() - 1; ++i) {
			tmp = tmp * x0 + coefs[i];
			ret[i] = tmp;
		}
		return Polynom(ret);
	}
}
