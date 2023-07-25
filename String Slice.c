#include <stdio.h>
#include <string.h>

void slice(char *str, int m, int n) {
    if (str == NULL || strlen(str) == 0) {
        printf("Invalid input string.\n");
        return;
    }

    int length = strlen(str);

    // Check if m and n are within bounds
    if (m < 0 || m >= length || n < 0 || n >= length || m > n) {
        printf("Invalid start and/or end positions.\n");
        return;
    }

    // Calculate the size of the sliced string
    int sliceSize = n - m + 1;

    // Create a new buffer to hold the sliced string
    char slicedStr[sliceSize + 1]; // +1 for the null-terminator

    // Copy characters from the input string to the sliced string buffer
    int i, j = 0;
    for (i = m; i <= n; i++) {
        slicedStr[j] = str[i];
        j++;
    }
    slicedStr[j] = '\0'; // Null-terminate the sliced string

    // Copy the sliced string back to the original input string
    strcpy(str, slicedStr);

    // No need to free memory as we are using a local buffer
}

int main() {
    char inputString[100];
    int m, n;

    printf("Enter the input string: ");
    scanf("%[^\n]%*c", inputString); // Take input string that may contain spaces

    printf("Enter the start position (m): "); // 0 is the 1st position, 1 is the 2nd position etc.
    scanf("%d", &m);

    printf("Enter the end position (n): "); // 0 is the 1st position, 1 is the 2nd position etc.
    scanf("%d", &n);

    slice(inputString, m, n); // 0 is the 1st position, 1 is the 2nd position etc.

    printf("Sliced string: %s\n", inputString);

    return 0;
}
