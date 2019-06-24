#
#	makefile for sf2float
#
#
CC=gcc
CFLAGS= -ansi -O3 -Dunix -I ./include
PORTSF = -L./lib -lportsf

.c.o:
	$(CC) $(CFLAGS) -c $<


#
#	targets
#
all:	sf2float 

clean:
	-rm -f sf2float.o

./lib/portsf.a:
	cd portsf; make; make install

sf2float: ./lib/portsf.a	sf2float.o 
	$(CC) $(CFLAGS) sf2float.o  -o sf2float $(PORTSF)

#
#	dependencies
#
