#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define col 6

void initVec(int a[col], int b[col], int sol[col], int sol_mpi[col]) {
  for (int i = 0; i < col; i++)
    a[i] = b[i] = i * 2;

  for (int i = 0; i < col; i++)
    sol[i] = sol_mpi[i] = 0;
}

void showVector(int a[col]) {
  for (int i = 0; i < col; i++)
    printf("%d  ", a[i]);
  printf("\n");
}

void vecAdd(int a[col], int b[col], int sol[col]) {
  for (int i = 0; i < col; i++)
    for (int j = 0; j < col; j++)
      sol[i] = a[i] + b[i];
}

int check(int a[col], int b[col]) {
  for (int i = 0; i < col; i++)
    if (a[i] != b[i])
      return 0;
  return 1;
}


int main() {
  MPI_Init(NULL, NULL);

  int a[col], b[col], sol[col], sol_mpi[col];
  double start = 0, time_seq = 0, time_omp = 0;
  double t1, t2;

  initVec(a, b, sol, sol_mpi);

  t1 = MPI_Wtime();
  vecAdd(a, b, sol);
  t2 = MPI_Wtime();
  printf( "Elapsed time is %f\n", t2 - t1 );

  // if(check(sol, sol_Open)) {
  //   printf("%s %f\n", "Time Sequential: ", time_seq);
  //   printf("%s %f\n", "Time OMP: ", time_omp);
  // }
  // else printf("%s\n", "Wrong answer");
  showVector(a);
  showVector(b);
  showVector(sol);

  MPI_Finalize();
  return 0;
}
