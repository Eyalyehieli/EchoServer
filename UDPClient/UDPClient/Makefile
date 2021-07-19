UDPClient: main.c die.h myClient.c
	gcc -Wall -g -c main.c -o obj/Debug/main.o
	gcc -Wall -Wno-unused-result -g -c -O myClient.c -o obj/Debug/myClient.o
	gcc -o bin/Debug/UDPClient obj/Debug/main.o obj/Debug/myClient.o
clean:
	rm bin/Debug/*
	rm obj/Debug/*
