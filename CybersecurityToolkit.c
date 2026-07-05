#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void check_password_strength(char password[]) {
    int length = strlen(password);
    int upper = 0, lower = 0, digit = 0, special = 0;

    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) upper = 1;
        else if (islower(password[i])) lower = 1;
        else if (isdigit(password[i])) digit = 1;
        else special = 1;
    }

    printf("\nPassword Analysis:\n");

    if (length >= 12 && upper && lower && digit && special)
        printf("Strong password\n");
    else if (length >= 8 && ((upper && lower && digit) || (upper && lower && special)))
        printf("Medium password\n");
    else
        printf("Weak password\n");
}

void sha256_file(const char *filename, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Cannot open file\n");
        return;
    }

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    unsigned char buffer[32768];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
        SHA256_Update(&sha256, buffer, bytesRead);

    SHA256_Final(hash, &sha256);

    fclose(file);
}

void print_hash(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);
    printf("\n");
}

void file_integrity() {
    char filename[256];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter file path: ");
    scanf("%255s", filename);

    sha256_file(filename, hash);

    printf("\nSHA-256 Hash:\n");
    print_hash(hash);
}

void derive_key(const char *password, unsigned char key[32]) {
    SHA256((const unsigned char *)password, strlen(password), key);
}

void encrypt_file() {
    char input[256], output[256], password[256];

    printf("Input file: ");
    scanf("%255s", input);

    printf("Output file: ");
    scanf("%255s", output);

    printf("Password: ");
    scanf("%255s", password);

    FILE *fin = fopen(input, "rb");
    if (!fin) {
        printf("Cannot open input file\n");
        return;
    }

    FILE *fout = fopen(output, "wb");
    if (!fout) {
        fclose(fin);
        printf("Cannot create output file\n");
        return;
    }

    unsigned char key[32];
    unsigned char iv[16];

    derive_key(password, key);
    RAND_bytes(iv, sizeof(iv));

    fwrite(iv, 1, sizeof(iv), fout);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char inbuf[1024];
    unsigned char outbuf[1040];
    int inlen, outlen;

    while ((inlen = fread(inbuf, 1, sizeof(inbuf), fin)) > 0) {
        EVP_EncryptUpdate(ctx, outbuf, &outlen, inbuf, inlen);
        fwrite(outbuf, 1, outlen, fout);
    }

    EVP_EncryptFinal_ex(ctx, outbuf, &outlen);
    fwrite(outbuf, 1, outlen, fout);

    EVP_CIPHER_CTX_free(ctx);

    fclose(fin);
    fclose(fout);

    printf("File encrypted successfully.\n");
}

void decrypt_file() {
    char input[256], output[256], password[256];

    printf("Encrypted file: ");
    scanf("%255s", input);

    printf("Output file: ");
    scanf("%255s", output);

    printf("Password: ");
    scanf("%255s", password);

    FILE *fin = fopen(input, "rb");
    if (!fin) {
        printf("Cannot open encrypted file\n");
        return;
    }

    FILE *fout = fopen(output, "wb");
    if (!fout) {
        fclose(fin);
        printf("Cannot create output file\n");
        return;
    }

    unsigned char key[32];
    unsigned char iv[16];

    derive_key(password, key);

    fread(iv, 1, sizeof(iv), fin);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    unsigned char inbuf[1024];
    unsigned char outbuf[1040];
    int inlen, outlen;

    while ((inlen = fread(inbuf, 1, sizeof(inbuf), fin)) > 0) {
        EVP_DecryptUpdate(ctx, outbuf, &outlen, inbuf, inlen);
        fwrite(outbuf, 1, outlen, fout);
    }

    if (EVP_DecryptFinal_ex(ctx, outbuf, &outlen))
        fwrite(outbuf, 1, outlen, fout);
    else
        printf("Wrong password or corrupted file.\n");

    EVP_CIPHER_CTX_free(ctx);

    fclose(fin);
    fclose(fout);

    printf("Decryption finished.\n");
}

int main() {
    OpenSSL_add_all_algorithms();

    int choice;
    char password[256];

    while (1) {
        printf("\n====================================\n");
        printf("      Cybersecurity Toolkit (C)\n");
        printf("====================================\n");
        printf("1. Check Password Strength\n");
        printf("2. File Integrity (SHA-256)\n");
        printf("3. Encrypt File (AES-256)\n");
        printf("4. Decrypt File (AES-256)\n");
        printf("5. Exit\n");
        printf("Choose: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter password: ");
                scanf("%255s", password);
                check_password_strength(password);
                break;

            case 2:
                file_integrity();
                break;

            case 3:
                encrypt_file();
                break;

            case 4:
                decrypt_file();
                break;

            case 5:
                printf("Exiting...\n");
                EVP_cleanup();
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
