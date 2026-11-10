# ElGamal Encryption Scheme

An educational C++ implementation of the ElGamal public-key encryption scheme, demonstrating key generation, modular arithmetic, message encryption and decryption.

## Project Overview

The project demonstrates the mathematical principles of the ElGamal public-key encryption scheme.

The application simulates the complete encryption workflow:
- generation or manual input of cryptographic parameters;
- generation of public and private keys;
- conversion of text into numerical representations;
- encryption of message elements;
- decryption of ciphertext pairs;
- conversion of decrypted values back into characters.

## Algorithm Overview

### 1. Key Generation

The algorithm uses the following parameters:

- `p` — a prime number.
- `g` — a generator of the multiplicative group modulo `p`.
- `x` — the private key.
- `y` — the public key.

The public key is calculated as:

```text
y = g^x mod p
```

The key components are:

- **Public key:** `(p, g, y)`
- **Private key:** `x`

### 2. Encryption

The plaintext message is represented as a sequence of numerical values `M`, where each value must satisfy:

```text
0 <= M < p
```

For each message element, the program selects a session key `k` and calculates:

```text
a = g^k mod p
b = y^k * M mod p
```

The ciphertext is represented as a pair:

```text
(a, b)
```

### 3. Decryption

Using the private key `x`, the original message element is recovered:

```text
M = b * (a^x)^(-1) mod p
```

The modular inverse is used to reverse the multiplication by the shared session value.

## Implemented Features

- Manual input and automatic generation of the prime modulus `p`.
- Manual input and automatic selection of the generator candidate `g`.
- Manual input and automatic generation of the private key `x`.
- Calculation of the public key `y`.
- Manual input and automatic generation of session keys `k`.
- Verification of the greatest common divisor between `k` and `p - 1`.
- Encryption of text using ASCII values or a predefined character set.
- Generation of ciphertext pairs `(a, b)`.
- Manual input of ciphertext pairs for decryption.
- Recovery of numerical message values.
- Conversion of decrypted values into characters.
- Console-based menu for encryption and decryption.

## Project Structure

```text
cpp-elgamal-encryption/
├── README.md
└── src/
    └── main.cpp
```

## Technologies

- C++
- Standard Template Library (STL)
- `iostream`
- `string`
- `cstdlib`
- `ctime`
- `limits`

## Build and Run

Compile using g++:

```bash
g++ -std=c++17 src/main.cpp -o elgamal
```

Run:

```bash
./elgamal
```

On Windows:

```bash
elgamal.exe
```

## Current Implementation Limitations

- The automatically generated prime modulus is limited to a small numerical range and is not suitable for real cryptographic use.
- The `rand()` function is not a cryptographically secure random number generator.
- The generator candidate `g` is not verified to be a primitive root modulo `p`.
- Intermediate arithmetic uses `int` and can overflow.
- Modular exponentiation is implemented using repeated multiplication instead of binary exponentiation.
- The modular inverse is found through brute-force search.
- The custom alphabet implementation has indexing and character encoding limitations.
- Invalid characters may leave message array elements uninitialized.
- The decryption input is not fully validated.
- The program displays the private key during encryption, which is unsuitable for secure key handling.

## Security Considerations

This implementation is intended for educational purposes only.

It demonstrates the mathematical principles of ElGamal encryption but does not provide production-grade security.

Real-world implementations require cryptographically secure random number generation, sufficiently large parameters, validated group elements, safe modular arithmetic and appropriate message encoding.

The implementation should not be used to protect real information.

## Learning Outcomes

- Understanding public-key cryptography.
- Studying the ElGamal encryption scheme.
- Practicing modular exponentiation and modular inverse calculations.
- Applying the Euclidean algorithm and GCD.
- Working with prime numbers and number theory.
- Converting text into numerical representations.
- Implementing encryption and decryption procedures in C++.
- Identifying security requirements and implementation limitations.
