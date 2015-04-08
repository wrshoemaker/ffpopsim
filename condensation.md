# Genotype condensation #
Fitness interactions between mutations is called epistasis. Epistasis implies that some mutations are selected to stick together. Recombination has the opposite tendency, as it scrambles genotypes. The competition between these two forces can give rise to a sharp transition between regimes where the population condenses into a few very fit ones, or a large number of average genotypes. Investigating this trade-off is made easy by FFPopSim:

```

# Import module
import sys
sys.path.append('../pkg/python')

import numpy as np
import matplotlib.pyplot as plt
import FFPopSim as ffpop
import argparse

plt.ion()

#parse the command line arguments
parser = argparse.ArgumentParser(description="Simulate a population on a mixed additive/epistatic fitness function")
parser.add_argument('--pop', default=10000, type=float, help='Population size (N)')
parser.add_argument('--rec',  default=0,type=float, help='out-crossing rate (r)')
parser.add_argument('--sigma', default=0.05,type=float, help='Sigma')
parser.add_argument('--hsq', default=0,type=float, help='heritability')
parser.add_argument('--Ttraj', default=200,type=int, help='Length of trajectory in generations')
parser.add_argument('--dt',  default=1,type =int, help='time increments of trajectory')
params=parser.parse_args()

#set up the population
L=64
pop=ffpop.haploid_highd(L)
pop.outcrossing_rate=params.rec
pop.set_random_epistasis(params.sigma*np.sqrt(1-params.hsq))
pop.recombination_model = ffpop.FREE_RECOMBINATION
if (params.hsq>0):
pop.set_additive_trait(np.ones(L)*params.sigma*sqrt(params.hsp/L))


#initialize
pop.set_allele_frequencies(np.ones(L)*0.5, params.pop)
pfit = pop.get_fitness_statistics()
popstat = []
for gen in range(params.dt,params.Ttraj, params.dt):
#append current statistics to the list
pfit = pop.get_fitness_statistics()
popstat.append([gen,pfit.mean, pfit.variance, pop.get_participation_ratio(), pop.number_of_clones])

#evolve for dt generations and clean up
pop.evolve(params.dt)
pop.unique_clones()
pop.calc_stat()

#cast population statistics to an array to allow slicing
popstat=np.array(popstat)

#plot quantities of interest
plt.figure(1)
plt.plot(popstat[:,0],popstat[:,-2])
plt.xlabel('Time')
plt.ylabel('Participation ratio')

plt.figure(2)
plt.plot(popstat[:,0],popstat[:,-1])
ax=plt.gca()
ax.set_yscale('log')
plt.xlabel('Time')
plt.ylabel('Number of clones')

plt.figure(3)
plt.plot(popstat[:,0],popstat[:,1], label='fitness mean')
plt.plot(popstat[:,0],np.sqrt(popstat[:,2]), label='fitness standard deviation')
plt.legend(loc=2)
plt.xlabel('Time')
```