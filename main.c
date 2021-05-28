#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define ITERATIONS 200

#define NPOP 10

// Length of the equation
#define LENGTH 5
// Weights of the variables
int weights[] = { 1, 2, 3, 4, -5};
int total = 35;

double CrossRate = 0.80f;
double MutRate = 0.1f;

// Static Variables
struct Chromosome {
	int Gene[LENGTH];
	int fitness_raw;
	double fitness;
};
struct Chromosome swap_pop[NPOP];

/*
 * Probability Array
 */
double P[NPOP];

/*
 * Roulette Array
 */
double C[NPOP];

/*
 * Random rolls Array
 */
double R[NPOP];

int print_Chrmsm(struct Chromosome target){
	putchar('[');
	for (int i = 0; i < LENGTH; ++i) {
		printf("%3d, ", target.Gene[i]);
	}
	putchar(']'); printf(" fr: %4d", target.fitness_raw);
	printf(" f: %.4f\n", target.fitness);
	return 1;
}

int gen_value(){
	return (rand() % total) + 1;
}

int init_Chrmsm( struct Chromosome *target ){
	for (int i = 0; i < LENGTH; ++i) {
		target->Gene[i] = gen_value();
	}
	return 1;
}

int eval_Fitness( struct Chromosome *target ){
	int sum = 0;
	for (int i = 0; i < LENGTH; ++i) {
		sum += target->Gene[i] * weights[i];
	}
	sum -= total;
	if( sum < 0 ) sum *= -1;
	target->fitness_raw = sum;
	target->fitness = 1.0f / ( 1.0f + sum );
	return 1;
}

int gen_Random(){
	for (int i = 0; i < NPOP; ++i)
		R[i] = ( (double) rand() / RAND_MAX) ;
}

int set_roulette( struct Chromosome *population ){
	double total;
	for (int i = 0; i < NPOP; ++i)
		total += population[i].fitness;

	for (int i = 0; i < NPOP; ++i)
		P[i] = population[i].fitness / total;

	C[0] = P[0];
	for (int i = 1; i < NPOP; ++i)
		C[i] = P[i] + C[i-1];

	gen_Random();

	return 1;
}

int eval_Roll( int index ){
	/*
	* recieves: index of roll
	* returns: the chosen gene
	*/
	double roll = R[ index ];
	int ret = NPOP-1;

	for (int i = NPOP-1; i >= 0; i--) {
		if( roll < C[i])
			ret = i;
	}
	return ret;
}

int select_pop( struct Chromosome *population ){
	for (int i = 0; i < NPOP; ++i)
		swap_pop[i] = population[ eval_Roll( i ) ];

	for (int i = 0; i < NPOP; ++i)
		population[i] = swap_pop[i];
	return 1;
}

int cross( int first, int second, struct Chromosome *population){
	int roll = (rand() % 3) + 1;
	for (int i = roll; i < LENGTH; i++)
		population[first].Gene[i] = population[second].Gene[i];

	printf("[%dx%d;%d]; ", first, second, roll);
}

int get_smaller(){
	double smallest = 100.0f;
	int ret_index = 0;

	for (int i = 0; i < NPOP; ++i) {
		if( R[i] < smallest){
			smallest = R[i];
			ret_index = i;
		}
	}
	R[ ret_index ] = 100.f;

	return ret_index;
}

int crossOver(struct Chromosome *population){
	gen_Random();
	putchar('\n');
	int n_selected = 0;
	int items[ NPOP ]= { 0 };

	for (int i = 0; i < NPOP; ++i) {
		if( R[i] < CrossRate){
			items[ n_selected++ ] = i;
		}
	}
	/*for (int i = 0; i < NPOP; ++i) {*/
		/*printf("%f\n", R[i]);*/
	/*}*/

	if(n_selected == 0) return 0;
	if(n_selected == 1) return 0;
	if(n_selected == 2){
		cross( items[0],items[1], population);
		putchar('\n');
		return 1;
	}
	for (int i = 0; i < n_selected; ++i) {
		int second = get_smaller();
		cross( items[i],second, population);
	}
		putchar('\n');
	return 1;
}

void mutate( struct Chromosome *population){
	putchar('\n');
	for (int i = 0; i < NPOP; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
			double roll = ( (double) rand() / RAND_MAX) ;
			if( roll < MutRate ){
				population[i].Gene[j] = gen_value();
				printf("{%d>%d}; ", j, i);
			}
		}
	}
	putchar('\n');
}

int print_result( struct Chromosome target ){
	printf(" 1*%d  2*%d  3*%d  4*%d \n");
}

int check( struct Chromosome *population){
	int ret = 0;
	for (int i = 0; i < NPOP; ++i)
		if( population[i].fitness_raw == 0)
			return 1;
	return 0;
}

int main(){
	srand(time(0));

	struct Chromosome population[NPOP];

	for (int i = 0; i < NPOP; ++i) {
		init_Chrmsm( population + i );
	}

	for (int n = 0; n < ITERATIONS; ++n) {
		printf("Run %d\n", n);

		for (int i = 0; i < NPOP; ++i) {
			eval_Fitness( population + i );
		}

		set_roulette( population );

		select_pop( population );

		crossOver( population );

		mutate(population);

		for (int i = 0; i < NPOP; ++i) {
			eval_Fitness( population + i );
		}
		for (int i = 0; i < NPOP; ++i) {
			printf("CHR %d :", i);
			print_Chrmsm( population[i] );
		}
		if( check( population ) ) break;
	}

	puts("eae");

	return 0;
}
