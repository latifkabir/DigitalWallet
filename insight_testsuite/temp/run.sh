#!/usr/bin/env bash

#Compile the source files :
echo " Compiling the sources ....."
g++ -O2 ./src/PayMo.cpp -std=c++11 -lm -o ./PayMo
echo " Done Compiling. The binary is inside ./bin directory."

#Run the binary for feature:1
echo " Running the program for feature 1 ... ..."
./PayMo 1 > ./paymo_output/output1.txt
echo " Done writing output file for feature 1."


#Run the binary for feature:2
echo "Running the program for feature 2 ... ..."
./PayMo 2 > ./paymo_output/output2.txt
echo " Done writing output file for feature 2."


#Run the binary for feature:3
echo "Running the program for feature 3 ... ..."
./PayMo 3 > ./paymo_output/output3.txt
echo " Done writing output file for feature 3."
