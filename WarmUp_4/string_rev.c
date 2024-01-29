#include <stdio.h>

int main() {
    char str[] = "Hello";
    int length = 0;

    // calculate length of the string
    while (str[length] != '\0') {
        length++; // get the length of the string
    }

    //reverse the string
    for (int i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

    // rrint the reversed string
    printf("%s\n", str);
    return 0;
}
