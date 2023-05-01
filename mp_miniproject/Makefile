CPPFLAGS=-Werror -Wall -pedantic -std=gnu++98 -ggdb3
PROGS=path-step1 path-step2 path-step3 path-step4
all: $(PROGS)

path-step1: path-step1.o path_planning.o
	g++ -o $@ $^

path-step2: path-step2.o path_planning.o
	g++ -o $@ $^

path-step3: path-step3.o path_planning.o
	g++ -o $@ $^

path-step4: path-step4.o path_planning.o
	g++ -o $@ $^

%.o: %.cpp
	g++ $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ *.o $(PROGS)

path_planning.o: path_planning.hpp
