GTEST_DIR = /home/marcos/Repositories/R/P2/googletest-release-1.8.1/googletest
DIR_SYSTEM=/home/marcos/Repositories/R/P2/

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread -std=gnu++11

TESTS = test_systemFunctions

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : $(TESTS) Clean

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

systemFunctions.o : systemFunctions.h systemFunctions.cc $(DIR_SYSTEM)gameManager/gameManager.cc $(DIR_SYSTEM)gameManager/gameManager.h $(DIR_SYSTEM)game/game.cc $(DIR_SYSTEM)game/game.h $(DIR_SYSTEM)user/user.cc $(DIR_SYSTEM)user/user.h

test_systemFunctions.o : test_systemFunctions.cc systemFunctions.h systemFunctions.cc $(DIR_SYSTEM)gameManager/gameManager.cc $(DIR_SYSTEM)gameManager/gameManager.h $(DIR_SYSTEM)game/game.cc $(DIR_SYSTEM)game/game.h $(DIR_SYSTEM)user/user.cc $(DIR_SYSTEM)user/user.h

test_systemFunctions : systemFunctions.o test_systemFunctions.o gtest_main.a $(DIR_SYSTEM)gameManager/gameManager.cc $(DIR_SYSTEM)gameManager/gameManager.h $(DIR_SYSTEM)game/game.cc $(DIR_SYSTEM)game/game.h $(DIR_SYSTEM)user/user.cc $(DIR_SYSTEM)user/user.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

.Phony: Clean
Clean :
	rm -f gtest.a gtest_main.a *.o ??XX.txt