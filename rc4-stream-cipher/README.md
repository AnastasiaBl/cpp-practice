# RC4 Stream Cipher and Binary Converter

An educational C++ project demonstrating stream cipher concepts, pseudo-random keystream generation, XOR operations and text conversion between binary and hexadecimal representations.

## Project Overview

The project implements an RC4-inspired encryption and decryption workflow.

The program accepts plaintext and a key, converts both into binary strings, processes the binary data using a permutation-based state array and XOR operations, and displays the encrypted result in binary and hexadecimal formats.

## Implemented Features

### 1. Binary Conversion

The `BinaryConverter` class provides methods for converting data:

- `textToBits()` — converts text into a binary string using 8 bits per input byte.
- `bitsToText()` — converts complete groups of 8 bits back into text.
- `b_hex()` — converts complete binary bytes into hexadecimal representation.
- `hex_b()` — converts hexadecimal byte pairs into binary representation.

### 2. RC4-Inspired Processing

The implementation contains the following components:

- `KSA()` — initializes and permutes the 256-element state array using the supplied key representation.
- `PRGA()` — updates the internal state and generates a pseudo-random byte.
- `enc_RC4()` — processes binary data using XOR with generated keystream bits.

### 3. Console Interface

The application provides two operations:

- Encryption of input text.
- Decryption of hexadecimal ciphertext.

The program also supports repeated operations through a console menu.

## Project Structure

```text
cpp-rc4-stream-cipher/
├── README.md
├── include/
│   └── BinaryConverter.h
└── src/
    ├── main.cpp
    └── rc4.cpp
```

## Technologies

- C++
- Standard Template Library (STL)
- `iostream`
- `string`
- `bitset`
- `sstream`
- `iomanip`

## Build and Run

Example compilation command after separating declarations and implementations into the recommended files:

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/rc4.cpp -o rc4
```

Run:

```bash
./rc4
```

On Windows:

```bash
rc4.exe
```

## Current Implementation Limitations

- The key is converted into a binary string before being passed to KSA. Consequently, the algorithm processes the ASCII representations of `'0'` and `'1'`, rather than the original key bytes.
- The implementation generates a new PRGA output byte for every input bit. Standard RC4 generates a byte of keystream for each byte of plaintext.
- The `x()` helper function is not used by the main encryption workflow.
- Empty keys are not validated and can cause division by zero in KSA.
- The hexadecimal conversion methods do not fully validate malformed or incomplete input.
- The string input helper may discard the first character of subsequent input values because it unconditionally calls `cin.ignore()`.
- The current source organization includes a `.cpp` file directly instead of using a separate header file.

## Security Considerations

RC4 is a deprecated stream cipher and is not recommended for protecting real-world data.

This project is intended for educational purposes only. It demonstrates concepts related to stream ciphers, state permutations, pseudo-random keystream generation and XOR operations. It should not be used as a production cryptographic implementation.

## Learning Outcomes

- Understanding the general principles of stream ciphers.
- Studying the KSA and PRGA stages associated with RC4.
- Practicing bitwise XOR operations.
- Converting text into binary and hexadecimal representations.
- Working with arrays, strings, classes and standard C++ libraries.
- Organizing a C++ project into header and implementation files.
