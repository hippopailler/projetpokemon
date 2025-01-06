CC = g++
CFLAGS = -Wall -Werror

SOURCES = deck.cpp hand.cpp player.cpp game.cpp energy.cpp move.cpp pokemon.cpp main.cpp
OBJS = $(SOURCES:.cpp=.o) 

EXECUTABLE = main.x

.PHONY: all clean realclean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.cpp 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

realclean: clean
	rm -f $(EXECUTABLE)