# Polynomial Solver

An analytical and numerical polynomial root-finding library implemented in modern C++. This solver combines algebraic bounds, calculus theorems, and higher-order iterative methods to guarantee that all discrete real roots are found without manual tuning parameters (such as minimum, maximum bounds, or step sizes).

---

## Technical Overview & Core Mathematics

The library utilizes a layered mathematical strategy to isolate and approximate roots with high precision and stability:

### 1. Root Bounding: Cauchy's Bound Theorem

Before searching for roots, the solver calculates a strict interval $[-R, R]$ that is guaranteed to contain all real roots of the polynomial. This eliminates the need for manual range guessing.

* **Theorem:** For a polynomial $c_n x^n + c_{n-1} x^{n-1} + \dots + c_0 = 0$, all real roots lie within the bound:

$$R = 1 + \frac{\max(|c_0|, |c_1|, \dots, |c_{n-1}|)}{|c_n|}$$


* Reference: [Cauchy's Bound Theorem on Wikipedia](https://www.google.com/search?q=https://en.wikipedia.org/wiki/Geometrical_properties_of_polynomial_roots%23Cauchy%27s_bound)

### 2. Isolation: Rolle's Theorem

To find all roots without missing any, the solver recursively finds the roots of the polynomial's first derivative. These represent the critical points (extrema).

* **Theorem:** Between any two consecutive critical points, the polynomial is strictly monotonic. This allows us to divide the global Cauchy interval into smaller, structurally guaranteed segments.
* Reference: [Rolle's Theorem on Wikipedia](https://en.wikipedia.org/wiki/Rolle%27s_theorem)

### 3. Verification: Bolzano's Theorem (IVT)

The solver evaluates the boundaries of each monotonic interval. If the polynomial changes signs between two critical points, a single unique root is guaranteed to exist within that segment.

* **Theorem:** If a continuous function satisfies $f(a) \cdot f(b) < 0$, then there exists at least one $c \in (a, b)$ such that $f(c) = 0$.
* Reference: [Bolzano's Theorem on Wikipedia](https://www.google.com/search?q=https://en.wikipedia.org/wiki/Intermediate_value_theorem%23Bolzano%27s_theorem)

### 4. Approximation: Halley's Method

Once a root is isolated within a guaranteed interval, Halley's method (a third-order iterative root-finding algorithm) is deployed from the midpoint of the interval to rapidly converge to the exact root.

* **Formula:** 
$$x_{n+1} = x_n - \frac{2 f(x_n) f'(x_n)}{2 [f'(x_n)]^2 - f(x_n) f''(x_n)}$$


* Reference: [Halley's Method on Wikipedia](https://en.wikipedia.org/wiki/Halley%27s_method)

### 5. Evaluation & Deflation: Horner's Method

The polynomial and its derivatives are evaluated using synthetic division, which reduces the computational complexity of evaluating an $n$-degree polynomial to $O(n)$ time complexity while maximizing numerical stability.

* Reference: [Horner's Method on Wikipedia](https://en.wikipedia.org/wiki/Horner%27s_method)

---

## Safety Features

* **Infinite Loop Prevention:** The solver automatically strips leading zero coefficients. This ensures that the polynomial degree strictly decreases during differentiation, preventing infinite recursion.
* **Numerical Drift Safeguard:** If numerical instability causes Halley's method to jump outside the mathematically verified interval boundaries, the solver discards the unstable step to prevent false positives.

---

## Building

The project uses CMake as its build system. To build the executable and the test suite, run the following commands:

```sh
mkdir build
cd build
cmake ..
cmake --build .

```

## Usage

You can run the solver from the command line. It accepts polynomial coefficients as arguments, ordered from the highest degree coefficient to the constant term.

```sh
./polynom_solver <c_n> <c_n-1> ... <c_0>

```

**Examples:**

Run the solver for $2x^2 - 8 = 0$:

```sh
./polynom_solver 2 0 -8

```

Run the solver for $x^3 - 6x^2 + 11x - 6 = 0$:

```sh
./polynom_solver 1 -6 11 -6

```

**C++ Integration Example:**

```cpp
#include "Polynom.h"
#include "PolynomSolver.h"
#include <iostream>

int main() {
    // Represents: x^2 - 4 = 0
    Solver::Polynom p({1.0, 0.0, -4.0}); 
    Solver::PolynomSolver solver(p);

    std::vector<double> roots = solver.findSolutions();

    for (double root : roots) {
        std::cout << "Found root: " << root << std::endl;
    }
    return 0;
}

```

## Testing

The project includes a comprehensive test suite covering the `Polynom` and `PolynomSolver` logic. To run the tests, execute `ctest` from your build directory:

```sh
ctest --output-on-failure

```
