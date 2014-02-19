#
#  Makefile for Sphere_Normal 
#


LIBDIR =  -Wl,-rpath,-lm  -ltiff

CFLAGS = -g3 -Wno-deprecated

CC = g++

.SUFFIXES: .o .cpp

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<


ALL.O =  sphere_normals_579.o figio.o 

sphere_normals_579: $(ALL.O)
	$(CC) $(CFLAGS) -o $@ $(ALL.O) $(INCLUDE) $(LIBDIR) $(LIBS)

clean:
	rm -f $(ALL.O) sphere_normals_579 *~
