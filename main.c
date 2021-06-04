#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "ga.h"

#define ITERATIONS 100000

#define NPOP 20

int main(){
	srand(time(0));

	struct timespec begin, end;
	int msbegin, msend;

	unsigned int run = 0;

	int warr[] = { 1, 2, 3, 4 , -5, 6, 7, 8, 9};
	int len = sizeof(warr) / sizeof(int);
	int tot = 15000;

	double cr = 0.8f;
	double mr = 0.1f;

	struct Chromosome population[NPOP];
	int done = 0;
	ga_init( NPOP,  // Population Number
			tot,	// Total
			len,	// Equation Length
			warr,	// Weigth Array
			cr,		// Reproduction Rate
			mr		// Mutation Rate
			);


	for (int i = 0; i < NPOP; ++i) {
		init_Chrmsm( population + i );
	}
	clock_gettime(CLOCK_REALTIME, &begin);
	for (int n = 0; n < ITERATIONS; ++n) {
		printf("Run %d\n", run = n+1);

		for (int i = 0; i < NPOP; ++i)
			eval_Fitness( population + i );


		set_roulette( population );
		select_pop( population );

		crossOver( population );

		mutate(population);

		for (int i = 0; i < NPOP; ++i)
			eval_Fitness( population + i );
		for (int i = 0; i < NPOP; ++i) {
			printf("CHR %3d :", i);
			print_Chrmsm( population[i] );
		}

		done = check( population );
		if( done ){
			clock_gettime(CLOCK_REALTIME, &end);
			printf("Run %d in %f seconds\n",
					run,
					(double) ( end.tv_sec - begin.tv_sec) + (double)( end.tv_nsec - begin.tv_nsec)/ 1000000000
				);
			return 0;
		}
	}
	puts("Result not found!");


	return 0;
}
