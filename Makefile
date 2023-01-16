build: main.o str_handle.o user_manage.o DB.o
	gcc -g main.o str_handle.o user_manage.o DB.o -o main

main.o: main.c
	gcc -Wall -g -c main.c

str_handle.o: str_handle.c
	gcc -Wall -g -c str_handle.c

user_manage.o: user_manage.c
	gcc -Wall -g -c user_manage.c

DB.o: DB.c
	gcc -Wall -g -c DB.c

clean:
	rm -f *.o main

run:
	./main DB.csv

debug:
	gdb --args ./main DB.csv