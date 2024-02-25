#include <chrono>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <omp.h> // Include OpenMP header

using namespace std::chrono;
using namespace std;

void randomVector(int vector[], int size) {
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100;
  }
}

int main() {
  unsigned long size = 100000000;
  srand(time(0));
  int *v1, *v2, *v3;
  auto start = high_resolution_clock::now();
  v1 = (int *)malloc(size * sizeof(int));
  v2 = (int *)malloc(size * sizeof(int));
  v3 = (int *)malloc(size * sizeof(int));
  randomVector(v1, size);
  randomVector(v2, size);

  #pragma omp parallel for // Use OpenMP parallel construct
  for (int i = 0; i < size; i++) {
    v3[i] = v1[i] + v2[i];
  }
  
  int total = 0; // Shared variable for the total sum

  #pragma omp parallel for reduction(+:total) // Use reduction clause to compute total sum
  for (int i = 0; i < size; i++) {
    total += v3[i];
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Total sum of elements in v3: " << total << endl;
  cout << "Time taken by function :" << duration.count() << " microseconds"
       << endl;
  return 0;
}
