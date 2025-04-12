echo "Start compilling ------------------------------------------------------------------------------------ "
g++ -Wall -c BinTreeFunc.cpp AkinatorMain.cpp Input.cpp AkinatorFunc.cpp StackFunc.cpp
g++ -Wall -o akinator.exe BinTreeFunc.o AkinatorMain.o Input.o AkinatorFunc.o StackFunc.o

echo "End compilling   ------------------------------------------------------------------------------------ "
