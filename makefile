# compiler and flags
CXX = g++
CXXFLAGS = -Wall -ldl -lglfw

# Program and their sources
PROGRAMS = graphic tri3

graphic_SRC = first.cpp glad.c
graphic_OBJS = $(graphic_SRC:.cpp=.o)

tri3_SRC = tri3.cpp glad.c
tri3_OBJS = $(tri3_SRC:.cpp=.o)

all: $(PROGRAMS)

graphic: $(graphic_SRC)
	$(CXX) $^ $(CXXFLAGS) -o $@ 

tri3: $(tri3_SRC)
	$(CXX) $^ $(CXXFLAGS) -o $@ 

%.o: %.cpp shader.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAMS) *.o
#g++ hello_triangle.cpp glad.c -ldl -lglfw
