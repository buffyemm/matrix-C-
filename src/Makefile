LIBRARY=./matrix/s21_matrix_oop.cpp
CUM=./matrix/s21_matrix_oop.h
TESTS=./tests/tests.cpp
OUTPUT=s21_matrix_oop.a
CXXFLAGS=-std=c++17 -g

all: $(OUTPUT)

$(OUTPUT): $(LIBRARY) $(TESTS)
	g++ $(CXXFLAGS) -o $(OUTPUT) $(LIBRARY) $(CUM)
	./$(OUTPUT)




build: $(OUTPUT)
	g++ $(CXXFLAGS) -o $(OUTPUT) $(LIBRARY) $(TESTS) -lgtest

clean:
	rm -f $(OUTPUT)
