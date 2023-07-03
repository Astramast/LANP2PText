CXX = g++-11
CXXFLAGS += -std='c++20' -Wall -Wextra -Wsign-compare -pedantic -D_GNU_SOURCE -fmax-errors=2
BINS = $(filter-out main.o, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

.PHONY: default
default: main clean

main: ${BINS}
	${CXX} ${CXXFLAGS} $^ main.cpp -o LANP2PChat -pthread

%.o: %.cpp
	${CXX} ${CXXFLAGS} $< -c -o $@

.PHONY: clean
clean:
	rm -f *.o

