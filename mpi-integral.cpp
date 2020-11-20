#include <iostream>
#include <cstdlib>
#include <cmath>
#include "mpi.h"

double integral(const double &A, const double &B, const int &N, int &pid, int &nproc);
void sumar(double sum, int pid, int nproc);
void print(double sum, int pid, int nproc);

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  const double A = 0.0;
  const double B = 10.0;
  const double N = 1000000;
  int pid = 0, nproc = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  
  double start = MPI_Wtime();
  double sum = integral(A, B, N, pid, nproc);
  sumar(sum, pid, nproc);
  double end = MPI_Wtime();
  if (0 == pid) {
    std::cout << end-start << "\n";
  }
  //print(sum, pid, nproc);

  MPI_Finalize();
  return 0;
}

double integral(const double &A, const double &B, const int &N, int &pid, int &nproc)
{
  double suma = 0.0;
  const double dx = (B-A)/N;
  const double l = N/nproc;
  
  for(int i = pid*l; i < pid*l + l; i++){
    suma += dx*std::pow(i*dx, 2);
  }
  return suma;
}

void sumar(double sum, int pid, int nproc)
{
  int tag = 0;
  if (0 == pid) {
    double suma = sum;
    double sumaux = 0.0;
    for (int src = 1; src < nproc; ++src) {
      MPI_Recv(&sumaux, 1, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      suma += sumaux;
    }
    std::cout << suma << std::endl;
  } else {
    int dest = 0;
    MPI_Send(&sum, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  }
}

void print(double sum, int pid, int nproc)
{
  int tag = 0;
  if (0 == pid) {
    std::cout << pid << "\t" << sum << std::endl;
    double sumaux = 0.0;
    for (int src = 1; src < nproc; ++src) {
      MPI_Recv(&sumaux, 1, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      std::cout << src << "\t" << sumaux << std::endl;
    }
  } else {
    int dest = 0;
    MPI_Send(&sum, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  }
}
