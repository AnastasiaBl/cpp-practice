# Elliptic Curve Point Arithmetic (ECC)

Educational C++ implementation of elliptic curve arithmetic over a finite field. The program checks curve parameters, enumerates valid points, displays a coordinate grid and demonstrates point addition and scalar multiplication.

## Overview

The project demonstrates the mathematical principles behind elliptic curves defined over a finite field.

The implementation uses the short Weierstrass equation:

\[
y^2 \equiv x^3 + ax + b \pmod p
\]

where:
- `a` and `b` are curve coefficients;
- `p` is a prime modulus;
- `x` and `y` are point coordinates in the finite field.

For the curve to be nonsingular, its discriminant must satisfy:

\[
4a^3 + 27b^2 \not\equiv 0 \pmod p
\]

## Features

- Manual or automatic selection of curve coefficients.
- Manual or automatic generation of the prime modulus.
- Verification of the curve's nonsingularity condition.
- Enumeration of points satisfying the elliptic curve equation.
- Display of a coordinate grid showing the left and right sides of the equation.
- Assignment of labels to enumerated points.
- Interactive selection of points for addition.
- Demonstration of point doubling.
- Scalar multiplication through repeated point addition.
- Calculation of modular multiplicative inverses using a search algorithm.

## Mathematical Operations

### 1. Point enumeration

The program checks candidate coordinates in the range from `0` to `p - 1` and compares:

\[
L = y^2 \bmod p
\]

\[
R = (x^3 + ax + b) \bmod p
\]

A coordinate pair is added to the point set when:

\[
L = R
\]

The point at infinity is represented separately as `O`.

### 2. Point addition

For two distinct points with different x-coordinates, the implementation uses the slope:

\[
\lambda = (y_1-y_2)(x_1-x_2)^{-1} \pmod p
\]

The resulting coordinates are:

\[
x_3 = \lambda^2-x_1-x_2 \pmod p
\]

\[
y_3 = \lambda(x_1-x_3)-y_1 \pmod p
\]

### 3. Point doubling

For a point added to itself, the tangent slope is:

\[
\lambda = (3x_1^2+a)(2y_1)^{-1} \pmod p
\]

The resulting coordinates are:

\[
x_3 = \lambda^2-2x_1 \pmod p
\]

\[
y_3 = \lambda(x_1-x_3)-y_1 \pmod p
\]

### 4. Scalar multiplication

Scalar multiplication is demonstrated through repeated point addition:

\[
2P=P+P
\]

\[
3P=2P+P
\]

The program calculates the result for a user-selected positive integer coefficient.

## Project Structure

```text
cpp-elliptic-curve-arithmetic/
├── README.md
└── src/
    └── cal_elliptic_curve_point.cpp
```

## Implementation Details

The implementation is contained in a single C++ source file.

| Component | Responsibility |
|---|---|
| `input_int()` | Reads integers and performs basic input validation |
| `input_ra()` | Validates a selection from a numeric range |
| `m()` | Calculates an integer power by repeated multiplication |
| `pr()` | Checks whether a number is prime |
| `input_P()` | Selects and validates the prime modulus |
| `coordinate_plane()` | Enumerates curve points and displays the coordinate grid |
| `input_d()` | Searches for a modular multiplicative inverse |
| `addition()` | Calculates the sum of two selected points |
| `multiplication()` | Demonstrates scalar multiplication |
| `main()` | Controls parameter selection and the interactive menu |

## Limitations

This project is an educational demonstration, not a production-ready ECC implementation.

The current source code has several mathematical and implementation limitations:

- The modulus validation does not explicitly require `p > 3`, although the implemented short Weierstrass formulas assume a field of characteristic greater than 3.
- The coefficients `a` and `b` are not consistently normalized modulo `p`.
- Integer arithmetic uses `int`, which can overflow during exponentiation, discriminant calculation and coordinate operations.
- The point addition function does not correctly handle every case where two points have the same x-coordinate. In particular, it does not distinguish point doubling from addition of inverse points.
- The scalar multiplication function starts by doubling the point, so it does not correctly handle a multiplier equal to `1`.
- Intermediate scalar multiplication steps do not consistently handle all special cases of elliptic curve point addition.
- The program reports a missing result in the enumerated point set as the point at infinity. A missing point may instead indicate an arithmetic or implementation error.
- The point at infinity is displayed but cannot be selected as an operand in the interactive menu.
- The global point collection is not cleared when new curve parameters are selected.
- Point labels use the `char` type, so the labeling mechanism is limited.
- Modular inverses are found by brute-force search rather than the extended Euclidean algorithm.
- Random parameter generation uses `rand()`, which is not cryptographically secure.

The assignment operations `A + B`, `F + C`, `D + D`, `A + A` and `3E` are listed in the source comments, but are not automatically executed by the program. They must be selected manually through the interactive menu, and the required point labels depend on the generated curve.

## Security Notice

The project demonstrates elliptic curve mathematics only. It does not implement a complete ECC cryptographic protocol and must not be used to protect real data or generate production cryptographic keys.

A practical ECC implementation requires, among other things, validated domain parameters, secure key generation, correct point arithmetic, standardized protocols and cryptographically secure libraries.

## Build

The project can be compiled using a C++ compiler that supports the standard library.

```bash
g++ -std=c++17 src/cal_elliptic_curve_point.cpp -o ecc
```

Run on Linux:

```bash
./ecc
```

Run on Windows:

```bash
ecc.exe
```

## Technologies

- C++
- Object-oriented and procedural programming concepts
- Number theory
- Finite fields
- Modular arithmetic
- Elliptic curve mathematics

## Learning Objectives

- Understand the short Weierstrass equation over a finite field.
- Explore the nonsingularity condition for elliptic curves.
- Enumerate points over a finite field.
- Understand elliptic curve point addition and doubling.
- Explore scalar multiplication through repeated point addition.
- Practice modular arithmetic and modular multiplicative inverses.

## Author

**Anastasia Blokhina**

Educational project developed as part of programming and information security studies.
