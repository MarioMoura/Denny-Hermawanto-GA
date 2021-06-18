#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "ga.h"

#define ITERATIONS 100000

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#ifndef NPOP
#define NPOP 20
#endif /* ifndef NPOP */

#ifndef CSV_OUT
#define CSV_OUT STR(NPOP)
#endif /* ifndef CSV_OUT */

int main(){
	srand(time(0));

	FILE *csv_out = fopen("data/"CSV_OUT".csv", "a");

	struct timespec begin, end;
	int msbegin, msend;
	double time;

	unsigned int run = 0;

	// 1a + 2b + 3c + 4d - 5e + 6f + 7g + 8h + 9i + 10j + 11k + 12l = 15000
	int warr[] = { 1, 2, 3, 4 , -5, 6, 7, 8, 9, 10, 11, 12};
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

		for (int i = 0; i < NPOP; ++i)
			eval_Fitness( population + i );


		set_roulette( population );
		select_pop( population );

		crossOver( population );

		mutate( population );

		done = check( population );
		if( done ){
			clock_gettime(CLOCK_REALTIME, &end);
			time = (double) ( end.tv_sec - begin.tv_sec) +
				(double)( end.tv_nsec - begin.tv_nsec)/ 1000000000;

			printf("%d,%d,%f\n", NPOP, n+1, time);
			fprintf(csv_out,"%d,%d,%f\n", NPOP, n+1, time);
			return 0;
		}
	}
	puts("Result not found!");


	return 0;
}
