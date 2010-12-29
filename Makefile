CXX = g++ -Wall -Werror
FLAGS = -I$$BOOST_ROOT

all: dictionary

dictionary: main.o
	$(CXX) main.o -o dictionary

main.o: main.cpp
	$(CXX) $(FLAGS) main.cpp

clean:
	rm -rf *o dictionary