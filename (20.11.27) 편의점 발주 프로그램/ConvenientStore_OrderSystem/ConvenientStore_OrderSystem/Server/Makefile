server : RootHeader.o socket.o Client.o OrderSystem.o main.o
	gcc -o server RootHeader.o socket.o Client.o OrderSystem.o main.o

RootHeader.o : header/RootHeader.c
	gcc -c -o RootHeader.o header/RootHeader.c

socket.o : header/socket.c
	gcc -c -o socket.o header/socket.c

Client.o : header/Client.c
	gcc -c -o Client.o header/Client.c

OrderSystem.o : header/OrderSystem.c
	gcc -c -o OrderSystem.o header/OrderSystem.c

main.o : main.c
	gcc -c -o main.o main.c

clean:
	rm *.o 
