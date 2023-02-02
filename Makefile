server: server.o str_handling.o users_input.o DB.o
	gcc -pthread -g server.o str_handling.o users_input.o DB.o -o server

client: client.o str_handling.o users_input.o DB.o
	gcc -g client.o str_handling.o users_input.o DB.o -o client

local: main.o str_handling.o users_input.o DB.o
	gcc -g main.o str_handling.o users_input.o DB.o -o main

client.o: client.c
	gcc -Wall -g -c client.c

server.o: server.c
	gcc -Wall -g -c server.c

main.o: main.c
	gcc -Wall -g -c main.c

str_handling.o: str_handling.c
	gcc -Wall -g -c str_handling.c

users_input.o: users_input.c
	gcc -Wall -g -c users_input.c

DB.o: DB.c
	gcc -Wall -g -c DB.c

clean:
	rm -f *.o main server client

run_local:
	./main DB.csv

run_server:
	./server DB.csv 127.0.0.1 12345

run_client:
	./client 127.0.0.1 12345

debug_local:
	gdb --args ./main DB.csv

debug_server:
	gdb --args ./server DB.csv 127.0.0.1 12345

debug_client:
	gdb --args ./client 127.0.0.1 12345