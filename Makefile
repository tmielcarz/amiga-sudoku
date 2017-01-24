CXX = /Users/tmielcarz/Applications/m68k-amigaos/bin/m68k-amigaos-g++
CXXFLAGS = -Os -Wall -fomit-frame-pointer

OBJ = output/main.o output/board.o output/application.o output/board_block.o output/board_cell.o output/board_hint_switch.o output/board_guess_switch.o output/board_abstract_switch.o output/puzzle.o output/timer.o output/board_line.o
BIN = output/sudoku

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

clean: clean-custom
	$(RM) $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) -s -noixemul -m68020

output/main.o: main.cpp
	$(CXX) -c main.cpp -o output/main.o $(CXXFLAGS)

output/board.o: board.cpp
	$(CXX) -c board.cpp -o output/board.o $(CXXFLAGS)

output/application.o: application.cpp
	$(CXX) -c application.cpp -o output/application.o $(CXXFLAGS)

output/board_block.o: board_block.cpp
	$(CXX) -c board_block.cpp -o output/board_block.o $(CXXFLAGS)

output/board_cell.o: board_cell.cpp
	$(CXX) -c board_cell.cpp -o output/board_cell.o $(CXXFLAGS)

output/board_hint_switch.o: board_hint_switch.cpp
	$(CXX) -c board_hint_switch.cpp -o output/board_hint_switch.o $(CXXFLAGS)

output/board_guess_switch.o: board_guess_switch.cpp
	$(CXX) -c board_guess_switch.cpp -o output/board_guess_switch.o $(CXXFLAGS)

output/board_abstract_switch.o: board_abstract_switch.cpp
	$(CXX) -c board_abstract_switch.cpp -o output/board_abstract_switch.o $(CXXFLAGS)

output/puzzle.o: puzzle.cpp
	$(CXX) -c puzzle.cpp -o output/puzzle.o $(CXXFLAGS)

output/timer.o: timer.cpp
	$(CXX) -c timer.cpp -o output/timer.o $(CXXFLAGS)

output/board_line.o: board_line.cpp
	$(CXX) -c board_line.cpp -o output/board_line.o $(CXXFLAGS)

