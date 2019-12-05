Dijkstra.exe: Dijkstra.o dxta.o heap.o hash.o
	g++ -o Dijkstra.exe Dijkstra.o dxta.o heap.o hash.o

Dijkstra.o: Dijkstra.cpp
	g++ -c Dijkstra.cpp

dxta.o: dxta.cpp dxta.h
	g++ -c dxta.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o DijkstraDebug.exe Dijkstra.cpp dxta.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
