#!/bin/bash
cd user
make
./test_user
cd ..
cd systemFunctions
make
./test_systemFunctions
cd ..
make