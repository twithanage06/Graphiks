CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../include

TARGET = function_test

SOURCES = function_test.cpp ../src/tokeniser.cpp

all: $(TARGET)

$(TARGET): $(SOURCES) ../include/tokeniser.hpp
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean