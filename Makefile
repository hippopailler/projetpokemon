# Compilateur et options
CC = g++
CFLAGS = -std=c++20 -Isrc -Icode -Wall -Werror
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Répertoires
GRAPHICDIR = code
LOGICDIR = src
OBJDIR = obj
BINDIR = build
ASSETS = assets

# Fichiers
GRAPHIC_SOURCES = $(wildcard $(GRAPHICDIR)/*.cpp)
LOGIC_SOURCES = $(wildcard $(LOGICDIR)/*.cpp)
SOURCES = $(GRAPHIC_SOURCES) $(LOGIC_SOURCES)
OBJECTS = $(patsubst $(GRAPHICDIR)/%.cpp, $(OBJDIR)/graphic_%.o, $(GRAPHIC_SOURCES)) \
          $(patsubst $(LOGICDIR)/%.cpp, $(OBJDIR)/logic_%.o, $(LOGIC_SOURCES))
EXECUTABLE = $(BINDIR)/pokemon_game

# Règles
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/graphic_%.o: $(GRAPHICDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/logic_%.o: $(LOGICDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

realclean: clean
	rm -rf $(ASSETS)
