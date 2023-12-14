#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ascending(int* data, const long long N) {
    for (long long i = 0; i < N - 1; i++) {
        data[i] = i + 1;
    }
    data[N - 1] = 0;
}


void descending(int* data, const long long N) {
    data[0] = N - 1;
    for (long long i = 1; i < N; i++) {
        data[i] = i - 1;
    }
}


void random(int* data, const long long N) {
    int temp;
    long long i = N;
    srand(time(NULL));
    while (i > 1) {
        i--;
        int j = rand() % i;
        temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
}


int test(int* data, const long long N, const int K, void (*gen)(int* data, const long long N), FILE* out) {
    gen(data, N);
    int k;
    long long i;
    for (k = 0, i = 0; i < N; i++) {
        k = data[k];
    }
    unsigned long long start = __builtin_ia32_rdtsc();
    for (k = 0, i = 0; i < N * K; i++) {
        k = data[k];
    }
    unsigned long long end = __builtin_ia32_rdtsc();
    fprintf(out, "N = %lld, Tick = %llu\n", N * 4, (end - start) / N / K);
    return k;
}


int main() {
    const long long Nmin = 1024 / sizeof(int);
    const long long Nmax = 32 * 1024 * 1024LL / sizeof(int);
    const int K = 10;

    int* data = (int*)malloc(Nmax * sizeof(int));

    FILE* out = fopen("time.txt", "w");

    for (int N = Nmin; N <= Nmax; N *= 2) {
        fprintf(out, "N = %d\n", N);
        fprintf(out, "Asc: ");
        test(data, N, K, ascending, out);
        fprintf(out, "Desc: ");
        test(data, N, K, descending, out);
        fprintf(out, "Random: ");
        test(data, N, K, random, out);
        fprintf(out, "\n");
    }
    fclose(out);
    free(data);
    return 0;
}
