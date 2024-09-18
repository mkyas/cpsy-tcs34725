CXXFLAGS = -std=c++20 -Wall -O2
LDLIBS = -li2c

testtcs: testtcs.cpp libtcl34725.a

libtcl34725.a: libtcl34725.a(TCS34725.o)
	ranlib $@

libtcl34725.a(.o): TCS34725.o

TCS34725.o: TCS34725.cpp TCS34725.hpp

