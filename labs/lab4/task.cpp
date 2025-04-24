#include <mpi.h>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
    int myid, np, number_of_tosses;
    int n = 100;
    int accum;
    double x, y, distance_squared;

    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int pi_estimate = 0;
    int startval = n * myid / np + 1;
    int endval = n * (myid + 1) / np;
    int number_in_circle = 0;

    srand(time(NULL));
    (double)rand() / RAND_MAX;

    for (int toss = 0; toss < number_of_tosses; toss++)
    {
        x = ((double)rand() / RAND_MAX) - 1;
        y = ((double)rand() / RAND_MAX) - 1;

        distance_squared = x * x + y * y;
        if (distance_squared <= 1)
            number_in_circle++;
    }

    if (myid != 0)
    {
        for (int i = 1; i < np; i++)
        {
            MPI_Send(&pi_estimate, 1, MPI_INT, i, 17, MPI_COMM_WORLD);
            MPI_Recv(&number_of_tosses, 1, MPI_INT, i, 17, MPI_COMM_WORLD, &status);
        }
    }
    else
    {
        cout << "Enter the number of tosses: " << endl;
        cin >> number_of_tosses;

        for (int i = 1; i < np; i++)
        {
            MPI_Recv(&accum, 1, MPI_INT, 0, 17, MPI_COMM_WORLD, &status);
            MPI_Send(&number_of_tosses, 1, MPI_INT, i, 17, MPI_COMM_WORLD);
            pi_estimate = pi_estimate + (4 * number_in_circle / ((double)number_of_tosses));
        }
        printf("The pi_estamate is: %d\n", pi_estimate);
    }

    MPI_Finalize();
    return 0;
}