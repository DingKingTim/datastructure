CC = g++
CXXFLAGS = --std=c++11
CPPFLAGS=-I ./
TARGET=double_list


OBJ_DIR=obj
BIN_DIR=bin

SRC = $(wildcard *.cc)
OBJ =$(subst .cc,.o,$(SRC))

$(TARGET): build $(OBJ)
	$(CC) ${OBJ} -o $(BIN_DIR)/$@

build:
	mkdir -p $(BIN_DIR)

$(OBJ): %.o:%.cc
	$(CC) $(CXXFLAGS) -c $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f *.o
	rm -rf $(BIN_DIR)
