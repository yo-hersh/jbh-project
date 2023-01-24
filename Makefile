build: main.o str_handling.o users_input.o DB.o
	gcc -g main.o str_handling.o users_input.o DB.o -o main

main.o: main.c
	gcc -Wall -g -c main.c

str_handling.o: str_handling.c
	gcc -Wall -g -c str_handling.c

users_input.o: users_input.c
	gcc -Wall -g -c users_input.c

DB.o: DB.c
	gcc -Wall -g -c DB.c

clean:
	rm -f *.o main

run:
	./main DB.csv

debug:
	gdb --args ./main DB.csv