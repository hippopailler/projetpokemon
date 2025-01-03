# Compilateur et options
CC = g++
CFLAGS = -std=c++17 -Icode -Wall -Werror
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Répertoires
SRCDIR = code
OBJDIR = obj
BINDIR = build
ASSETS = assets

# Fichiers
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
EXECUTABLE = $(BINDIR)/pokemon_game

# Règles
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Supprimer tout
realclean: clean
	rm -rf $(ASSETS)
