#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PW_LEN 8

int main() {
    // --- Stored Values Only (MEANT for RE Lab) ---
    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char atbash[]   = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    // ------------------------------------------------

    char plaintext[PW_LEN + 1];
    char atbash_pw[PW_LEN + 1];
    char guess[PW_LEN + 1];

    srand((unsigned)time(NULL));

    // Generate random plaintext password
    for (int i = 0; i < PW_LEN; i++) {
        int r = rand() % 26;
        plaintext[i] = alphabet[r];
    }
    plaintext[PW_LEN] = '\0';

    // Convert to Atbash (cipher only shown to user)
    for (int i = 0; i < PW_LEN; i++) {
        char p = plaintext[i];
        int idx = p - 'A';          // position in normal alphabet
        atbash_pw[i] = atbash[idx]; // mapped Atbash letter
    }
    atbash_pw[PW_LEN] = '\0';

    printf("=== Reverse Engineering Challenge ===\n");
    printf("Below is the encrypted password.\n");
    printf("You must decrypt it to exit.\n\n");

    printf("ATBASH PASSWORD: %s\n", atbash_pw);

    // Loop until the correct plaintext is entered
    while (1) {
        printf("\nEnter original plaintext password: ");
        scanf("%8s", guess);

        // convert guess to uppercase to match stored plaintext
        for (int i = 0; i < PW_LEN; i++) {
            if (guess[i] >= 'a' && guess[i] <= 'z')
                guess[i] -= 32;
        }

        if (strcmp(guess, plaintext) == 0) {
            printf("Correct! Exiting program.\n");
            break;
        } else {
            printf("Incorrect. Try again.\n");
        }
    }

    return 0;
}
