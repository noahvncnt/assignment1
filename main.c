// main.c (minimal)
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : "tests.txt";
    FILE *f = fopen(path, "r");
    if (!f) { printf("Error: Could not open %s\n", path); return 1; }

    char line[256];
    int test_num = 1;

    while (fgets(line, sizeof(line), f)) {
        // skip comments and empty
        if (line[0] == '#' || line[0] == '\n') continue;

        //handle print_tables "print_tables <n> FORMATTED_OUTPUT"
        unsigned nPT; char tag[32];
        if (sscanf(line, "print_tables %u %31s", &nPT, tag) == 2) {
            print_tables(nPT);
            printf("Test %d: print_tables %u -> [SKIPPED - formatted output]\n", test_num++, nPT);
            continue;
        }

        // handle conversions: "<func> <n> <base> <expected>"
        char func[16], expected[65], actual[65];
        unsigned n; int base;
        if (sscanf(line, "%15s %u %d %64s", func, &n, &base, expected) != 4) {
            // not a valid test line
            continue;
        }

        if (strcmp(func, "div_convert") == 0) {
            div_convert((uint32_t)n, base, actual);
        } else if (strcmp(func, "sub_convert") == 0) {
            sub_convert((uint32_t)n, base, actual);
        } else {
            //ignore unknown function
            continue;
        }

        if (strcmp(actual, expected) == 0) {
            printf("Test %d: %s %u %d -> %s [PASS]\n",
                   test_num, func, n, base, actual);
        } else {
            printf("Test %d: %s %u %d -> got %s, expected %s [FAIL]\n",
                   test_num, func, n, base, actual, expected);
        }
        test_num++;
    }

    fclose(f);
    return 0;
}
