default: compile

compile: encryption

encryption: ciphers.o encryption.c
	gcc ciphers.o encryption.c -o encryption.exe

ciphers.o: ciphers.c ciphers.h
	gcc -c ciphers.c -o ciphers.o

clean:
	rm encryption ciphers.o
