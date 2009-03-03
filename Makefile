
all: crossword

crossword: main.o SearchableADT.o BST.o AVL.o
	g++ main.o -o crossword

main.o: main.cpp
	g++ -c src/main.cpp

BST.o: BST.h
	g++ -c src/BST.h

AVL.o: AVL.h
	g++ -c src/AVL.h

SearchableADT.o: SearchableADT.h
	g++ -c src/SearchableADT.h

clean:
	rm -rf *o crossword
	
