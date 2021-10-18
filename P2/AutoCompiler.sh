#!/bin/bash
cd user
make
./test_user
cd ..
cd refran
make
./test_refran
cd ..
cd game
make
./test_game
cd ..
cd gameManager
make
./test_gameManager
cd ..
cd systemFunctions
make
./test_systemFunctions
cd ..
make