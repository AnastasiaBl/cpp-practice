# RSA Encryption Scheme

An educational implementation of the RSA public-key cryptosystem in C++. The project demonstrates prime number validation, RSA parameter generation, public and private exponent calculation, and message encryption using modular arithmetic.

## Overview

RSA is an asymmetric cryptographic algorithm based on the mathematical properties of large prime numbers and modular exponentiation.

The implementation demonstrates the initial stages of the RSA workflow:

- Selection and generation of prime numbers `p` and `q`.
- Calculation of the modulus `n = p * q`.
- Calculation of Euler's totient function `φ(n)`.
- Selection of the public exponent `e`.
- Calculation of the private exponent `d`.
- Encryption of message values using modular exponentiation.

**Current implementation status:** key parameter generation and encryption are implemented. Decryption is not yet implemented.

## Implemented Features

### 1. Prime Number Validation

The `pr()` function checks whether an integer is prime by testing possible divisors up to its square root.

### 2. RSA Parameter Generation

The program supports manual input and automatic generation of prime numbers `p` and `q`.

It calculates:

- RSA modulus: `n = p * q`
- Euler's totient function: `φ(n) = (p - 1) * (q - 1)`

The program checks that the modulus is greater than the maximum encoded message value.

### 3. Public Exponent Selection

The `input_e()` function allows the user to enter or generate the public exponent `e`.

The exponent must be relatively prime to `φ(n)`.

### 4. Private Exponent Calculation

The `input_d()` function searches for a value satisfying:

`d * e ≡ 1 (mod φ(n))`

The current implementation uses a brute-force search.

### 5. Message Encoding

The program supports two input modes:

- ASCII character encoding.
- A predefined custom alphabet containing Latin and Cyrillic characters, digits, and punctuation.

### 6. Message Encryption

Each encoded message value is encrypted using:

`C = M^e mod n`

The resulting ciphertext values are displayed as an integer sequence.

## Technologies

- C++
- Standard Template Library (STL)
- Modular arithmetic
- RSA public-key cryptography
- Prime number validation
- Dynamic memory allocation

## Project Structure

```text
cpp-rsa-encryption/
├── README.md
└── src/
    └── main.cpp
```

## Limitations

This project is an educational implementation and is not suitable for protecting real data.

Current limitations:

- RSA decryption is not implemented.
- The implementation uses small prime numbers and is not cryptographically secure.
- Random values are generated using `rand()`, which is not suitable for cryptographic key generation.
- The program does not verify that `p` and `q` are different.
- The public exponent validation does not fully enforce the required range.
- The modular exponentiation is implemented using repeated multiplication rather than an efficient binary algorithm.
- Integer multiplication may overflow for larger parameters.
- The private exponent `d` is displayed in the program output and should not be exposed.
- The custom alphabet implementation processes `std::string` character by character and does not correctly handle multibyte UTF-8 Cyrillic characters.
- Input characters not found in the custom alphabet are not handled safely.

## Future Improvements

- Implement RSA decryption.
- Add binary modular exponentiation.
- Calculate the modular inverse using the extended Euclidean algorithm.
- Validate all RSA parameters and enforce `p != q`.
- Use safer integer types and overflow-resistant modular multiplication.
- Replace `rand()` with a cryptographically secure random number generator.
- Correctly support UTF-8 text encoding.
- Remove private key information from program output.
- Replace raw dynamic arrays with `std::vector`.

## Disclaimer

This project is intended for educational purposes only. It demonstrates basic RSA concepts and does not provide production-grade cryptographic security.
