
CXX = clang++-18
CXXFLAGS = -std=c++11 -Wall -Wextra -g

#files
SRC = Graph.cpp Queue.cpp Algorithms.cpp PriorityQueue.cpp UnionFind.cpp
TEST = TestGraph.cpp
OBJ = $(SRC:.cpp=.o)

#Executable for unit tests
TEST_EXE = test

# Executable for main
MAIN_SRC = main.cpp
MAIN_EXE = main


all: $(TEST_EXE)

# compile tests
$(TEST_EXE): $(SRC) $(TEST)
	$(CXX) $(CXXFLAGS) $(SRC) $(TEST) -o $(TEST_EXE)

# run tests
runtest: $(TEST_EXE)
	./$(TEST_EXE)

#compile main
$(MAIN_EXE): $(SRC) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(MAIN_SRC) -o $(MAIN_EXE)

#run main
run: $(MAIN_EXE)
	./$(MAIN_EXE)

#memory check using Valgrind for both main and tests
valgrind: $(MAIN_EXE)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN_EXE)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_EXE)

#clean files
clean:
	rm -f $(TEST_EXE) $(MAIN_EXE) *.o
