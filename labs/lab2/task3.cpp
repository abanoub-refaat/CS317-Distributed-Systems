#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

void initialize(double **array, int n, int m);
void add(double **arr1, double **arr2, int n, int m);

int main()
{
    int m, n = 1000000;
    double **m1 = new double *[m];
    double **m2 = new double *[m];

    for (int i = 0; i < m; i++)
    {
        m1[i] = new double[n];
        m2[i] = new double[n];
    }

    initialize(m1, m, n);
    initialize(m2, m, n);

    auto start = high_resolution_clock::now();
    add(m1, m2, m, n);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time: " << duration.count();

    return 0;
}

void initialize(double **array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            array[i][j] = 1;
        }
    }
}

void add(double **arr1, double **arr2, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            arr1[i][j] = arr1[i][j] + arr2[i][j];
        }
    }
}
