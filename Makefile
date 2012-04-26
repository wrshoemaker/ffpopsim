#############################################################################
#
# Licence:	
# Author:	Richard Neher, Boris Shraiman, Fabio Zanini
# Date:		2012/04/19
#
# Description:
# ------------
# Makefile for the PopGenLib library.
#
##==========================================================================
SRCDIR = src
DOCDIR = doc
TESTSDIR = tests

DIRS = $(SRCDIR) $(DOCDIR) $(TESTSDIR)

.PHONY : all clean src doc tests clean-src clean-doc clean-tests
all: src doc tests
clean: clean-src clean-doc clean-tests

##==========================================================================
# SOURCE
##==========================================================================
CXX = g++
CXXFLAGS= -O2 -g3 -fPIC

LIBRARY := libPopGenLib.a

HEADER_GENERIC = popgen.h
SOURCE_GENERIC = sample.cpp
OBJECT_GENERIC = $(SOURCE_GENERIC:%.cpp=%.o)

HEADER_LOWD = $(HEADER_GENERIC) popgen_lowd.h
SOURCE_LOWD = hypercube.cpp haploid_gt_dis.cpp
OBJECT_LOWD = $(SOURCE_LOWD:%.cpp=%.o)

HEADER_HIGHD = $(HEADER_GENERIC) popgen_highd.h
SOURCE_HIGHD = hypercube_function.cpp haploid_clone.cpp
OBJECT_HIGHD = $(SOURCE_HIGHD:%.cpp=%.o)

HEADER_HIV = hivpopulation.h
SOURCE_HIV = $(HEADER_HIV:%.h=%.cpp)
OBJECT_HIV = $(SOURCE_HIV:%.cpp=%.o)

OBJECTS = $(OBJECT_GENERIC) $(OBJECT_LOWD) $(OBJECT_HIGHD) $(OBJECT_HIV)

src: $(SRCDIR)/$(LIBRARY)

$(SRCDIR)/$(LIBRARY): $(OBJECTS:%=$(SRCDIR)/%)
	ar rcs $@ $^

$(OBJECT_GENERIC:%=$(SRCDIR)/%): $(SOURCE_GENERIC:%=$(SRCDIR)/%)
	$(CXX) $(CXXFLAGS) -c -o $@ $(@:.o=.cpp)

$(OBJECT_LOWD:%=$(SRCDIR)/%): $(SOURCE_LOWD:%=$(SRCDIR)/%) $(HEADER_LOWD:%=$(SRCDIR)/%)
	$(CXX) $(CXXFLAGS) -c -o $@ $(@:.o=.cpp)

$(OBJECT_HIGHD:%=$(SRCDIR)/%): $(SOURCE_HIGHD:%=$(SRCDIR)/%) $(HEADER_HIGHD:%=$(SRCDIR)/%)
	$(CXX) $(CXXFLAGS) -c -o $@ $(@:.o=.cpp)

$(OBJECT_HIV:%=$(SRCDIR)/%): $(SOURCE_HIV:%=$(SRCDIR)/%) $(HEADER_HIV:%=$(SRCDIR)/%)
	$(CXX) $(CXXFLAGS) -c -o $@ $(@:.o=.cpp)

clean-src:
	cd $(SRCDIR); rm -rf $(LIBRARY) *.o *.h.gch

##==========================================================================
# DOCUMENTATION
##==========================================================================
DOXYFILE   = $(DOCDIR)/Doxyfile
DOXY       = doxygen

doc:
	$(DOXY) $(DOXYFILE)

clean-doc:
	rm -rf $(DOCDIR)/latex $(DOCDIR)/html


##==========================================================================
# TESTS
##==========================================================================
testlibraries =  -lgsl -lgslcblas -lHandyTools -lPopGenLib 

TESTS_LDFLAGS = -L$(SRCDIR)/ -L$(SRCDIR)/../../HandyTools/src/ -L/usr/ -O2
TESTS_CXXFLAGS = -I$(SRCDIR)/ -I$(SRCDIR)/../../HandyTools/src/ -Wall -O2 -c -fPIC -g3

TESTS_LOWD = lowd
TESTS_HIGHD = highd

TESTS_SOURCE_LOWD = $(TESTS_LOWD:%=%.cpp)
TESTS_SOURCE_HIGHD = $(TESTS_HIGHD:%=%.cpp)

TESTS_HEADER_LOWD = $(TESTS_LOWD:%=%.h)
TESTS_HEADER_HIGHD = $(TESTS_HIGHD:%=%.h)

TESTS_OBJECT_LOWD = $(TESTS_LOWD:%=%.o)
TESTS_OBJECT_HIGHD = $(TESTS_HIGHD:%=%.o)

tests: $(TESTS_LOWD:%=$(TESTSDIR)/%) $(TESTS_HIGHD:%=$(TESTSDIR)/%)

$(TESTS_LOWD:%=$(TESTSDIR)/%): $(TESTS_OBJECT_LOWD:%=$(TESTSDIR)/%) $(SRCDIR)/$(LIBRARY)
	$(CXX) $(TESTS_LDFLAGS) -o $@ $^ $(testlibraries)

$(TESTS_OBJECT_LOWD:%=$(TESTSDIR)/%): $(TESTS_SOURCE_LOWD:%=$(TESTSDIR)/%) $(TESTS_HEADER_LOWD:%=$(TESTSDIR)/%)
	$(CXX) $(TESTS_CXXFLAGS) -c -o $@ $(@:.o=.cpp)

$(TESTS_HIGHD:%=$(TESTSDIR)/%): $(TESTS_OBJECT_HIGHD:%=$(TESTSDIR)/%) $(OBJECT_HIV:%=$(SRCDIR)/%) $(SRCDIR)/$(LIBRARY)
	$(CXX) $(TESTS_LDFLAGS) -o $@ $^ $(testlibraries)

$(TESTS_OBJECT_HIGHD:%=$(TESTSDIR)/%): $(TESTS_SOURCE_HIGHD:%=$(TESTSDIR)/%) $(TESTS_HEADER_HIGHD:%=$(TESTSDIR)/%)
	$(CXX) $(TESTS_CXXFLAGS) -c -o $@ $(@:.o=.cpp)

clean-tests:
	cd $(TESTSDIR); rm -rf *.o $(TESTS_LOWD) $(TESTS_HIGHD)

#############################################################################
