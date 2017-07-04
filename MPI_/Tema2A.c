Scrieți un program care caută un element în interiorul unui matrice.
A. Utilizați MPI_Broadcast pentru trimiterea matricei. Dacă elementul este găsit, imprimați maximul
Indice de poziție. 
Pentru a calcula poziția maximă, trebuie să utilizați MPI_Reduce.








#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define SIZE 100
#define value 42


int main(int argc, char *argv[])
{
    int rank, size, segmentSize, startP, endP, found = -1, finalFound = -2;
    int array[SIZE];

    srand(time(NULL) + 1);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        for (int i = 0; i < SIZE; i++)
        {
            array[i] = rand() % 100;
        }
    }

    segmentSize = SIZE / size;//each one receives its part of the array
    if (SIZE % size != 0)
        segmentSize++;

    MPI_Bcast(array, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    startP = rank * segmentSize;
    endP = startP + segmentSize - 1;

    for (int i = startP; i <= endP; i++)
    {

        if (array[i] == value)
        {
            found = i;
        }
    }

    MPI_Reduce(&found, &finalFound, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        if (finalFound == -2)
            printf("\nThe number wasn`t found\n");
        else printf("\nNumber found on position %d", finalFound);
    }


    MPI_Finalize();

}