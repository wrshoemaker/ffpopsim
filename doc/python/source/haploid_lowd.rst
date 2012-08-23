.. _haploid_lowd:

haploid_lowd Class Reference
============================
.. autoclass:: FFPopSim.haploid_lowd
   :members: L,
             N,
             number_of_loci,
             population_size,
             circular,
             carrying_capacity,
             free_recombination,
             generation,
             get_allele_frequencies,
             get_divergence_histogram,
             get_divergence_statistics,
             get_diversity_histogram,
             get_diversity_statistics,
             get_fitnesses,
             get_genotype_frequencies,
             get_mutation_rates,
             outcrossing_rate,
             plot_divergence_histogram,
             plot_diversity_histogram,
             plot_fitness_histogram,
             random_clones,
             set_allele_frequencies,
             set_fitness_function,
             set_genotypes,
             set_mutation_rates

   .. automethod:: FFPopSim.haploid_lowd.allele_entropy()
   .. automethod:: FFPopSim.haploid_lowd.evolve(gen=1)
   .. automethod:: FFPopSim.haploid_lowd.evolve_deterministic(gen=1)
   .. automethod:: FFPopSim.haploid_lowd.evolve_norec(gen=1)
   .. automethod:: FFPopSim.haploid_lowd.genotype_entropy()
   .. automethod:: FFPopSim.haploid_lowd.get_allele_frequency(locus)
   .. automethod:: FFPopSim.haploid_lowd.get_chi(locus)
   .. automethod:: FFPopSim.haploid_lowd.get_fitness(genotype)
   .. automethod:: FFPopSim.haploid_lowd.get_genotype_frequency(locus)
   .. automethod:: FFPopSim.haploid_lowd.get_LD(locus1, locus2)
   .. automethod:: FFPopSim.haploid_lowd.get_moment(locus1, locus2)
   .. automethod:: FFPopSim.haploid_lowd.set_fitness_additive(coefficient)
   .. automethod:: FFPopSim.haploid_lowd.set_recombination_rates(rec_rates)

