//dceol is acronym for "dark themed color even odd lines"
#include <stdio.h>
//#include <unistd.h>

int main() {
    int c;
    int lf_count = 0; // Count of LF characters encountered

    while ((c = getchar()) != EOF) {
        if (c == 0x0a) { // LF character
            lf_count++;
            if (lf_count % 2 == 1) { // Even position
                printf("\e[48;5;235m");
            } else { // Odd position
                printf("\e[0m");
            }
        }
        putchar(c);
    }

    // Reset terminal color before exiting
    printf("\e[0m");
    //if(lf_count%2==1)write(1,"\n\n",2);
    return 0;
}
