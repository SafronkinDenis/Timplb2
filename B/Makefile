CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = route
SRCS = main.cpp modeBetaCipher.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp modeBetaCipher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
