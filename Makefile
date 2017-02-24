CXX = /Users/tmielcarz/Applications/m68k-amigaos/bin/m68k-amigaos-g++
CXXFLAGS = -Os -Wall -fomit-frame-pointer

OBJ = output/main.o output/board.o output/application.o output/board_block.o output/board_cell.o \
    output/board_hint_switch.o output/board_guess_switch.o output/board_abstract_switch.o \
    output/puzzle.o output/timer.o output/board_line.o output/title_screen.o output/abstract_screen.o \
    output/event.o output/event_listener.o output/event_bus.o output/puzzle_select_screen.o output/puzzle_select_event.o

BIN = output/sudoku

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

clean: clean-custom
	$(RM) $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) -s -noixemul -m68020

output/main.o: src/main.cpp
	$(CXX) -c src/main.cpp -o output/main.o $(CXXFLAGS)

output/board.o: src/board/board.cpp
	$(CXX) -c src/board/board.cpp -o output/board.o $(CXXFLAGS)

output/application.o: src/application.cpp
	$(CXX) -c src/application.cpp -o output/application.o $(CXXFLAGS)

output/board_block.o: src/board/board_block.cpp
	$(CXX) -c src/board/board_block.cpp -o output/board_block.o $(CXXFLAGS)

output/board_cell.o: src/board/board_cell.cpp
	$(CXX) -c src/board/board_cell.cpp -o output/board_cell.o $(CXXFLAGS)

output/board_hint_switch.o: src/board/board_hint_switch.cpp
	$(CXX) -c src/board/board_hint_switch.cpp -o output/board_hint_switch.o $(CXXFLAGS)

output/board_guess_switch.o: src/board/board_guess_switch.cpp
	$(CXX) -c src/board/board_guess_switch.cpp -o output/board_guess_switch.o $(CXXFLAGS)

output/board_abstract_switch.o: src/board/board_abstract_switch.cpp
	$(CXX) -c src/board/board_abstract_switch.cpp -o output/board_abstract_switch.o $(CXXFLAGS)

output/puzzle.o: src/puzzle.cpp
	$(CXX) -c src/puzzle.cpp -o output/puzzle.o $(CXXFLAGS)

output/timer.o: src/timer.cpp
	$(CXX) -c src/timer.cpp -o output/timer.o $(CXXFLAGS)

output/board_line.o: src/board/board_line.cpp
	$(CXX) -c src/board/board_line.cpp -o output/board_line.o $(CXXFLAGS)

output/title_screen.o: src/title/title_screen.cpp
	$(CXX) -c src/title/title_screen.cpp -o output/title_screen.o $(CXXFLAGS)

output/abstract_screen.o: src/abstract_screen.cpp
	$(CXX) -c src/abstract_screen.cpp -o output/abstract_screen.o $(CXXFLAGS)

output/event.o: src/eventbus/event.cpp
	$(CXX) -c src/eventbus/event.cpp -o output/event.o $(CXXFLAGS)

output/event_listener.o: src/eventbus/event_listener.cpp
	$(CXX) -c src/eventbus/event_listener.cpp -o output/event_listener.o $(CXXFLAGS)

output/event_bus.o: src/eventbus/event_bus.cpp
	$(CXX) -c src/eventbus/event_bus.cpp -o output/event_bus.o $(CXXFLAGS)

output/puzzle_select_screen.o: src/title/puzzle_select_screen.cpp
	$(CXX) -c src/title/puzzle_select_screen.cpp -o output/puzzle_select_screen.o $(CXXFLAGS)

output/puzzle_select_event.o: src/title/puzzle_select_event.cpp
	$(CXX) -c src/title/puzzle_select_event.cpp -o output/puzzle_select_event.o $(CXXFLAGS)
