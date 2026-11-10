# Random Permutation Matrix Cipher

An educational C++ program demonstrating a text transposition technique based on a randomly shuffled matrix of character indices.

The project was originally developed as an exercise on the topic of magic squares. However, the current implementation uses a random permutation matrix rather than a mathematical magic square.

## Overview

The program demonstrates a basic text rearrangement approach:

1. The user enters a text message.
2. The program calculates the dimensions of a square matrix based on the message length.
3. A sequence of integer indices is generated.
4. The indices are randomly shuffled to create a permutation matrix.
5. Characters are placed into the matrix according to the shuffled indices.
6. The resulting character matrix is traversed row by row to produce the transformed text.

The program also contains an interactive decryption mode, but the current implementation does not correctly restore the original message because it does not reuse or reconstruct the original permutation key.

## Features

- Interactive encryption and decryption menu.
- Text input through the console.
- Automatic calculation of square matrix dimensions.
- Generation of a sequence of character indices.
- Random shuffling using the C++ `<random>` library.
- Dynamic allocation of two-dimensional arrays.
- Mapping of text characters to matrix positions.
- Display of the generated permutation matrix and its indices.
- Output of the transformed text.
- Manual character input in the decryption mode.

## Encryption Algorithm

Let `L` be the length of the input text.

The program calculates the matrix dimension as:

\[
n = \left\lceil \sqrt{L} \right\rceil
\]

The matrix contains:

\[
N = n^2
\]

positions.

A sequence of indices from `0` to `N - 1` is generated and randomly shuffled.

Each matrix cell receives a character from the input text using the corresponding index. Positions outside the original text length are filled with a hyphen (`-`).

The resulting matrix is traversed row by row. Padding positions are skipped, and the remaining characters form the transformed text.

## Implementation Details

| Component | Responsibility |
|---|---|
| `encryption()` | Maps text characters to the matrix and outputs the transformed text |
| `decryption()` | Requests matrix characters from the user and attempts to reconstruct the text |
| `main()` | Controls input, matrix allocation, randomization and program flow |
| `std::shuffle()` | Randomly rearranges the index sequence |
| `std::mt19937` | Generates pseudorandom values |
| `std::random_device` | Initializes the random number generator |

## Project Structure

```text
cpp-random-permutation-cipher/
├── README.md
└── src/
    └── main.cpp
```

## Technologies

- C++
- Standard Template Library (STL)
- `std::string`
- Dynamic memory allocation
- Two-dimensional arrays
- `<algorithm>`
- `<random>`
- `std::shuffle`
- `std::mt19937`
- Windows Console API

## Limitations

The current implementation is an educational demonstration and has several limitations:

- The generated matrix is a random permutation matrix, not a mathematical magic square.
- The generated permutation is not saved or exported as a reusable key.
- The decryption procedure creates a sequential index matrix instead of using the original permutation.
- The current decryption implementation cannot reliably restore the original plaintext.
- The matrix dimensions are calculated from the entered text length. Since padding characters are omitted from the transformed output, the original matrix dimensions cannot reliably be recovered from the transformed text alone.
- The hyphen (`-`) is used as a padding marker. A hyphen occurring in the original message is also omitted from the output.
- The program uses `char` and `std::string` indexing, which operates on bytes rather than Unicode characters. Multibyte UTF-8 text, including Cyrillic text, may be processed incorrectly depending on the input encoding.
- Dynamic memory is managed manually using `new[]` and `delete[]`.
- Input validation is limited.
- `Windows.h` and Windows Console API calls make the current version platform-dependent.
- Random permutation generation is not a cryptographically secure key-generation mechanism.

## Security Notice

This project demonstrates a basic transposition technique. It does not provide modern cryptographic security and must not be used to protect confidential information.

Randomly rearranging characters does not provide the security guarantees of established encryption algorithms.

## Build

The current source code targets Windows because it uses `Windows.h` and console code-page functions.

Compile using a C++ compiler with Windows SDK support:

```bash
g++ -std=c++17 src/main.cpp -o cipher.exe
```

Run:

```bash
cipher.exe
```

## Learning Objectives

- Understand matrix-based text transformations.
- Practice working with two-dimensional arrays.
- Generate and shuffle sequences of indices.
- Use pseudorandom number generators in C++.
- Apply dynamic memory allocation.
- Explore the basic principles of transposition ciphers.
- Understand why encryption and decryption must use matching keys.
