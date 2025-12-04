/* RELab_easy.c
   Super-easy reverse engineering lab for beginners.
   - Fixed plaintext password.
   - Key is an obvious ASCII string in .rdata: "EXITKEY"
   - Repeating XOR encryption
   - Program writes password.enc and then loops until the user types the plaintext.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static const char KEY[] = "EXITKEY";            /* obvious key - search for EXITKEY */
static const char PLAINTEXT[] = "lab-password"; /* fixed password - students should recover this */

/* repeating XOR (same function for encrypt/decrypt) */
static void xor_stream(uint8_t *buf, size_t buflen, const uint8_t *key, size_t keylen) {
    for (size_t i = 0; i < buflen; ++i)
        buf[i] ^= key[i % keylen];
}

int main(void) {
    const size_t len = strlen(PLAINTEXT);

    printf("Program waits for the plaintext to exit.\n");

    /* now require the plaintext to exit */
    char input[128];
    while (1) {
        printf("Enter password to exit: ");
        if (!fgets(input, sizeof(input), stdin)) { clearerr(stdin); continue; }
        /* trim newline */
        size_t n = strlen(input);
        if (n && (input[n-1] == '\n' || input[n-1] == '\r')) input[--n] = '\0';

        if (n == len && strcmp(input, PLAINTEXT) == 0) {
            printf("Correct — exiting.\n");
            return 0;
        }
        printf("Incorrect. Try again.\n");
    }
    return 0;
}
