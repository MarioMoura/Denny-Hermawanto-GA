#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Chromosome {
	int *Gene;
	int fitness_raw;
	double fitness;
};

int ga_init( int lcl_npop, int lcl_total, int lcl_length, int *lcl_weigths, double cr, double mr);
int print_Chrmsm(struct Chromosome target);
int init_Chrmsm( struct Chromosome *target );
int eval_Fitness( struct Chromosome *target );
int set_roulette( struct Chromosome *population );
int select_pop( struct Chromosome *population );
int crossOver(struct Chromosome *population);
int cross( int first, int second, struct Chromosome *population);
void mutate(struct Chromosome *population);
int check( struct Chromosome *population);
int gen_Random();
