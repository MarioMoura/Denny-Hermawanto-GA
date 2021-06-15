 #include "ga.h"

int npop = 0;
int length = 0;
int *weights;
int total = 0;

double CrossRate = 0.0f;
double MutRate = 0.0f;

struct Chromosome *swap_pop;

/*
 * Probability Array
 */
double *P;

/*
 * Roulette Array
 */
double *C;

/*
 * Random rolls Array
 */
double *R;

int ga_init( int lcl_npop, int lcl_total, int lcl_length, int *lcl_weigths, double cr, double mr){
	npop = lcl_npop;
	length = lcl_length;
	total = lcl_total;
	weights = lcl_weigths;

	CrossRate = cr;
	MutRate = mr;

	swap_pop = malloc( npop * sizeof( struct Chromosome ));

	for (int i = 0; i < npop; ++i) {
		swap_pop[i].Gene = malloc( length * sizeof( int ));
		for (int n = 0; n < length; ++n) {
			swap_pop[i].Gene[n] = 0;
		}
	}

	P = malloc( npop * sizeof( double ));
	C = malloc( npop * sizeof( double ));
	R = malloc( npop * sizeof( double ));

}

int print_Chrmsm(struct Chromosome target){
	putchar('[');
	for (int i = 0; i < length; ++i) {
		printf("%3d, ", target.Gene[i]);
	}
	putchar(']'); printf(" fr: %4d", target.fitness_raw);
	printf(" f: %.4f\n", target.fitness);
	return 1;
}

int gen_value(){
	return (rand() % total * 2) - total;
}

int init_Chrmsm( struct Chromosome *target ){
	target->Gene = malloc( length * sizeof( int ));
	target->fitness = 0.0f;
	target->fitness_raw = 0;
	for (int i = 0; i < length; ++i) {
		target->Gene[i] = gen_value();
	}
	return 1;
}

int eval_Fitness( struct Chromosome *target ){
	int sum = 0;
	for (int i = 0; i < length; ++i) {
		sum += target->Gene[i] * weights[i];
	}
	sum -= total;
	if( sum < 0 ) sum *= -1;
	target->fitness_raw = sum;
	target->fitness = 1.0f / ( 1.0f + sum );
	return 1;
}

int gen_Random(){
	for (int i = 0; i < npop; ++i)
		R[i] = ( (double) rand() / RAND_MAX) ;
}

int set_roulette( struct Chromosome *population ){
	double lcl_total;
	for (int i = 0; i < npop; ++i){
		lcl_total += population[i].fitness;
	}

	for (int i = 0; i < npop; ++i)
		P[i] = population[i].fitness / lcl_total;

	C[0] = P[0];
	for (int i = 1; i < npop; ++i)
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
	int ret = npop-1;

	for (int i = npop-1; i >= 0; i--) {
		if( roll < C[i])
			ret = i;
	}
	return ret;
}

void cpy_Chrmsm( struct Chromosome *dest,struct Chromosome *src ){
	for (int i = 0; i < length; ++i) {
		dest->Gene[i] = src->Gene[i];
	}
	dest->fitness_raw = src->fitness_raw;
	dest->fitness= src->fitness;
}

int select_pop( struct Chromosome *population ){
	int roll = 0;
	for (int i = 0; i < npop; ++i){
		roll = eval_Roll( i );
		cpy_Chrmsm(swap_pop + i, population + roll );
	}

	/*putchar('\n');*/
	for (int i = 0; i < npop; ++i)
		/*population[i] = swap_pop[i];*/
		cpy_Chrmsm( population + i, swap_pop + i);
	return 1;
}

int cross( int first, int second, struct Chromosome *population){
	int roll = (rand() % 3) + 1;
	for (int i = roll; i < length; i++)
		population[first].Gene[i] = population[second].Gene[i];
}

int get_smaller(){
	double smallest = 100.0f;
	int ret_index = 0;

	for (int i = 0; i < npop; ++i) {
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
	int n_selected = 0;
	int *items = malloc( npop * sizeof( int ));
	for (int i = 0; i < npop; ++i)
		items[i] = 0;

	for (int i = 0; i < npop; ++i) {
		if( R[i] < CrossRate){
			items[ n_selected++ ] = i;
		}
	}

	if(n_selected == 0) return 0;
	if(n_selected == 1) return 0;
	if(n_selected == 2){
		cross( items[0],items[1], population);
		return 1;
	}
	for (int i = 0; i < n_selected; ++i) {
		int second = get_smaller();
		cross( items[i],second, population);
	}
	return 1;
}


void mutate( struct Chromosome *population){
	for (int i = 0; i < npop; ++i) {
		for (int j = 0; j < length; ++j) {
			double roll = ( (double) rand() / RAND_MAX) ;
			if( roll < MutRate ){
				population[i].Gene[j] = gen_value();
			}
		}
	}
}

int print_result( struct Chromosome target ){
	int i  = 0;
	char signal = ' ';

	if( weights[i] < 0 ) signal = '-';
	printf("Result: %c (%d)*%d ", signal, target.Gene[i++],
				weights[i] < 0 ? weights[i] * -1 : weights[i]
			);
	for (i = 1; i < length; ++i) {
		if( weights[i] < 0 ) signal = '-';
		else signal = '+';
		printf("%c (%d)*%d ",
				signal,
				target.Gene[i],
				weights[i] < 0 ? weights[i] * -1 : weights[i]
			  );
	}
	printf("= %d\n", total );
}

int check( struct Chromosome *population){
	int ret = 0;
	for (int i = 0; i < npop; ++i)
		if( population[i].fitness_raw == 0){
			ret = 1;
			print_result( population[i] );
		}
	return ret ;
}
