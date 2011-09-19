CC = g++
CFLAGS = -O2 -c -g -fPIC

HEADERS = popgen.h

PopGenLib:	haploid_gt_dis.o  haploid_pop_hop.o  haploid_population.o hypercube_function.o hypercube.o sample.o
	ar  rcs libPopGenLib.a haploid_pop_hop.o haploid_gt_dis.o haploid_population.o hypercube_function.o hypercube.o sample.o


sample.o:	sample.cpp $(HEADERS)
	$(CC) ${CFLAGS} sample.cpp

haploid_pop_hop.o:	$(HEADERS) haploid_pop_hop.cpp haploid_gt_dis.cpp
	$(CC) ${CFLAGS} haploid_pop_hop.cpp

haploid_gt_dis.o:	$(HEADERS) haploid_gt_dis.cpp
	$(CC) ${CFLAGS} haploid_gt_dis.cpp

haploid_population.o:	$(HEADERS) haploid_population.cpp
	$(CC) ${CFLAGS} haploid_population.cpp

hypercube_function.o: $(HEADERS) hypercube_function.cpp
	$(CC) ${CFLAGS} hypercube_function.cpp

hypercube.o: $(HEADERS) hypercube.cpp
	$(CC) ${CFLAGS} hypercube.cpp

clean:
	rm -rf *.o libPopGenLib.a
