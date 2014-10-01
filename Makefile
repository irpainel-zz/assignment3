CC = g++
CFLAGS = -g -Wall -Wextra -pedantic 
IPATH = -I/usr/X11/include -I/usr/pkg/include -I./include
LPATH = -L/usr/X11/lib -L/usr/pkg/lib
LDPATH = -Wl,-R/usr/pkg/lib
LIBS=-lGL -lglut -lGLU -ljpeg -lpng16 -lm -lGLEW 

BUILD = ./build/
SRC = ./src/

all: $(BUILD)Ass3

$(BUILD)Ass3: $(BUILD)main.o $(BUILD)G308_Geometry.o $(BUILD)Display.o $(BUILD)textfile.o $(BUILD)G308_ImageLoader.o $(BUILD)Arcball.o $(BUILD)Material.o $(BUILD)Skybox.o
	$(CC) -o $@ $^ $(LIBS) $(LPATH) $(LDPATH)
	
$(BUILD)%.o: $(SRC)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^ $(IPATH)

clean:
	$(RM) -f $(BUILD)*.o $(BUILD)*.gch $(BUILD)Ass3


