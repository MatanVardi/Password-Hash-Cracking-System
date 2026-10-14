#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 50

int main() {

    FILE *wordlistPtr;
    char line[MAX_LINE_LENGTH];

    char file [] = "wordlist.txt";
    wordlistPtr = fopen(file, "r");

    if (wordlistPtr == NULL) {
        printf("The file named %s doesn't exist", file);
    }

    while (fgets(line, MAX_LINE_LENGTH, wordlistPtr)) {
        printf("%s", line);
    }





    return 0;
}