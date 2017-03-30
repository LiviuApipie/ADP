#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 23                 /* number of rows in matrix A */
#define M 14                 /* number of columns in matrix A */
#define P 8                  /* number of columns in matrix B */

int main (int argc, char *argv[])
{
int	tid, nthreads, i, j, k;
double	a[N][M],           /* matrix A to be multiplied */
	b[M][P],           /* matrix B to be multiplied */
	c[N][P];           /* result matrix C */

//parallel regions
//a,b,c,nthreads are shared between threads
//tid,i,j,k are private to each thread
#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
  {
  tid = omp_get_thread_num(); //Returns the ID (0 to n-1) for the thread calling it
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();  //Returns the number of threads in team
    printf("Starting matrix with %d threads\n",nthreads);
    printf("Initializing matrices...\n");
    }

  /*** Initialize matrices ***/

  //loops are divided into equal chunks
  //this means the iterations of a loop are distributed among the threads in a roughly equal number of iterations.
  //if m iterations and N threads are in the thread team, each thread gets m/N iterations, and the compiler and runtime library correctly handles the case when m is not evenly divisible by N
  //with the static-even scheduling, you could minimize the chances of memory conflicts that can arise when more than one processor is trying to access the same piece of memory.
  //Loop iterations are divided into pieces of size chunk and then statically assigned to threads
  //If chunk is not specified, the iterations are evenly (if possible) divided contiguously among the threads.
  #pragma omp for schedule (static)
  for (i=0; i<N; i++)
    for (j=0; j<M; j++)
      a[i][j]= i+j;
  #pragma omp for schedule (static)
  for (i=0; i<M; i++)
    for (j=0; j<P; j++)
      b[i][j]= i*j;
  #pragma omp for schedule (static)
  for (i=0; i<N; i++)
    for (j=0; j<P; j++)
      c[i][j]= 0;

  printf("Thread %d starting matrix multiply...\n",tid);
  #pragma omp for schedule (static)
  for (i=0; i<N; i++)
    {
    printf("Thread=%d did row=%d\n",tid,i);
    for(j=0; j<P; j++)
      for (k=0; k<M; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }   /*** End of parallel region ***/

/*** Print results ***/
printf("Result Matrix:\n");
for (i=0; i<N; i++)
  {
  for (j=0; j<P; j++)
    printf("%6.2f   ", c[i][j]);
  printf("\n");
  }
printf ("Done.\n");

}
