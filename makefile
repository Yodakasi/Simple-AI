OBJS = src/main.cpp src/car.cpp src/map.cpp src/collider.cpp src/network.cpp src/neuron.cpp src/settings.cpp src/handlegeneration.cpp
CC = g++
COMPILER_FLAGS = -Wall -Wextra
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJ_NAME = bin/gierka

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
