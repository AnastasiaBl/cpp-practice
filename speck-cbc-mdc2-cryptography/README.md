# Speck-Inspired Encryption, CBC Mode and MDC-2-Inspired Hashing

An educational C++ project demonstrating block encryption and decryption, Cipher Block Chaining (CBC), and a custom hash construction inspired by MDC-2.

The implementation combines a Speck-inspired 128-bit block cipher, a CBC-style chaining mechanism, hexadecimal data representation and a two-branch hash construction.

## Overview

The program provides several interactive modes:

1. **Speck-inspired encryption and decryption** — processes data in 128-bit blocks using a 128-bit key representation.
2. **CBC mode** — applies block chaining by XORing each plaintext block with the previous ciphertext block before encryption.
3. **MDC-2-inspired hashing** — processes message blocks through two parallel chaining states and produces a 256-bit output.
4. **CBC and hashing workflow** — demonstrates encryption, decryption and hash calculation.
5. **Test mode** — executes predefined test scenarios using different messages and keys.

## Features

- Implementation of Speck-inspired round transformations.
- 128-bit block processing using two 64-bit words.
- Key schedule generation with 32 rounds.
- Block encryption and decryption.
- CBC-style chaining of ciphertext blocks.
- Custom initialization value generation.
- Two-branch hash construction inspired by MDC-2.
- Conversion between binary data and hexadecimal representation.
- Interactive console menu.
- Predefined test cases for encryption and decryption workflows.

## Cryptographic Components

### 1. Speck-Inspired Block Cipher

The block transformation uses two 64-bit words and 32 rounds.

The round function includes:
- Right rotation by 8 bits.
- Addition modulo \(2^{64}\).
- XOR with a round key.
- Left rotation by 3 bits.
- XOR between the two state words.

The key schedule generates round keys from two 64-bit key components.

The implementation follows a Speck-inspired round structure. Its compliance with a specific standardized Speck variant has not been independently verified.

### 2. CBC Mode

The CBC-style encryption process XORs each plaintext block with the previous chaining value before applying the block cipher:

\[
C_i = E_K(P_i \oplus C_{i-1})
\]

The first chaining value is generated from the key by the custom `gener()` function.

Decryption reverses the block transformation and XORs the result with the previous chaining value.

### 3. MDC-2-Inspired Hash Construction

The `MDC_2()` function maintains two independent pairs of 64-bit chaining values.

Each input block is processed through two encryption branches, and the results are combined with the previous states.

The final output consists of four 64-bit values, forming a 256-bit result.

This is a custom MDC-2-inspired construction, not a verified implementation of the standardized MDC-2 hash function.

### 4. Data Representation

The program includes functions for:
- Converting input bytes into 64-bit words.
- Splitting data into 128-bit blocks.
- Converting 64-bit words back into bytes.
- Representing binary data as hexadecimal strings.
- Converting hexadecimal input back into byte sequences.

## Project Structure

```text
cpp-speck-cbc-mdc2-cryptography/
├── README.md
└── src/
    └── main.cpp
```

## Implementation Details

| Function | Responsibility |
|---|---|
| `input_int()` | Reads and validates integer input |
| `input_ra()` | Validates menu selections |
| `to_uint64()` | Converts up to 16 input bytes into two 64-bit words |
| `text()` | Reads the message and encryption key |
| `hex()` | Converts a hexadecimal character into its numeric value |
| `hex_str()` | Converts hexadecimal data into bytes |
| `bin_str()` | Converts byte sequences into hexadecimal representation |
| `bit_byte()` | Converts a 64-bit word into eight bytes |
| `shift()` | Performs 64-bit rotations |
| `round()` | Implements the forward round transformation |
| `round_de()` | Implements the inverse round transformation |
| `encryption_speck()` | Performs 32 rounds of block encryption |
| `decryption_speck()` | Performs block decryption |
| `gener()` | Generates a custom initialization value |
| `encryption_cbc()` | Encrypts data using CBC-style chaining |
| `decryption_cbc()` | Decrypts data using CBC-style chaining |
| `MDC_2()` | Updates the two hash chaining branches |
| `main_i5()` | Runs the combined encryption, decryption and hash demonstration |
| `main()` | Controls the interactive application |

## Technologies

- C++
- 64-bit unsigned integer arithmetic
- Bitwise operations
- Bit rotations
- XOR operations
- Block cipher principles
- CBC mode
- Hash construction principles
- Hexadecimal encoding
- Windows Console API

## Build

The source code uses `Windows.h` and Windows console functions, so the current version targets Windows.

Compile with a C++ compiler supporting C++17:

```bash
g++ -std=c++17 src/main.cpp -o cryptography.exe
```

Run:

```bash
cryptography.exe
```

## Limitations and Security Considerations

This project is an educational implementation and is not suitable for protecting real data.

Known limitations include:

- The implementation has not been verified against official Speck test vectors.
- The key input is not restricted to an exact 128-bit key length. Short keys are zero-padded and longer keys are truncated.
- The final incomplete block is implicitly zero-padded, but the original message length is not stored with the ciphertext.
- The CBC initialization value is deterministically derived from the key instead of being generated as a fresh unpredictable IV for each encryption.
- The custom `gener()` function is not a standardized cryptographic IV-generation mechanism.
- The MDC-2-inspired construction has not been verified against the standardized MDC-2 specification or test vectors.
- The hash construction does not implement an explicit, unambiguous message-padding and length-encoding scheme.
- The combined CBC and hashing mode contains data-flow inconsistencies: the ciphertext is not correctly passed to the hash calculation in the corresponding menu branch.
- The program does not perform a final integrity comparison between the hashes calculated before and after the encryption/decryption workflow.
- Hexadecimal input validation is incomplete: invalid characters are converted to zero, and an unmatched final character is ignored.
- Global state is used for message buffers and hash chaining values.
- The implementation does not provide authenticated encryption or message authentication.

## Security Notice

The project demonstrates cryptographic algorithms and their composition for educational purposes. It must not be used as a production encryption or integrity-protection system.

For practical applications, use established cryptographic libraries and authenticated encryption schemes such as AES-GCM or ChaCha20-Poly1305.

## Learning Objectives

- Understand the structure of a 128-bit block cipher.
- Explore round transformations and key scheduling.
- Implement encryption and decryption using 64-bit arithmetic.
- Understand CBC block chaining.
- Explore the principles of two-branch hash constructions.
- Practice bitwise operations and hexadecimal encoding.
- Analyze the importance of initialization vectors, padding and integrity verification.
