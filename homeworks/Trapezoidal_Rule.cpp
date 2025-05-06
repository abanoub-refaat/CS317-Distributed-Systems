#include <mpi.h>
#include <iostream>
#include <cmath>
using namespace std;

// Function to integrate
double f(double x)
{
    return x * x; // Example function: f(x) = x^2
}

// Trapezoidal rule function
double trapezoidal_rule(double local_a, double local_b, int local_n, double h)
{
    double local_integral = (f(local_a) + f(local_b)) / 2.0;
    for (int i = 1; i < local_n; i++)
    {
        double x = local_a + i * h;
        local_integral += f(x);
    }
    local_integral *= h;
    return local_integral;
}

int main(int argc, char **argv)
{
    int myid, np, n = 1000;
    double a = 0.0, b = 3.0;
    double h, local_a, local_b, local_integral, total_integral;
    int local_n;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    h = (b - a) / n;
    local_n = n / np;

    local_a = a + myid * local_n * h;
    local_b = local_a + local_n * h;

    local_integral = trapezoidal_rule(local_a, local_b, local_n, h);

    if (myid == 0)
    {
        total_integral = local_integral;
        double received_integral;

        // Receive local integrals from other processes
        for (int i = 1; i < np; i++)
        {
            MPI_Recv(&received_integral, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
            total_integral += received_integral;
        }

        cout << "Approximate integral using Trapezoidal Rule: " << total_integral << endl;
    }
    else
    {
        // Send local_integral to process 0
        MPI_Send(&local_integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
