PROJECT = main

LIBPROJECT = $(PROJECT).a

TESTPROJECT = test

OBJECTS = main.o

DEPS = $(wildcard *.hpp)

A = ar

AFLAGS = rsv

CXX = g++

CXXFLAGS = -I. -std=c++17 -Werror -Wpedantic -Wall -g -fPIC

LDXXFLAGS = $(CXXFLAGS) -L. -l:$(LIBPROJECT)

LDGTESTFLAGS = $(LDXXFLAGS) -lgtest_main -lgtest -lpthread

.PHONY: default

default: all;

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	
$(LIBPROJECT): $(OBJECTS)
	$(A) $(AFLAGS) $@ $^
	

$(PROJECT): main.o $(LIBPROJECT)
	$(CXX) -o $@ $< $(LDXXFLAGS)
	
$(TESTPROJECT): circular_test.o $(LIBPROJECT)
	$(CXX) -o $@ $< $(LDGTESTFLAGS)

all: $(PROJECT)

test: $(TESTPROJECT)

.PHONY: clean

clean:
	rm -f *.o

cleanall: clean
	rm -f $(LIBPROJECT)
	rm -f $(PROJECT)
	rm -f $(TESTPROJECT)
