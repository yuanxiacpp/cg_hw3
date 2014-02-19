#
#  Makefile for ImageFilter 
#


LIBDIR =  -Wl,-rpath,-lm  -ltiff

CFLAGS = -g3 -Wno-deprecated -std=c++11

CC = g++

.SUFFIXES: .o .cpp

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<


ALL.O =  equalize.o figio.o 

program_name_here: $(ALL.O)
	$(CC) $(CFLAGS) -o $@ $(ALL.O) $(INCLUDE) $(LIBDIR) $(LIBS)

clean:
	rm -f $(ALL.O) equalize *~ 
