/**
 * @file hivpython.cpp
 * @brief Implementation of an HIV population with drug treatment.
 * @author Richard Neher, Boris Shraiman, Fabio Zanini
 * @version 
 * @date 2012-04-23
 */

#include "popgen.h"
#include "popgen_highd.h"
#include "hivpopulation.h"
#include "hivpython.h"
#include <iostream>
#include <fstream>

hivpython::hivpython() {
}


hivpython::~hivpython() {
}

int hivpython::evolve(int gen) {
	int err=haploid_clone::evolve(gen);
	if(err==0)
		haploid_clone::calc_stat();
	return err;
}

int hivpython::read_selection_coefficients(char *model){
	ifstream modelstream(model);
	return hivpopulation::read_selection_coefficients(modelstream);
}

int hivpython::read_resistance_coefficients(char *model){
	ifstream modelstream(model);
	return hivpopulation::read_resistance_coefficients(modelstream);
}

void hivpython::get_allele_frequencies(double *af) {
	for(size_t i=0; i < number_of_loci; i++)
		af[i] = haploid_clone::get_allele_frequency(i);
}

int hivpython::init_genotypes(double *nu, int n_o_g) {
	haploid_clone::init_genotypes(nu, n_o_g);
}

void hivpython::get_genotype(unsigned int i, unsigned short *seq) {
	boost::dynamic_bitset<> newgt = (*current_pop)[i].genotype;
	for(size_t i=0; i < number_of_loci; i++)
		seq[i] = newgt[i];
}

void hivpython::random_clones(int n_o_individuals, unsigned int * result) {
	vector <int> sample = vector <int>(0);
	int err = haploid_clone::random_clones(n_o_individuals, &sample);
	if(!err)
		for(size_t i=0; i < n_o_individuals; i++)
			result[i] = sample[i];
}

// Note: this function is renamed in the SWIG file for memory management issues
void hivpython::get_fitnesses(int ncl, double *fits) {
	if(ncl>(current_pop->size()))
		ncl = current_pop->size();
	for(size_t i=0; i < ncl; i++)
		fits[i] = haploid_clone::get_fitness(i);
}

int hivpython::distance_Hamming(unsigned int clone1, unsigned int clone2, int l1, int l2, unsigned int *chunksflat, int every) {
	// Check dimensions
	if(l2 != 2) return HP_BADARG;

	vector <unsigned int *> chunks;
	unsigned int *tmp_chunk;
	int d;

	// Allocate memory
	for(size_t i=0; i<l1; i++) {
		tmp_chunk = new unsigned int[2];
		tmp_chunk[0] = (unsigned int)chunksflat[i*2];
		tmp_chunk[1] = (unsigned int)chunksflat[i*2+1];
		chunks.push_back(tmp_chunk);
	}

	// Call baseclass method
	d = haploid_clone::distance_Hamming(clone1, clone2, &chunks, every);

	// Release memory
	for(size_t i=0; i<l1; i++) delete chunks[i];

	return d;
}

int hivpython::write_genotypes(char * filename, int sample_size, char * gt_label, int start, int length) {
	if(HIVPYTHON_VERBOSE >= 1) cerr<<"hivpython::write_genotypes(char * filename, int sample_size, char * gt_label, int start, int length)...";

	ofstream genotype_file(filename);	
	if(HIVPYTHON_VERBOSE >= 2) cerr<<"initialized ofstream...";

	string gt_labelstring;
	if(gt_label == NULL) {
		gt_labelstring = "";
		if(HIVPYTHON_VERBOSE >= 2) cerr<<"empty gt_labelstring...";
	}
	else {
		gt_labelstring = string(gt_label);
		if(HIVPYTHON_VERBOSE >= 2) cerr<<"gt_labelstring ="<<gt_labelstring<<"...";
	}

	int result = hivpopulation::write_genotypes(genotype_file, sample_size, gt_labelstring, start, length);
	if(HIVPYTHON_VERBOSE >= 1) cerr<<"done."<<endl;
	return result;
}

//int get_divergence_histogram(int bins_plus_1, unsigned int * bins_left, int bins, unsigned int * counts, int n_chunks, int two, unsigned int * chunks, unsigned int every=1, unsigned int n_sample=1000) {
//	return 0;
//};

