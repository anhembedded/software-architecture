#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

// 1. Recursive Fibonacci (Heavy CPU/Stack depth)
long long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 2. Matrix Multiplication (Heavy CPU/Nested Loops)
void matrix_multiply() {
    const int size = 120;
    double **A = malloc(size * sizeof(double*));
    double **B = malloc(size * sizeof(double*));
    double **C = malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        A[i] = malloc(size * sizeof(double));
        B[i] = malloc(size * sizeof(double));
        C[i] = malloc(size * sizeof(double));
        for (int j = 0; j < size; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0.0;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for (int i = 0; i < size; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

// 3. Bubble Sort (Heavy CPU/O(N^2) sorting)
void bubble_sort() {
    const int size = 3000;
    int *arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    free(arr);
}

// 4. DJB2 Hash String Implementation
unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// 4b. Hashing Loop
void hash_loop() {
    const char *payload = "Profiling target started. Running workloads in a loop. Hashing this string continuously.";
    unsigned long dummy = 0;
    for (int i = 0; i < 50000; i++) {
        dummy += hash_string(payload);
    }
    volatile unsigned long prevent_opt = dummy;
    (void)prevent_opt;
}

// 5. Prime Number Search
void find_primes() {
    const int limit = 15000;
    int count = 0;
    for (int i = 2; i <= limit; i++) {
        int is_prime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) count++;
    }
    volatile int prevent_opt = count;
    (void)prevent_opt;
}

// 6. Fourier Transform Simulation (Trigonometric operations)
void fourier_transform_sim() {
    double result = 0.0;
    for (int i = 0; i < 100000; i++) {
        result += sin(i) * cos(i) + sin(i * 0.1);
    }
    volatile double prevent_opt = result;
    (void)prevent_opt;
}

// 7. String Reverse Helper
void reverse_in_place(char *str, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// 7b. String Reverse Loop
void string_reverse_loop() {
    char buf[256];
    for (int i = 0; i < 80000; i++) {
        for (int j = 0; j < 255; j++) {
            buf[j] = 'a' + (j % 26);
        }
        buf[255] = '\0';
        reverse_in_place(buf, 255);
    }
}

// 8. Binary Search Helper
int binary_search_impl(const int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// 8b. Binary Search Loop
void binary_search_loop() {
    int arr[1000];
    for (int i = 0; i < 1000; i++) {
        arr[i] = i * 2;
    }
    int sum = 0;
    for (int i = 0; i < 200000; i++) {
        sum += binary_search_impl(arr, 1000, i % 2000);
    }
    volatile int prevent_opt = sum;
    (void)prevent_opt;
}

// 9. Linear Search Helper
int linear_search_impl(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// 9b. Linear Search Loop
void linear_search_loop() {
    int arr[1000];
    for (int i = 0; i < 1000; i++) {
        arr[i] = i;
    }
    int sum = 0;
    for (int i = 0; i < 30000; i++) {
        sum += linear_search_impl(arr, 1000, 999);
    }
    volatile int prevent_opt = sum;
    (void)prevent_opt;
}

// 10. Recursive Factorial
long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 10b. Factorial Loop
void factorial_loop() {
    long long sum = 0;
    for (int i = 0; i < 500000; i++) {
        sum += factorial(15);
    }
    volatile long long prevent_opt = sum;
    (void)prevent_opt;
}

// 11. Simple Float Math Operations
void math_operations() {
    double val = 1.0;
    for (int i = 0; i < 2000000; i++) {
        val = val * 1.00001 + 0.05;
    }
    volatile double prevent_opt = val;
    (void)prevent_opt;
}

int main() {
    printf("User-mode CPU saturation target started. PID: %d\n", getpid());
    printf("Press Ctrl+C to stop.\n");
    printf("Executing user-mode workloads...\n");

    int iteration = 0;
    while (1) {
        iteration++;
        
        fibonacci(32);
        matrix_multiply();
        bubble_sort();
        hash_loop();
        find_primes();
        fourier_transform_sim();
        string_reverse_loop();
        binary_search_loop();
        linear_search_loop();
        factorial_loop();
        math_operations();
        
        printf("User iteration %d completed\n", iteration);
        fflush(stdout);
    }
    return 0;
}
