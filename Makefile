TARGET=test
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:%.cpp=%.o)
FLAGS =-g
FLAGS += --std=c++11
FLAGS += -Wall -Wextra -Werror -Wfatal-errors
CXXLIBS=-lglut -lGLU -lGL -lglfw

all: $(OBJS)
	$(CXX) $(FLAGS) -o $(TARGET) $(OBJS) $(CXXLIBS)

.cpp.o:
	$(CXX) $(FLAGS) -c -o $*.o $<

clean:
	$(RM) $(TARGET) *.o *~ core*

