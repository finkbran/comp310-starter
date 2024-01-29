#include <stdio.h>
int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int sum = 0;
    double average;
    int length = sizeof(numbers) / sizeof (numbers[0]); //divide the size in bytes of the array by the size in bytes of an element to get the number of elements in the array
    for (int i = 0; i < length; ++i) {
        sum += numbers[i]; //runnign total of elements in array
    }
    average = (double)sum / length;
    printf("Sum: %d\n", sum);
    printf("Average: %f\n", average);
    return 0;

}