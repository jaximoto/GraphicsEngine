# compiler and flags
CXX = g++
CXXFLAGS = -Wall -ldl -lglfw
INCLUDE = ../includes/
# Program and their sources
PROGRAMS = output



SRC = src.cpp $(INCLUDE)glad.c
OBJS = $(SRC:.cpp=.o)

all: $(PROGRAMS)

output: $(SRC)
	$(CXX) $^ $(CXXFLAGS) -o $@ 

%.o: %.cpp $(INCLUDE)shader.h $(INCLUDE)std_image.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAMS) *.o
#g++ hello_triangle.cpp glad.c -ldl -lglfw
