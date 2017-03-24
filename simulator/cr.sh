g++ -std=c++11 *.cpp *.hpp -O2 -c
g++ -std=c++11 *.o -O2 -o single_cycle
mv single_cycle.exe single_cycle
./single_cycle
