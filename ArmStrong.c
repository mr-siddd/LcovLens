#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Declare handler
void handle_signal(int sig) {
    printf("\nSignal %d received. Flushing coverage data and exiting...\n", sig);
    exit(0); // triggers gcov's .gcda flush
}

// Existing function prototypes...
bool isArmstrong(unsigned long long num);
unsigned int countDigits(unsigned long long num);
unsigned long long powerInt(unsigned int base, unsigned int exp);
void findArmstrongInRange(unsigned long long start, unsigned long long end);

int main() {
    // Register signal handler for SIGINT (Ctrl+C) and SIGTERM (kill -15)
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    unsigned long long num;
    int choice;

    printf("Armstrong Number Checker (with signal handling)\n");
    printf("==============================================\n");
    printf("1. Check a single number\n");
    printf("2. Find Armstrong numbers in a range\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    if (choice == 1) {
        printf("Enter number: ");
        if (scanf("%llu", &num) != 1) {
            printf("Invalid number input.\n");
            return 1;
        }
        if (num > 0 && isArmstrong(num)) {
            printf("%llu is an Armstrong number.\n", num);
        } else if (num == 0) {
            printf("0 is considered an Armstrong number.\n");
        } else if ((long long)num < 0) {
            printf("Negative numbers cannot be Armstrong numbers.\n");
        } else {
            printf("%llu is NOT an Armstrong number.\n", num);
        }
    } else if (choice == 2) {
        unsigned long long start, end;
        printf("Enter start of range: ");
        scanf("%llu", &start);
        printf("Enter end of range: ");
        scanf("%llu", &end);
        if (start > end) {
            printf("Invalid range: start > end.\n");
            return 1;
        }
        findArmstrongInRange(start, end);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

// Function to check Armstrong number
bool isArmstrong(unsigned long long num) {
    if (num == 0) return true;
    if (num < 0) return false; // Negative case handling

    unsigned int digits = countDigits(num);
    unsigned long long sum = 0, temp = num;

    while (temp > 0) {
        unsigned int digit = temp % 10;
        sum += powerInt(digit, digits);
        temp /= 10;
    }
    return (sum == num);
}

// Count digits in a number
unsigned int countDigits(unsigned long long num) {
    if (num == 0) return 1;
    unsigned int count = 0;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

// Calculate integer power (avoiding pow() floating point issues)
unsigned long long powerInt(unsigned int base, unsigned int exp) {
    unsigned long long result = 1;
    for (unsigned int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// Find Armstrong numbers in a range
void findArmstrongInRange(unsigned long long start, unsigned long long end) {
    bool found = false;
    printf("Armstrong numbers between %llu and %llu:\n", start, end);
    for (unsigned long long i = start; i <= end; i++) {
        if (isArmstrong(i)) {
            printf("%llu ", i);
            found = true;
        }
    }
    if (!found) {
        printf("None found in this range.");
    }
    printf("\n");
}

