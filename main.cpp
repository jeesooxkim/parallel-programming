#include <iostream>
#include <omp.h>
#include <stdio.h>

# define N 32

using namespace std;
// build via g++ -fopenmp -o main main.cpp

void printVar(int a[], int b, int c, int d, int m) {
    cout << "b= "<< b << ", c= " << c << ", d= " << d << ", m= " << m << endl;
    cout << "a= ";
    for (int i = 0; i < N; i++) {
        cout << a[i] << ", ";
    }
    cout << endl;
}

int main() {
    int i;
    int a[N];
    int b = 0, c = 0, d = 0, m = 0;

    cout << "Before parallel for loop:" << endl;
    printVar(a, b, c, d, m);

    // Begin parallel block
    // #pragma omp <construct> <clause()>
    #pragma omp parallel for default(none) private(i,b) firstprivate(c) lastprivate(d) shared(a,m) schedule(dynamic, 3) num_threads(1)
    for (i = 0; i < N; i++) {
        b = 100;
        d = 10;
        printf("Thread %d, iteration %d: b = %d, c = %d, d = %d, m = %d\n", omp_get_thread_num(), i, b, c, d, m);
        a[i] = omp_get_thread_num(); // a runtime library function to return a thread ID.
        b = omp_get_thread_num();
        c = omp_get_thread_num();
        d = omp_get_thread_num();
        m = omp_get_thread_num();
    } // end of the Parallel region.

    cout << "After parallel for loop:" << endl;
    printVar(a, b, c, d, m);

    return 0;
}
