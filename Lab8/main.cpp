#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

unsigned long long rdtsc() {
    unsigned int low, high;
    asm volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((unsigned long long)high << 32) | low;
}

void direct(vector<int> Array, const long long N)
{
    for (long long i = 0; i < N; i++) {
        Array[i] = i + 1;
    }
    Array[N - 1] = 0;
}

void reverse(vector<int> Array, const long long N) 
{
    Array[0] = N - 1;
    for (long long i = 1; i < N; i++) {
        Array[i] = i - 1;
    }
}

void random(vector<int> Array, const long long N) 
{
    int temp;
    long long i = N;
    srand(time(NULL));
    while (i > 1) {
        i--;
        int j = rand() % i;
        temp = Array[i];
        Array[i] = Array[j];
        Array[j] = temp;
    }
}

int test(vector<int> Array, const long long N, const int K, 
    void (*create_function)(vector<int> Array, const long long N), ofstream& out)
{
    create_function(Array, N);
    int k;
    long long i;
    for (k = 0, i = 0; i < N; i++) 
    {
        k = Array[k];
    }
    //unsigned long long start = __builtin_ia32_rdtsc();
    unsigned long long start = rdtsc();
    for (k = 0, i = 0; i < N * K; i++) 
    {
        k = Array[k];
    }
    //unsigned long long end = __builtin_ia32_rdtsc();
    unsigned long long end = rdtsc();
    out << " N = " << N * 4 << ", "
        << "Tick = " << ((end - start)) << '\n';
         
    return k;
}

int main() 
{
    ofstream out("time.txt");
    if (!out) {
       return 0;
    }
    const long long Nmin = 1024 / sizeof(int);
    const long long Nmax = 32 * 1024 * 1024LL / sizeof(int);
    const int K = 10;

    vector<int> Array(Nmax);

    for (int N = Nmin; N <= Nmax; N *= 2) 
    {
        out << "N = " << N << "\n";
        out << "direct: ";
        test(Array, N, K, direct, out);
        out << "reverse: ";
        test(Array, N, K, reverse, out);
        out << "random: ";
        test(Array, N, K, random, out);
        out << '\n';
    }
    out.close();
}
