#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[] = "file.txt";

    //writing to a file
    FILE *fw = fopen(filename, "w"); //open file to write
    if (fw == NULL) { //error handling
        perror("Error opening file for writing");
        return 1;
    }
    fprintf(fw, "Hello, World!\n");
    fclose(fw);

    // Reading from a file
    FILE *fr = fopen(filename, "r"); //open file to read
    if (fr == NULL) {
        perror("Error opening file for reading");
        return 1;
    }
    char line[100];
    while (fgets(line, sizeof(line), fr) != NULL) { //read each line
        printf("%s", line);
    }
    fclose(fr);

    return 0;
}
