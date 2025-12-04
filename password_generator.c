#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define PASSWORD_LENGTH 8
#define SHIFT_AMOUNT 3

// Character set for password generation (simplified for easier reverse engineering)
const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Function to generate a random password
void generate_random_password(char *password, int length) {
    for (int i = 0; i < length; i++) {
        int index = rand() % (sizeof(charset) - 1);
        password[i] = charset[index];
    }
    password[length] = '\0';
}

// Function to apply Caesar cipher encryption (simplified)
char encrypt_char(char c, int shift) {
    if (isalpha(c)) {
        char base = 'A'; // Only uppercase for simplicity
        return ((c - base + shift) % 26) + base;
    }
    return c; // Return unchanged if not a letter
}

// Function to encrypt the entire password using Caesar cipher
void encrypt_password(const char *original, char *encrypted, int shift) {
    int len = strlen(original);
    for (int i = 0; i < len; i++) {
        encrypted[i] = encrypt_char(original[i], shift);
    }
    encrypted[len] = '\0';
}

// Function to decrypt Caesar cipher (simplified)
char decrypt_char(char c, int shift) {
    if (isalpha(c)) {
        char base = 'A'; // Only uppercase
        int decrypted = (c - base - shift) % 26;
        if (decrypted < 0) decrypted += 26;
        return decrypted + base;
    }
    return c; // Return unchanged if not a letter
}

// Function to decrypt the entire password (for verification)
void decrypt_password(const char *encrypted, char *decrypted, int shift) {
    int len = strlen(encrypted);
    for (int i = 0; i < len; i++) {
        decrypted[i] = decrypt_char(encrypted[i], shift);
    }
    decrypted[len] = '\0';
}

// Function to check if entered password matches the original
int check_password(const char *input, const char *original) {
    return strcmp(input, original) == 0;
}

int main() {
    char original_password[PASSWORD_LENGTH + 1];
    char encrypted_password[PASSWORD_LENGTH + 1];
    char user_input[PASSWORD_LENGTH + 10]; // Extra space for safety
    
    // Initialize random seed with a fixed value for consistent passwords
    srand(12345); // Fixed seed for reproducible results in reverse engineering
    
    // Generate the secret password
    generate_random_password(original_password, PASSWORD_LENGTH);
    
    // Encrypt the password
    encrypt_password(original_password, encrypted_password, SHIFT_AMOUNT);
    
    printf("=== Secret Access Challenge ===\n");
    printf("Encrypted key: %s\n", encrypted_password);
    printf("Enter the exit key to complete the challenge: ");
    
    // Get user input
    fgets(user_input, sizeof(user_input), stdin);
    // Remove newline character
    user_input[strcspn(user_input, "\n")] = '\0';
    
    // Check if the password is correct
    if (check_password(user_input, original_password)) {
        printf("\n*** CONGRATULATIONS! ***\n");
        printf("You successfully completed the reverse engineering challenge!\n");
        printf("Well done finding the original password: %s\n", original_password);
        printf("Good job! Press any key to exit...\n");
        getchar();
    } else {
        printf("\nIncorrect key. Challenge failed.\n");
        printf("Try again next time!\n");
        printf("Press any key to exit...\n");
        getchar();
    }
    
    return 0;
}