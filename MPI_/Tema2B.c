
Scrieți un program care caută un element în interiorul unui matrice
b. Utilizați scatter pentru a trimite matrice. Dacă elementul este găsit de mai multe ori, imprimați toate pozițiile sale.
Utilizați MPI_Gather pentru trimiterea înapoi a pozițiilor.







int main(int argc, char *argv[])
{
	int rank, size, segmentSize, index, found[SIZE], finalFound[SIZE + 10], poz;
	int arr[SIZE], segment[SIZE];
	bool ok = false;

	srand(time(NULL));

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	segmentSize = SIZE / size;
	if (SIZE % size != 0) {
		++segmentSize;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0) {
		printf("Array elements are:\n");
		for (int i = 0; i < SIZE; i++) {
			arr[i] = rand() % 100;
			printf("%d, ", arr[i]);
			finalFound[i] = -1;
		}
		arr[35] = 95;
		arr[98] = 95;
	}

	MPI_Scatter(arr, segmentSize, MPI_INT, segment, segmentSize, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < segmentSize; i++)
		found[i] = 0;

	index = 0;
	for (int i = 0; i < segmentSize; i++) {
		if (segment[i] == KEY) {
			found[index++] = i + rank * segmentSize;
		}
	}

	MPI_Gather(found, segmentSize, MPI_INT, finalFound, segmentSize, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		for (int i = 0; i < SIZE + 10; i++)
		if (finalFound[i] > 0)
			ok = true;
		if (ok) {
			printf("\n\nNumber found on the follwing position(s): ");
			for (int i = 0; i < SIZE + 10; i++)
			if (finalFound[i] != 0)
				printf("%d ", finalFound[i]);
		}


	}


	MPI_Finalize();
	return 0;
}