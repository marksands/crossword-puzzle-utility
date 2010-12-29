CXX = g++ -Wall -Werror
FLAGS = -I$$BOOST_ROOT
LIB = $$BOOST_ROOT/stage/lib/libboost_program_options.a

all: dictionary

dictionary: main.o
	$(CXX) main.o -o dictionary $(LIB)

main.o: main.cpp
	$(CXX) $(FLAGS) -c main.cpp

clean:
	rm -rf *o dictionary