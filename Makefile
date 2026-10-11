CXX ?= g++

CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic -g
CPPFLAGS += -Iinclude

TARGET ?= main

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard include/*.h)
OBJECTS := $(patsubst %.cpp,build/%.o,$(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

build/%.o: %.cpp $(HEADERS)
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)