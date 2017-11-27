CXXFLAGS += -O3 -w
LDFLAGS += -lrt

CC = g++

all: GenerateNetwork GenerateCascades

GenerateNetwork: Snap.o
	$(CC) -o GenerateNetwork GenerateNetwork.cpp Snap.o -I./glib -I./snap -O3

GenerateCascades: Snap.o
	$(CC) -o GenerateCascades GenerateCascades.cpp SimpleRNG.cpp Graph.cpp Simulation.cpp Snap.o -I./glib -I./snap -O3

Snap.o:
	$(CC) -c $(CXXFLAGS) ./snap/Snap.cpp -I./GLib

clean:
	rm *.o GenerateNetwork GenerateCascades
