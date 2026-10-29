CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = gronsfeld
SRCS = main.cpp modAlphaCipher.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
