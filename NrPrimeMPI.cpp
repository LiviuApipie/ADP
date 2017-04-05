#include <mpi.h>
#include <stdio.h>
#include <iostream>


#define LIMIT     37
#define FIRST     0

void print_prime_nr(int n);

int main(int argc, char *argv[])
{

	int   ntasks, rank, n, pcsum, mystart, stride;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	mystart = (rank * 2) + 1;
	stride = ntasks*2 ;


	if (rank == FIRST) {
		for (n = mystart; n <= LIMIT; n = n + stride) {
			print_prime_nr(n);

			}
		}

		printf("Done.");


	if (rank > FIRST) {
		for (n = mystart; n <= LIMIT; n = n + stride)
			print_prime_nr(n);

		}

	//system("PAUSE");
	MPI_Finalize();

}


void print_prime_nr(int n) {
	int i, k = 0;

	for (i = 1; i <= n/2; i++) {
		if (n%i == 0)
			k++;
	}

	if (k == 1)
		printf("\n%d ", n);

}
