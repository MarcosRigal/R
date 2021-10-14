DIR_SYSTEM=/home/marcos/Repositories/R/P2/systemFunctions

all: serverTCP clientTCP Clean

serverTCP: serverTCP.cc $(DIR_SYSTEM)/systemFunctions.h $(DIR_SYSTEM)/systemFunctions.cc
	g++ $^ -o serverTCP

clientTCP: clientTCP.cc $(DIR_SYSTEM)/systemFunctions.h $(DIR_SYSTEM)/systemFunctions.cc
	g++ $^ -o clientTCP

.Phony: Clean
Clean:
	rm -f *.o 