#include "Polynom.h"
#include <vector>
#include <string>
#include "Constants.h"
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
		for (std::size_t i = 0; i < coefs.size(); ++i) {
			ret *= x;
			ret += coefs[i];
		}
		return ret;
	}

	const Polynom Polynom::derivate() const {
		std::vector<double> ret(coefs.size() - 1);
		for (std::size_t i = 0; i < coefs.size() - 1; ++i) {
			ret[i] = coefs[i] * (coefs.size() - 1 - i);
		}
		return Polynom(ret);
	}

	const Polynom Polynom::divide(const double x0) const {
		// divides the polynom by (x - x0) using Horner's method, without calculating the remainder
		std::vector<double> ret(coefs.size() - 1);
		double tmp = 0;
		for (std::size_t i = 0; i < coefs.size() - 1; ++i) {
			tmp = tmp * x0 + coefs[i];
			ret[i] = tmp;
		}
		return Polynom(ret);
	}

	// helper
	std::string formatDouble(const double val) {
		std::string s = std::to_string(val);
		s.erase(s.find_last_not_of('0') + 1, std::string::npos);
		if (s.back() == '.') s.pop_back();
		return s;
	}

	std::string Polynom::toString() const {
		std::string res = "";
		bool empty = true;

		for (size_t i = 0; i < coefs.size(); ++i) {
			if (std::abs(coefs[i]) < EPSILON) continue;

			res += formatDouble(coefs[i]);

			size_t p = coefs.size() - 1 - i;
			if (p > 0) {
				res += "*x";
				if (p > 1) res += "^" + std::to_string(p);
			}
			res += " ";
			empty = false;
		}

		return empty ? "0" : res;
	}
}
