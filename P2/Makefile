DIR_SYSTEM=/home/marcos/Repositories/R/P2/

all: serverTCP clientTCP Clean

serverTCP: serverTCP.cc $(DIR_SYSTEM)systemFunctions/systemFunctions.h $(DIR_SYSTEM)gameManager/gameManager.cc $(DIR_SYSTEM)gameManager/gameManager.h $(DIR_SYSTEM)systemFunctions/systemFunctions.cc $(DIR_SYSTEM)game/game.cc $(DIR_SYSTEM)game/game.h $(DIR_SYSTEM)user/user.cc $(DIR_SYSTEM)user/user.h  
	g++ $^ -o serverTCP

clientTCP: clientTCP.cc $(DIR_SYSTEM)systemFunctions/systemFunctions.h $(DIR_SYSTEM)gameManager/gameManager.cc $(DIR_SYSTEM)gameManager/gameManager.h $(DIR_SYSTEM)systemFunctions/systemFunctions.cc $(DIR_SYSTEM)game/game.cc $(DIR_SYSTEM)game/game.h $(DIR_SYSTEM)user/user.cc $(DIR_SYSTEM)user/user.h
	g++ $^ -o clientTCP

.Phony: Clean
Clean:
	rm -f *.o 