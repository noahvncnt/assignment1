#include <stdint.h>
#include <string.h>
#include <stdio.h>


void div_convert(uint32_t n, int base, char *out){ //algorithm: Repeatedly divide by base, collecting remainders

    char temp [65]; // Temporary buffer
    int pos = 0;

    // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    // Extract digits from right to left
    while (n > 0){
        int remainder = n % base;
        n = n / base;

        // Convert digit to character
        if (remainder < 10)
            temp [pos++] = '0' + remainder;
        else
            temp [pos++] = 'A' + (remainder - 10);
    }

    //reverse temp into out
    for(int i = 0; i < pos; i++)
        out[i] = temp[pos - 1 - i];

    out[pos] = '\0';

    //printf("%s\n", out);
}


void sub_convert(uint32_t n, int base, char *out) {
    char temp[65];   // Temporary buffer
    int pos = 0;

    // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    //Find the biggest power of base <= n without overflow
    uint32_t power = 1;
    while (power <= n / (uint32_t)base) {
        power *= (uint32_t)base;
    }

    // Extract digits left to right
    while (power > 0) {
        int digit = 0;

        // Subtract power until n is smaller
        while (n >= power) {
            n -= power;
            digit++;
        }

        // Convert digit to character
        if (digit < 10)
            temp[pos++] = '0' + digit;
        else
            temp[pos++] = 'A' + (digit - 10);

        power /= base;
    }

    // Null terminate
    temp[pos] = '\0';

    // Copy to out
    strcpy(out, temp);

    //printf("%s\n", out);
}

void print_tables(uint32_t n) {
    char bin[33], oct[12], hex[9];

    // Original number
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
           bin, oct, n, hex);

    // Left shift by 3
    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
           bin, oct, shifted, hex);

    // AND with 0xFF
    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
           bin, oct, masked, hex);
}
