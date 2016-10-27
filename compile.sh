mkdir -p build
mkdir -p build/obj
g++ -g -c -Wall -O2 -std=c++14 strdeque.cc -o build/obj/strdeque.o
g++ -g -c -Wall -O2 -std=c++14 strdequeconst.cc -o build/obj/strdequeconst.o
gcc -g -c -Wall -O2 strdeque_test1.c -o build/obj/strdeque_test1.o
g++ -g -c -Wall -O2 -std=c++14 strdeque_test2a.cc -o build/obj/strdeque_test2a.o
g++ -g -c -Wall -O2 -std=c++14 strdeque_test2b.cc -o build/obj/strdeque_test2b.o
g++ -g -c -Wall -O2 -std=c++14 strdeque_test3.cc -o build/obj/strdeque_test3.o
gcc -g -c -Wall -O2 strdeque_test4.c -o build/obj/strdeque_test4.o
g++ -g build/obj/strdeque_test1.o build/obj/strdeque.o build/obj/strdequeconst.o -o build/strdeque_test1
g++ -g build/obj/strdeque_test2a.o build/obj/strdeque.o build/obj/strdequeconst.o -o build/strdeque_test2a
g++ -g build/obj/strdeque_test2b.o build/obj/strdeque.o build/obj/strdequeconst.o -o build/strdeque_test2b
g++ -g build/obj/strdeque_test3.o build/obj/strdeque.o build/obj/strdequeconst.o -o build/strdeque_test3
g++ -g build/obj/strdeque_test4.o build/obj/strdeque.o build/obj/strdequeconst.o -o build/strdeque_test4
