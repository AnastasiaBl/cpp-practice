# Digital Signature Verification Chat (RSA and ElGamal)

A C++ client-server chat application demonstrating digital signature generation and verification using RSA and ElGamal algorithms.

The project combines TCP network communication, multithreading, message hashing, and public-key cryptography to demonstrate how digital signatures can be used to verify message authenticity and integrity.

## Overview

The application consists of a TCP server and multiple clients. Users connect to the server, select a digital signature algorithm, and exchange messages.

Before sending a message, the client calculates its hash and generates a digital signature using either RSA or ElGamal. The server receives the message and signature parameters, verifies the signature, and forwards messages that pass verification to other connected clients.

## Implemented Features

### 1. TCP Client-Server Communication

- TCP server listening for incoming connections.
- Client connection to the server.
- Sending and receiving messages.
- Broadcasting verified messages to connected clients.
- Support for Windows and Linux socket APIs.

### 2. Multithreading

- Separate threads for sending and receiving messages on the client.
- A dedicated thread for handling each connected client on the server.
- Mutex-based synchronization for shared server data.

### 3. Message Hashing

- Custom hash calculation implemented in `hash.cpp`.
- Processing messages in 64-bit blocks.
- A custom compression construction using Speck-inspired round operations.
- Generation of a 256-bit hash output.

The hash implementation is experimental and is not a standardized or cryptographically validated hash function.

### 4. RSA Digital Signatures

The RSA implementation demonstrates:

- Prime number validation.
- Generation of RSA parameters.
- Calculation of the modulus and Euler's totient function.
- Selection of the public exponent.
- Calculation of the private exponent.
- Signature generation:

`S = m^d mod n`

- Signature verification:

`m1 = S^e mod n`

### 5. ElGamal Digital Signatures

The ElGamal implementation demonstrates:

- Prime modulus selection.
- Selection of the generator and private key.
- Public key calculation.
- Session key generation.
- Calculation of the signature components.
- Signature verification.

Signature generation:

`s = (m - x * r) * k^-1 mod (p - 1)`

where:

`r = g^k mod p`

Signature verification:

`y^r * r^s ≡ g^m (mod p)`

### 6. Signature Verification on the Server

The server selects the appropriate verification procedure based on the signature algorithm specified in the packet.

Messages with signatures that pass verification are forwarded to other connected clients. Messages that fail verification are rejected.

## Technologies

- C++
- TCP sockets
- Windows Winsock API
- POSIX sockets
- `std::thread`
- `std::mutex`
- RSA
- ElGamal
- Modular arithmetic
- Custom hash construction

## Project Structure

```text
cpp-digital-signature-chat/
├── README.md
├── client.cpp
├── server.cpp
├── network.cpp
├── network.h
├── rsa.cpp
├── rsa.h
├── elgamal.cpp
├── elgamal.h
├── hash.cpp
└── hash.h
```

## How It Works

### Message Sending

1. The user enters a message in the client application.
2. The client calculates the message hash.
3. The selected algorithm generates a digital signature.
4. The client creates a packet containing the message, signature and public parameters.
5. The packet is transmitted to the server over TCP.

### Message Verification

1. The server receives the packet.
2. The server identifies the signature algorithm.
3. The corresponding verification function is executed.
4. The message and signature are checked.
5. If verification succeeds, the server broadcasts the message to other clients.
6. If verification fails, the server rejects the message.

## Building the Project

The following commands assume that the source files are located in the project root directory.

### Windows

Build the client:

```bash
g++ client.cpp rsa.cpp elgamal.cpp hash.cpp network.cpp -o client.exe -std=c++14 -lws2_32
```

Build the server:

```bash
g++ server.cpp rsa.cpp elgamal.cpp hash.cpp network.cpp -o server.exe -std=c++14 -lws2_32
```

### Linux

Build the client:

```bash
g++ client.cpp rsa.cpp elgamal.cpp hash.cpp network.cpp -o client -std=c++14 -pthread
```

Build the server:

```bash
g++ server.cpp rsa.cpp elgamal.cpp hash.cpp network.cpp -o server -std=c++14 -pthread
```

## Running the Application

1. Start the server:

```bash
./server
```

2. Start one or more client instances:

```bash
./client
```

3. Enter a username.
4. Select RSA or ElGamal.
5. Enter messages and observe the signature verification results.

The client currently connects to `127.0.0.1` on port `1111`. To connect from another machine, the server address and client configuration must be adjusted.

## Limitations and Security Considerations

This project is an educational demonstration and must not be used as a production security solution.

Known limitations:

- RSA verification does not recalculate the hash from the received message. It verifies the signature against a hash value supplied in the packet.
- The custom hash construction is not a standardized or independently validated cryptographic hash function.
- The RSA implementation uses textbook RSA signatures without a secure padding scheme such as RSA-PSS.
- ElGamal public parameters are transmitted with each message and are not authenticated through a trusted key infrastructure.
- The application does not implement secure key storage or persistent user identity-to-key binding.
- Random values are generated using `rand()`, which is unsuitable for cryptographic key generation.
- RSA and ElGamal implementations use small parameters and integer arithmetic, making them unsuitable for real-world cryptographic protection.
- TCP communication does not provide encryption or confidentiality. Messages are transmitted in plaintext.
- The custom packet format uses a delimiter-based serialization scheme and does not safely handle all possible message contents.
- Socket operations require more robust handling of partial reads, writes, connection errors and message size limits.
- The server's broadcast and client lifecycle logic requires additional synchronization and resource management.

## Future Improvements

- Recalculate and verify the message hash on the server for both algorithms.
- Replace the experimental hash construction with a standardized cryptographic hash function.
- Implement RSA-PSS signatures.
- Introduce secure random number generation.
- Validate and authenticate public keys.
- Implement persistent user key management.
- Improve TCP framing, serialization and error handling.
- Add TLS for encrypted network communication.
- Improve thread lifecycle management and synchronization.
- Add automated tests for signature generation and verification.

## Disclaimer

This project is intended for educational purposes only. It demonstrates digital signatures, public-key cryptography, hashing and TCP communication. It does not provide production-grade authentication, integrity protection or confidentiality.
