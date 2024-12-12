# compiler and flags
CXX = g++
CXXFLAGS = -Wall -ldl -lglfw
INCLUDE = ../includes/
# Program and their sources
PROGRAMS = texture



texture_SRC = texture.cpp $(INCLUDE)glad.c
texture_OBJS = $(texture_SRC:.cpp=.o)

all: $(PROGRAMS)

texture: $(texture_SRC)
	$(CXX) $^ $(CXXFLAGS) -o $@ 

%.o: %.cpp $(INCLUDE)shader.h $(INCLUDE)std_image.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAMS) *.o
#g++ hello_triangle.cpp glad.c -ldl -lglfw
