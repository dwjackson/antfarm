EXE_NAME = antfarm
SRC_FILES = antfarm.cpp grids.cpp ants.cpp drawing.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
HDR_FILES = grids.hpp ants.hpp drawing.hpp
CXX = clang++
CFLAGS = -g -Wall -Wextra

$(EXE_NAME): $(OBJ_FILES)
	$(CXX) $(CFLAGS) -o $(EXE_NAME) $(OBJ_FILES) -lraylib

$(OBJ_FILES): $(SRC_FILES) $(HDR_FILES)
	$(CXX) $(CFLAGS) -c $(SRC_FILES)

clean:
	rm -f *.o
	rm -f $(EXE_NAME)

.PHONY: all clean
