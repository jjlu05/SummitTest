#
# Dragonfly
# Copyright Mark Claypool and WPI, 2014, 2015
#
# Makefile for example tests using the Unit Test Manager.
#

####################################
# Compiler settings.
LDFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt

# Dragonfly location.
ENGINC = -I../..
ENG = ../../libdragonfly.a

# Unit Test Manager location.
UNITINC = -I../utm
UNIT = ../utm/libunittest.a

####################################
EXECUTABLE = df-test-example
TESTSRC = $(wildcard *.cpp)
TESTHDR = $(wildcard *.h)
TESTOBJ = $(TESTSRC:.cpp=.o)
CC = g++
CFLAGS = 
#CFLAGS = -g			# uncomment if using gdb

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(ENG) $(TESTOBJ) $(TESTSRC) $(TESTHDR) $(UNIT)
	$(CC) $(CFLAGS) $(ENGINC) $(UNITINC) $(PLATFORM) $(TESTOBJ) $(ENG) $(UNIT) -o $@ $(LDFLAGS) 

.cpp.o: 
	$(CC) -c $(CFLAGS) $(ENGINC) $(UNITINC) $(PLATFORM) $< -o $@

clean:
	$(RM) -f $(TESTOBJ) $(TESTOBJ) $(EXECUTABLE) core *.log *~
	$(RM) -rf log/ out
	makedepend
	rm -f Makefile.bak

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE
