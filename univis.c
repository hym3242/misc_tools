#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <utf-8 string>\n", argv[0]);
        return 1;
    }

    unsigned char *str = (unsigned char *)argv[1];
    int i = 0;
    unsigned int codepoint;

    while (str[i]) {
        if (str[i] <= 0x7F) {
            // ASCII character, print as is
            printf("%c", str[i]);
            i++;
            continue;
        }

        if ((str[i] & 0xF0) == 0xF0) {
            // 4-byte sequence
            codepoint = ((str[i] & 0x07) << 18) | 
                        ((str[i+1] & 0x3F) << 12) | 
                        ((str[i+2] & 0x3F) << 6) | 
                        (str[i+3] & 0x3F);
            i += 4;
        } else if ((str[i] & 0xE0) == 0xE0) {
            // 3-byte sequence
            codepoint = ((str[i] & 0x0F) << 12) | 
                        ((str[i+1] & 0x3F) << 6) | 
                        (str[i+2] & 0x3F);
            i += 3;
        } else if ((str[i] & 0xC0) == 0xC0) {
            // 2-byte sequence
            codepoint = ((str[i] & 0x1F) << 6) | 
                        (str[i+1] & 0x3F);
            i += 2;
        } else {
            fprintf(stderr, "Invalid UTF-8 at byte %d\n", i);
            return 1;
        }

        printf("\e[7mU+%04X\e[0m", codepoint);
    }

	printf("\n");
    return 0;
}
