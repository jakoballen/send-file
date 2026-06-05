CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++11

SRC = src/main.cpp \
      src/network.cpp \
      src/file_io.cpp \
      src/crypto.cpp \
      src/util.cpp

TARGET = sendfile

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)