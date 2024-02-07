TARGET = PROJECT
CXX = g++
CXXFLAGS = -Wall -std=c++14 -g

SRCS = main.cpp graph.cpp input.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf *.o $(TARGET)
