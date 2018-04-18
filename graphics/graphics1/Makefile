PLATFORM = $(shell uname)


## Compilation flags
##comment out one or the other 
##debugging 
CFLAGS = -g 
##release
#CFLAGS = -O3 -DNDEBUG
LDFLAGS=

CFLAGS+= -Wall

ifeq ($(PLATFORM),Darwin)
## Mac OS X
CFLAGS += -m64 -isystem/usr/local/include -Wno-deprecated
LDFLAGS+= -m64 -lc -framework AGL -framework OpenGL -framework GLUT -framework Foundation
else
## Linux
CFLAGS += -m64 -Wno-deprecated
INCLUDEPATH  = -I/usr/include/GL/ 
LIBPATH = -L/usr/lib64 -L/usr/X11R6/lib
LDFLAGS+=  -lGL -lglut -lrt -lGLU -lX11 -lm  -lXmu -lXext -lXi
endif


CC = gcc 


PROGS = simple1 simple2 simple3 simple4 simple5 simple6 simple7 

default: $(PROGS)



####2D
simple1: simple1.o
	$(CC) -o $@ simple1.o  $(LDFLAGS)
simple1.o: simple1.c 
	$(CC) -c $(INCLUDEPATH) $(CFLAGS)  simple1.c  -o $@

simple2: simple2.o
	$(CC) -o $@ simple2.o  $(LDFLAGS)
simple2.o: simple2.c 
	$(CC) -c $(INCLUDEPATH) $(CFLAGS)  simple2.c  -o $@

simple3: simple3.o
	$(CC) -o $@ simple3.o  $(LDFLAGS)
simple3.o: simple3.c 
	$(CC) -c $(INCLUDEPATH) $(CFLAGS)  simple3.c  -o $@

simple4: simple4.o
	$(CC) -o $@ simple4.o  $(LDFLAGS)
simple4.o: simple4.c 
	$(CC) -c $(INCLUDEPATH) $(CFLAGS)  simple4.c  -o $@

simple5: simple5.o
	$(CC) -o $@ simple5.o  $(LDFLAGS)
simple5.o: simple5.c 
	$(CC) -c $(INCLUDEPATH) $(CFLAGS)  simple5.c  -o $@


###3D 

simple6:simple6.o 
	$(CC)  simple6.o  $(LDFLAGS) -o $@
simple6.o:simple6.c
	$(CC)  $(INCLUDEPATH) $(CFLAGS)   -c simple6.c  -o $@
simple7:simple7.o 
	$(CC)  simple7.o  $(LDFLAGS) -o $@
simple7.o:simple7.c
	$(CC)  $(INCLUDEPATH) $(CFLAGS)   -c simple7.c  -o $@


clean::	
	rm *.o
	rm $(PROGS)


