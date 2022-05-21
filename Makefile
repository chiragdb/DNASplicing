INCLUDES=-I includes/
CXXFLAGS=-std=c++20 -stdlib=libc++ -lc++abi -g -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

exec: bin/main.out
	$<

tests: bin/tests.out
	- $<

clean:
	rm -f bin/*

bin/main.out: src/driver.cc src/dna_strand.cc 
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests.out: tests/tests.cc src/dna_strand.cc 
	$(CXX) $(CXXFLAGS) $^ -o $@

src/%.cc: includes/%.h
	touch $@

.DEFAULT_GOAL := tests
.PHONY: test clean exec