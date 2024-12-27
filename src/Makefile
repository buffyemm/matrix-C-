LIBRARY=./matrix/matrix.cpp
CUM=./matrix/matrix.h
TESTS=./tests/tests.cpp
OUTPUT=vedro
CXXFLAGS=-std=c++17 -g

all: $(OUTPUT)

$(OUTPUT): $(LIBRARY) $(TESTS)
	g++ $(CXXFLAGS) -o $(OUTPUT) $(LIBRARY) $(CUM)
	./$(OUTPUT)

build: $(OUTPUT)
	g++ $(CXXFLAGS) -o $(OUTPUT) $(LIBRARY) $(TESTS) -lgtest

clean:
	rm -f $(OUTPUT)
