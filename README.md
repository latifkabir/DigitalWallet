
Algorithm
------------
Hash Table type of data structure is used to store payment information with sender and receiver ID. This makes item look up very quick.
It produces a undirected graph.
Recursion is used to scan through different generations.



Requirements
----------------
1. Requires -std=c++11 flag to compile.


How to compile
---------------
g++ -O2 ./src/PayMo.cpp -std=c++11 -lm -o ./PayMo


How to run
-----------
#Run the binary for feature:1
./PayMo 1 > ./paymo_output/output1.txt


#Run the binary for feature:2
./PayMo 2 > ./paymo_output/output2.txt


#Run the binary for feature:3
./PayMo 3 > ./paymo_output/output3.txt




Add On:
-------
The way it is implemented , the program works for any number of generation in general.
