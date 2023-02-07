server: server.o str_handling.o users_input.o DB.o
	gcc -pthread -g server.o str_handling.o users_input.o DB.o -o server

client: client.o str_handling.o users_input.o DB.o
	gcc -g client.o str_handling.o users_input.o DB.o -o client

local: local.o str_handling.o users_input.o DB.o
	gcc -g local.o str_handling.o users_input.o DB.o -o local

client.o: client.c
	gcc -Wall -g -c client.c

server.o: server.c
	gcc -Wall -g -c server.c

local.o: local.c
	gcc -Wall -g -c local.c

str_handling.o: str_handling.c
	gcc -Wall -g -c str_handling.c

users_input.o: users_input.c
	gcc -Wall -g -c users_input.c

DB.o: DB.c
	gcc -Wall -g -c DB.c

clean:
	rm -f *.o local server client

run_local:
	./local DB.csv

run_server:
	./server DB.csv 127.0.0.1 12345

run_client:
	./client 127.0.0.1 12345

debug_local:
	gdb --args ./local DB.csv

debug_server:
	gdb --args ./server DB.csv 127.0.0.1 12345

debug_client:
	gdb --args ./client 127.0.0.1 12345