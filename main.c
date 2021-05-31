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

	int warr[] = { 1, 2, 3, 4 };

	struct Chromosome population[NPOP];
	int done = 0;
	ga_init( NPOP,
			400,
			4,
			warr,
			0.5f,
			0.1f
		   );
			

	for (int i = 0; i < NPOP; ++i) {
		init_Chrmsm( population + i );
	}

	for (int n = 0; n < ITERATIONS; ++n) {
		printf("Run %d\n", n);

		for (int i = 0; i < NPOP; ++i) {
			eval_Fitness( population + i );
			printf("CHR %3d :", i);
			print_Chrmsm( population[i] );
		}

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
		if( done ) break;
		getchar();
	}


	return 0;
}
