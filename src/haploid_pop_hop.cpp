/*
 * haploid_pop_hop.cpp
 *
 * Created on: Sept 19, 2011
 * Author: Fabio Zanini
 */
#include "popgen.h"

haploid_pop_hop::haploid_pop_hop() : haploid_gt_dis()
{
}

haploid_pop_hop::~haploid_pop_hop()
{
 //TODO: free the memory for the hop rates here
 // the destructor of the superclass is called automagically
}

haploid_pop_hop::haploid_pop_hop(int nloci, double popsize, int rngseed) : haploid_gt_dis(nloci, popsize, rngseed)
{
}

int haploid_pop_hop::set_hopping_rate(double h)
{
	return 0;
}
