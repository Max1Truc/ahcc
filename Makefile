all: ahcc

ahcc:
	g++ src/main.cpp src/libahcc.cpp -o bin/ahcc -Iinclude

clean:
	rm bin/ahcc
