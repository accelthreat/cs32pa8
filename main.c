#include <stdio.h>
#include <stdlib.h>

int quick_select(int A[], int p, int r, int rank);
int random_partition(int A[], int p, int r);
void exchange(int* a, int* b);
int median_of_medians(int A[], int p, int r);
void insertion_sort(int A[], int from, int to);

int quick_select(int A[], int p, int r, int rank) {
    if (p == r) {
        return A[p];
    }
    int q = random_partition(A, p, r);
    int k = q - p + 1;
    if (rank == k) {
        return A[q];
    } else if (k < rank) {
        return quick_select(A, p, q - 1, k);
    } else {
        return quick_select(A, q + 1, r, k - rank);
    }
}

int random_partition(int A[], int p, int r) {
    int median = median_of_medians(A, p, r);
    int ind = 0;
    exchange(&A[ind], &A[r]);
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i = i + 1;
            exchange(&A[i], &A[j]);
        }
    }
    exchange(&A[i + 1], &A[r]);
}

void exchange(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int median_of_medians(int A[], int p, int r) {
    int n = r / 5;
    int C[n];
    for (int i = 0; i < n; i++) {
        int B[5];
        int s = p + (5 * i);
        int e = floor(s + 5, p + r - 1);
        for (int j = s; j <= e; j++) {
            B[j - s] = A[j];
        }
        insertion_sort(B, 0, e - s);
        C[i] = (e - s) % 2 == 0 ? (e - s / 2) : (e - s / 2) + 1;
    }
    int z = n % 2 == 0 ? n / 2 : n / 2 + 1;
    return quick_select(C, 0, n, z);
}

void insertion_sort(int A[], int from, int to) {
    for (int i = from; i < to; i++) {
        for (int j = i + 1; j > from && A[j] < A[j - 1]; j--) {
            int temp = A[j - 1];
            A[j - 1] = A[j];
            A[j] = temp;
        }
    }
}
