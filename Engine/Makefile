
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

OBJS = main.o tokeniser.o parser.o evaluator.o

calculator: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o calculator

main.o: src/main.cpp include/parser.hpp include/tokeniser.hpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o

tokeniser.o: src/tokeniser.cpp include/tokeniser.hpp
	$(CXX) $(CXXFLAGS) -c src/tokeniser.cpp -o tokeniser.o

parser.o: src/parser.cpp include/parser.hpp include/tokeniser.hpp include/evaluator.hpp
	$(CXX) $(CXXFLAGS) -c src/parser.cpp -o parser.o

evaluator.o: src/evaluator.cpp include/evaluator.hpp
	$(CXX) $(CXXFLAGS) -c src/evaluator.cpp -o evaluator.o

clean:
	rm -f *.o calculator

.PHONY: clean
