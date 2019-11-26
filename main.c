#include <stdio.h>
#include <stdlib.h>

int quick_select(int A[], int p, int r, int rank);
int random_partition(int A[], int p, int r);
void exchange(int* a, int* b);
int median_of_medians(int A[], int p, int r);
void insertion_sort(int A[], int from, int to);
int median_5(int A[], int left, int right);

int quick_select(int A[], int p, int r, int rank) {
    if (p == r) {
        return A[p];
    }
    int q = random_partition(A, p, r);
    int k = q - p + 1;
    printf("k: %d\n", k);
    if (rank == k) {
        return A[q];
    } else if (k < rank) {
        return quick_select(A, p, q - 1, k);
    } else {
        return quick_select(A, q + 1, r, k - rank);
    }
}

int random_partition(int A[], int p, int r) {
    int ind = median_of_medians(A, p, r);
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
    return i + 1;
}

void exchange(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int median_of_medians(int A[], int p, int r) {
    if (r - p < 5) {
        printf("finished\n");
        return median_5(A, p, r);
    }

    printf("P: %d\n", p);
    //int n = ceil(r - p + 1 / 5);
    for (int i = p; i < r; i += 5) {
        int right = i + 4;
        if (right > r)
            right = r;
        printf("i: %d, right: %d\n", i, right);
        int med5 = median_5(A, i, right);
        int index2 = p + ((i - p) / 5);
        printf("median: %d, index2: %d\n", med5, index2);
        exchange(&A[med5], &A[index2]);
        // printf("hello5\n");
    }
    //int z = n % 2 == 0 ? (n / 2) - 1 : n / 2;
    //int n = r - p + 1;
    //int z = n % 2 == 0 ? (n / 2) : n / 2 + 1;
    int z = (r - p) / 10 + p + 1;
    printf("dulo\n");
    return quick_select(A, p, p + (p - r / 5), z);
    // return quick_select(C, 0, n - 1, z);
}

int median_5(int A[], int left, int right) {
    int n = right - left + 1;
    //int z = n % 2 == 0 ? (n / 2) : n / 2 + 1;
    insertion_sort(A, left, right);
    if (n % 2 == 0)
        return (int)((left + right) / 2);
    else
        return (int)((left + right) / 2 + 1);
    // return z;
}

void insertion_sort(int A[], int from, int to) {
    for (int i = from; i < to; i++) {
        for (int j = i + 1; j > from && A[j] < A[j - 1]; j--) {
            exchange(&A[j - 1], &A[j]);
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int n;
        scanf("%d", &n);
        int A[n];
        for (int j = 0; j < n; j++)
            scanf("%d", &A[j]);
        int c = n / 2 + 1;
        printf("ceil %d\n", c);
        int rank = n % 2 == 0 ? (n / 2) : c;
        printf("Median: %d\n", quick_select(A, 0, n - 1, rank));
    }
}
