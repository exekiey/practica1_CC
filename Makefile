CXX ?= g++

CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -g

TARGET ?= main

SOURCES := $(wildcard *.cpp)

OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)