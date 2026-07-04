#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>

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

void sha256_file(const char *filename, unsigned char output[65]) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Cannot open file\n");
        return;
    }

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    const int bufSize = 32768;
    unsigned char *buffer = malloc(bufSize);
    int bytesRead = 0;

    while ((bytesRead = fread(buffer, 1, bufSize, file))) {
        SHA256_Update(&sha256, buffer, bytesRead);
    }

    SHA256_Final(output, &sha256);

    fclose(file);
    free(buffer);
}

void print_hash(unsigned char hash[32]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);
    printf("\n");
}

void file_integrity() {
    char filename[256];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter file path: ");
    scanf("%s", filename);

    sha256_file(filename, hash);

    printf("\nSHA-256 Hash:\n");
    print_hash(hash);
}

int main() {
    int choice;
    char password[256];

    while (1) {
        printf("\n============================\n");
        printf(" Cybersecurity Toolkit (C)\n");
        printf("============================\n");
        printf("1. Check Password Strength\n");
        printf("2. File Integrity (SHA-256)\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter password: ");
                scanf("%s", password);
                check_password_strength(password);
                break;

            case 2:
                file_integrity();
                break;

            case 3:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
