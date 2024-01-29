#include <stdio.h>

int factorial(int n) {
    if (n <= 0) {
        return 1;
    } else {
        return n * factorial(n - 1); //multiply current number n times n - 1 until n is 0
    }
}

int main() {
    int number = 5;
    printf("Factorial of %d is: %d\n", number, factorial(number));
    return 0;
}
