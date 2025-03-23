#include <mpi.h>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

double f(double x)
{
    return x * x;
}

int main(int argc, char **argv)
{
    int myid, np, n = 1000;
    double a = 0.0, b = 3.0;
    double h, local_a, local_b, local_integral, total_integral = 0.0;
    int local_n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    h = (b - a) / n;
    local_n = n / np;

    // Define local start and end points
    local_a = a + myid * local_n * h;
    local_b = local_a + local_n * h;

    local_integral = trapezoidal_rule(local_a, local_b, local_n, h);

    MPI_Reduce(&local_integral, &total_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myid == 0)
    {
        cout << "Approximate integral using Trapezoidal Rule: " << total_integral << endl;
    }

    MPI_Finalize();
    return 0;
}

int trapezoidal_rule(double local_a, double local_b, int local_n, double h)
{
    double trapezoidal_rule(double local_a, double local_b, int local_n, double h)
    {
        double local_integral = 0.0;
        local_integral = (f(local_a) + f(local_b)) / 2.0;
        for (int i = 1; i < local_n; i++)
        {
            double x = local_a + i * h;
            local_integral += f(x);
        }
        local_integral *= h;
        return local_integral;
    }
}