DIR_SYSTEM=/home/marcos/Repositories/R/P2/

all: serverTCP clientTCP Clean

serverTCP: serverTCP.cc $(DIR_SYSTEM)systemFunctions/systemFunctions.h $(DIR_SYSTEM)gameManager/gameManager.cc $(DIR_SYSTEM)gameManager/gameManager.h $(DIR_SYSTEM)systemFunctions/systemFunctions.cc $(DIR_SYSTEM)game/game.cc $(DIR_SYSTEM)game/game.h $(DIR_SYSTEM)user/user.cc $(DIR_SYSTEM)user/user.h  $(DIR_SYSTEM)refran/refran.cc $(DIR_SYSTEM)refran/refran.cc
	g++ $^ -Wno-multichar -Wno-type-limits -o serverTCP

clientTCP: clientTCP.cc $(DIR_SYSTEM)systemFunctions/systemFunctions.h $(DIR_SYSTEM)gameManager/gameManager.cc $(DIR_SYSTEM)gameManager/gameManager.h $(DIR_SYSTEM)systemFunctions/systemFunctions.cc $(DIR_SYSTEM)game/game.cc $(DIR_SYSTEM)game/game.h $(DIR_SYSTEM)user/user.cc $(DIR_SYSTEM)user/user.h $(DIR_SYSTEM)refran/refran.cc $(DIR_SYSTEM)refran/refran.cc
	g++ $^ -Wno-multichar -Wno-type-limits -o clientTCP

.Phony: Clean
Clean:
	rm -f *.o 