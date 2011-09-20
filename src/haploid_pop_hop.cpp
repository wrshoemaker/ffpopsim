/*
 * haploid_pop_hop.cpp
 *
 * Created on: Sept 19, 2011
 * Author: Fabio Zanini
 */
#include "popgen.h"


haploid_pop_hop::haploid_pop_hop() : haploid_gt_dis() {}


haploid_pop_hop::~haploid_pop_hop() {
 free_mem();
}


haploid_pop_hop::haploid_pop_hop(int nloci, double popsize, int rngseed) {
 mem=false;
 free_recombination=true;
 outcrossing_rate=0.0;
 generation=0;
 setup(nloci, popsize, rngseed);
}


int haploid_pop_hop::setup(int nloci, double popsize, int rngseed) {
 number_of_loci=nloci;
 population_size=popsize;
 if (rngseed==0) seed=time(NULL);
 else seed=rngseed;
 return allocate_mem(); // <-----------	SUBCLASS METHOD CALLED!
}


int haploid_pop_hop::allocate_mem() {
 // call superclass method
 int sc_return = haploid_gt_dis::allocate_mem();
 if (sc_return)
  return sc_return;

 mem=false;	// we are not finished yet

 // allocate hopping rates (number_of_loci exists already at this stage)
 hopping_rates=new double*[(1<<number_of_loci)];
 for (int gt=0; gt < (1<<number_of_loci); gt++) {
  hopping_rates[gt]=new double [number_of_loci];
 }

 mem=true;

 // set hopping rates to zero
 return set_hopping_rate(0.0);
}


int haploid_pop_hop::free_mem() {
 if (mem) {
  // free hopping_rates
  for (int gt=0; gt < (1<<number_of_loci); gt++) {
   delete [] hopping_rates[gt];
  }
  delete [] hopping_rates;
 
  // call superclass method (inverse order to allocation)
  return haploid_gt_dis::free_mem();
 }
}


int haploid_pop_hop::set_hopping_rate(double h) {
/*
 * Generic hopping rate, mostly for testing purposes
*/
 if (!mem){
  cerr<<"haploid_pop_hop::set_hopping_rate(): allocate memory first!\n";
  return HG_MEMERR;
 }
 for (int gt=0; gt < (1<<number_of_loci); gt++) {
  for (int locus = 0; locus<number_of_loci; locus++){
   hopping_rates[gt][locus] = h;
  }
 }
 return 0;
}


int haploid_pop_hop::set_hopping_rate(double** h) {
/*
 * Genotype- and neighbour specific hopping rate. This must be a (2^L x L) matrix, i.e.
 * every h[i] is an L vector. h[i][j] is the hopping rate FROM genotype i TO the
 * neighbour with inversed j-th spin.
*/
 if (!mem){
  cerr<<"haploid_pop_hop::set_hopping_rate(): allocate memory first!\n";
  return HG_MEMERR;
 }
 // No dimensional check on h... please BE CAREFUL!
 for (int gt=0; gt < (1<<number_of_loci); gt++){
  for (int locus=0; locus<number_of_loci; locus++){
   hopping_rates[gt][locus] = h[gt][locus];
  }
 }
 return 0;
}


int haploid_pop_hop::hop() {
 // I can recycle the mutants attribute for my goals, since a pop does not mutate and hop at the same time
 mutants.set_state(HC_FUNC);
 population.set_state(HC_FUNC);
 for (int i=0; i<(1<<number_of_loci); i++) {
  mutants.func[i]=0;
  for (int locus=0; locus<number_of_loci; locus++) {
   if (i&(1<<locus)){			// In this case, i[locus] = 1, thus his neighbour is i-(1<<locus)
    mutants.func[i]+= hopping_rates[i-(1<<locus)][locus] * population.func[i-(1<<locus)] - hopping_rates[i][locus] * population.func[i];
    //							 ^							   ^
    //		INWARDS FLOW FROM THE NEIGHBOUR	_________|			 OUTWARDS FLOW TO THE NEIGHBOUR	___|
    //
   } else {				// In this case, i[locus] = 0, thus its neighbour is i+(1<<locus)
    mutants.func[i]+= hopping_rates[i+(1<<locus)][locus] * population.func[i+(1<<locus)] - hopping_rates[i][locus] * population.func[i];
   }
  }
 }
 // Set the population to the mutants
 for (int i=0; i<(1<<number_of_loci); i++){
  population.func[i]+=mutants.func[i];
 }

 return 0;
}
