CPPFLAGS = -ansi -Wall

proj3: proj3.o Matrix.o Graph.o Edge.o Vertex.o
	g++ proj3.o Matrix.o Graph.o Edge.o Vertex.o -o proj3

proj3.o: proj3.cpp
	g++ $(CPPFLAGS) -g -c proj3.cpp -o proj3.o

Matrix.o: Matrix.cpp Matrix.h
	g++ $(CPPFLAGS) -g -c Matrix.cpp -o Matrix.o

Graph.o: Graph.cpp Graph.h
	g++ $(CPPFLAGS) -g -c Graph.cpp -o Graph.o

Edge.o: Edge.cpp Edge.h
	g++ $(CPPFLAGS) -g -c Edge.cpp -o Edge.o

Vertex.o: Vertex.cpp Vertex.h
	g++ $(CPPFLAGS) -g -c Vertex.cpp -o Vertex.o

.PHONY: clean

clean:
	rm -rf proj3.o Matrix.o Graph.o Edge.o Vertex.o proj3

