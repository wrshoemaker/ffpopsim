# Fitness valley crossing #

Fitness valleys are what most prevents most drug resistance. In other words, a pathogen has to acquire several mutations before the altered genotype can grow in presence of the drug and out-compete the wild-type. The dynamics of fitness valley crossing is affected in subtle ways and often requires very large populations. Hence the part of FFPopSim for a few loci is ideally suited to study valley crossing.

The following will do the trick:

```

import FFPopSim
L = 4 # number of loci
N = 1e10 # population size
s1 = 1e-5 # fitness of wildtype
s2 = 0.01 # fitness of quadruple mutant

c = FFPopSim.haploid_lowd(L) # create population
c.set_genotypes([0b0],[N]) # start with wildtype

c.set_recombination_rates([1e-2] * (L-1)) # set recombination rates
c.set_mutation_rate(1e-5)                 # set mutation rate

# assign positive relative fitness to wildtype and quadruple mutant
c.set_fitness_function([0b0, 0b1111], [s1, s1+s2])

# cross valley with an accuracy of 100 generations
gens_at_once = 100
while c.get_genotype_frequency(0b1111)<0.5 and c.generation<1e7:
c.evolve(gens_at_once)

# print result
print 'Time to cross the valley: '+str(c.generation)+' generations'
```