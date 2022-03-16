TARGETS = libeig_pair.so
OBJS=$(TARGETS:=.o)

all: $(TARGETS)

libeig_pair.o: libeig_pair.c
	gcc -I. -Wall -fPIC -c -o $@ $< -fopenmp

libeig_pair.so: libeig_pair.o
	gcc -Wall -fPIC -I. $< -o $@ -shared -fopenmp

$(OBJS): Makefile

clean:
	rm *.o *.so