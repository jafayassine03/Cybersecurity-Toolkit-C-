# Cybersecurity Toolkit (C)

A lightweight, console-based security utility written in C. This toolkit leverages the **OpenSSL** library to provide essential cryptographic functionalities, file integrity verification, password analysis, and an educational brute-force simulation.

## 🌟 Features

*   **Password Strength Analyzer**: Evaluates complexity based on length, casing, numbers, and special characters.
*   **File Integrity Verifier**: Computes high-speed **SHA-256** cryptographic hashes of any local file to detect tampering.
*   **File Encryption (AES-256-CBC)**: Secures sensitive files using strong symmetric encryption with random IV generation.
*   **File Decryption (AES-256-CBC)**: Restores encrypted files back to their original state using your secret password.
*   **Brute-Force Simulator**: An educational tool demonstrating how weak alphanumeric passwords can be broken via combinatorial search.
*   ase64 Decode File


## 🔒 Security Notice

This toolkit is designed for educational and personal administrative purposes. 
*   The key derivation function uses a direct SHA-256 mapping of the password for simplicity. 
*   For enterprise production environments, modern key-stretching mechanisms like **PBKDF2**, **bcrypt**, or **Argon2** are highly recommended to resist advanced hardware-accelerated offline attacks.

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
