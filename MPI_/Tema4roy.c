//Matricea costurilor optime



#include "mpi.h"
#include <iostream>
using namespace std;

#define N 6

int main(int argc, char *argv[])
{
	int a[N][N] = {
		{ 1, 2, 5, 979, 999, 999 },
		{ 999, 12, 4, 2, 999, 3 },
		{ 999, 999, 0, 8, 999, 999 },
		{ 999, 999, 999, 0, 3, 999 },
		{ 999, 999, 2, 999, 8, 3 },
		{ 999, 5, 999, 2, 0,8 }
	};
	int result[N][N];
	int numprocs, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);



	for (int k = 0; k < N; k++)
	{
		for (int i = rank; i < N; i = i + numprocs)
		{
			for (int j = 0; j < N; j++)
			{
				if (a[i][j] > a[i][k] + a[k][j])
					a[i][j] = a[i][k] + a[k][j];
			}
		}
		//min a=result, matricea costurilor minime
		MPI_Reduce(a, result, N*N, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
		if (rank == 0) {
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					a[i][j] = result[i][j];
			MPI_Bcast(a, N*N, MPI_INT, 0, MPI_COMM_WORLD);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}

	if (rank == 0){
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++)
				cout << a[i][j] << " ";
			cout << "\n";
		}

	}

	MPI_Finalize();


	system("pause");
	return 0;
}
