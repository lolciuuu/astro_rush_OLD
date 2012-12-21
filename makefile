# Flagi kompilatora
CXX=g++
CFLAGS= -Wall -ansi -pedantic -g -std=c++0x -c -Wall -I ./include 

#Flagi linkera
LIBS = -lGL -lGLU -lSDL -lSDL_ttf -lSDL_image -lluabind -llua5.1 

# zrodla do skompilowania
SOURCES = src/main.cpp src/App.cpp src/Property.cpp src/Resource.cpp \
		  src/Game.cpp src/Writer.cpp src/Player.cpp src/Play.cpp \
		  src/Menu.cpp src/Renderer.cpp src/MenuItem.cpp src/Sprite.cpp \
		  src/Highscore.cpp src/SpriteManager.cpp src/MapManager.cpp \
		  src/Map.cpp src/LiveBar.cpp src/SoundManager.cpp src/Splash.cpp \
		  src/RendererGL.cpp src/Logger.cpp

# nazwy skompilowanych plikow cpp
OBJECTS=$(SOURCES:.cpp=.o)

# nazwa pliku wynikowego
EXECUTABLE = AstroRush

#
all: $(SOURCES) $(EXECUTABLE)
	 @echo "\n ---- Udało się ---- "

# linkowanie aplikacji w plik wykonywalny	
$(EXECUTABLE): $(OBJECTS) 
	 @echo "\n ---- Linkowanie ---- "
	$(CC)  $(OBJECTS)  -o $(EXECUTABLE) $(LIBS)

# kompilowanie plikow cpp
.cpp.o:
	 @echo "Kompilowanie pliku: $<"
	 @$(CXX) $(CFLAGS) $< -o $@ 

# czyszczenei 
clean:
	rm -rf ./src/*.o
	rm ./AstroRush
	@echo "Wyczyszczono"
	
	


   