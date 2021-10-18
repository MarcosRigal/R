GTEST_DIR = /home/marcos/Repositories/R/P2/googletest-release-1.8.1/googletest

DIR_SYSTEM=/home/marcos/Repositories/R/P2/

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wno-multichar -Wno-type-limits -Wextra -pthread -std=gnu++11

TESTS = test_game

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : $(TESTS) clean

clean :
	rm -f gtest.a gtest_main.a *.o ??XX.txt

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

game.o : game.h game.cc $(DIR_SYSTEM)refran/refran.cc $(DIR_SYSTEM)refran/refran.h

test_game.o : test_game.cc game.h game.cc $(DIR_SYSTEM)refran/refran.cc $(DIR_SYSTEM)refran/refran.h

test_game : game.o test_game.o gtest_main.a $(DIR_SYSTEM)refran/refran.cc $(DIR_SYSTEM)refran/refran.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@