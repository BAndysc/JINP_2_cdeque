mkdir -p build
mkdir -p build/obj
g++ -c -Wall -O2 -std=c++14 strdeque.cc -o build/obj/strdeque.o
g++ -c -Wall -O2 -std=c++14 strdequeconst.cc -o build/obj/strdequeconst.o
gcc -c -Wall -O2 strdeque_test1.c -o build/obj/strdeque_test1.o
g++ -c -Wall -O2 -std=c++14 strdeque_test2a.cc -o build/obj/strdeque_test2a.o
g++ -c -Wall -O2 -std=c++14 strdeque_test2b.cc -o build/obj/strdeque_test2b.o
g++ build/obj/strdeque_test1.o build/obj/strdeque.o build/obj/strdequeconst.o -o build/strdeque_test1
g++ build/obj/strdeque_test2a.o build/obj/strdeque.o build/obj/strdequeconst.o -o build/strdeque_test2a
g++ build/obj/strdeque_test2b.o build/obj/strdeque.o build/obj/strdequeconst.o -o build/strdeque_test2b