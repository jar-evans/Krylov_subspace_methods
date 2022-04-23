TARGETS = libKrylov.so
OBJS=$(TARGETS:=.o)

all: $(TARGETS)

libKrylov.o: libKrylov.cpp
	g++ -I. -Wall -fPIC -c -o $@ $< -fopenmp

libKrylov.so: libKrylov.o
	g++ -I. -Wall -fPIC $< -o $@ -shared -fopenmp

test: test.cpp
	make all
	g++ test.cpp -o $@
	./$@
	make clean

$(OBJS): Makefile

clean:
	rm *.o *.so *.out *