# Pull in ROOT
ROOT_INCLUDES=`root-config --cflags`
ROOT_ALL=`root-config --cflags --libs`

#Compiler
CC=g++ -O2 -g -Wall
CCC=${CC} -c

all: LogPlotter.exe

LogPlotter.exe: LogPlotter.cc
	${CC} ${ROOT_ALL} -o LogPlotter.exe \
	LogPlotter.cc

clean:
	rm -f LogPlotter.exe *.o
