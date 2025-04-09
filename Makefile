CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g

TARGET   := Assignment9.exe
OBJS     := main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean