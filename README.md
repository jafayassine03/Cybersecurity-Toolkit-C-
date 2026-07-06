# Cybersecurity Toolkit (C)

A lightweight, console-based security utility written in C. This toolkit leverages the **OpenSSL** library to provide essential cryptographic functionalities, file integrity verification, password analysis, and an educational brute-force simulation.

## 🌟 Features

*   **Password Strength Analyzer**: Evaluates complexity based on length, casing, numbers, and special characters.
*   **File Integrity Verifier**: Computes high-speed **SHA-256** cryptographic hashes of any local file to detect tampering.
*   **File Encryption (AES-256-CBC)**: Secures sensitive files using strong symmetric encryption with random IV generation.
*   **File Decryption (AES-256-CBC)**: Restores encrypted files back to their original state using your secret password.
*   **Brute-Force Simulator**: An educational tool demonstrating how weak alphanumeric passwords can be broken via combinatorial search.

## 🛠️ Prerequisites & Dependencies

To compile and run this project, you need a C compiler and the OpenSSL development library installed on your system.

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential libssl-dev
```

### macOS
```bash
brew install openssl
```

### Windows
You can use **MSYS2** or **vcpkg** to install the OpenSSL binaries and link them to your compiler (GCC/Clang/MSVC).

## 🚀 Compilation

Compile the project by linking the OpenSSL crypto libraries (`-lcrypto`).

```bash
gcc main.c -o crypto_toolkit -lcrypto
```

*Note: On macOS, you might need to specify the path to Homebrew's OpenSSL directory:*
```bash
gcc main.c -o crypto_toolkit -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lcrypto
```

## 💻 Usage

Run the compiled executable from your terminal:

```bash
./crypto_toolkit
```

### Main Menu Interface

```text
====================================
      Cybersecurity Toolkit (C)
====================================
1. Check Password Strength
2. File Integrity (SHA-256)
3. Encrypt File (AES-256)
4. Decrypt File (AES-256)
5. Simulate Brute-Force Attack
6. Exit
Choose: 
```

## 🔒 Security Notice

This toolkit is designed for educational and personal administrative purposes. 
*   The key derivation function uses a direct SHA-256 mapping of the password for simplicity. 
*   For enterprise production environments, modern key-stretching mechanisms like **PBKDF2**, **bcrypt**, or **Argon2** are highly recommended to resist advanced hardware-accelerated offline attacks.

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
