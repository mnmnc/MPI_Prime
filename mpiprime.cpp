#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <ctime>
#include "math.h"
#include "mpi.h"

using namespace std;

// FUNCTIONS DECLARATIONS
int main(int argc, char *argv[]);
vector<double> prime(int n, int id, int number_of_processes);

int main(int argc, char * argv[]){

	// VARIABLES
	int number, factor, i, id;
	int end, begin, user_given, number_of_processes;

	double primes, sums, partial, psum;
	vector<double> vpartial;

	// CHANGE THIS
	user_given = 100000;

	begin = user_given;
	end = begin + 1;
	factor = 2;

	// CAPTURE TIME
	clock_t begin_pt = clock();

	// INIT
	MPI_Init(&argc, &argv);

	// GET NUMBER OF PROCESSESS
	MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);

	// GET PROCESS ID
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	// BEGIN
	number = begin;

	// BROADCAST
	MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// CALCULATION
	vpartial = prime(number, id, number_of_processes);

	psum = vpartial.at(0);
	partial = vpartial.at(1);

	// REDUCE TO COMBINE PARTIAL SUMS AND NUMBER OF PRIMES
	MPI_Reduce(&partial, &primes, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&psum, 	 &sums,   1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (id == 0){
		cout << " Number given:\t\t" << user_given << endl;
		cout << " Number of primes:\t" << primes << endl;
		printf( " Sum of primes:\t\t%llu\n", (long long)sums );
		cout << " Sum mod 123:\t\t" << fmod(sums, 123) << endl;
		cout << " Time spent:\t\t" << double(clock() - begin_pt) / CLOCKS_PER_SEC << endl;
	}

	// TERMINATING MPI
	MPI_Finalize();

	return 0;
}

vector<double> prime(int n, int id, int number_of_processes){

	// LOCAL VARIABLES
	int i, j, check;
	double count, sum;
	vector<double> result;

	// PARTIAL RESULT VARIABLES
	count = 0;
	sum = 0;

	for(i = 2 + id; i <= n; i = i + number_of_processes){
		check = 1;
		for (j = 2; j < i; ++j){
			if ((i % j) == 0){
				// i IS NOT PRIME
				check = 0;
				break;		
			}
		}
		if (check == 1){
			sum += i;
		}
		count = count + check;
	}

	// CREATE RESULT
	result.push_back(sum);
	result.push_back(count);

	return result;
}