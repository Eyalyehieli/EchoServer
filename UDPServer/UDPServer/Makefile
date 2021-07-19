UDPServer: main.c die.h myServer.c
	gcc -Wall -g -c main.c -o  obj/Debug/main.o
	gcc -Wall -g -c -O myServer.c -o obj/Debug/myServer.o
	gcc -o bin/Debug/UDPServer obj/Debug/main.o obj/Debug/myServer.o
clean:
	rm bin/Debug/*
	rm obj/Debug/*
