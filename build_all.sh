#!/bin/bash

cd Debug
make clean && make all
cd ../MISS_Dispnew/Debug
make clean && make all
cd ../..
