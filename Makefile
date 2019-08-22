FLAGS = -g -Wall 

ptsh: main.o cd.o prompt.o utils.o ls.o
	gcc $(FLAGS) main.o cd.o prompt.o utils.o ls.o

clean: 
	rm *.o a.out

main.o: main.c 
	gcc $(FLAGS) -c main.c

prompt.o: prompt.c prompt.h
	gcc $(FLAGS) -c prompt.c

cd.o: cd.c cd.h
	gcc $(FLAGS) -c cd.c

utils.o: utils.c utils.h
	gcc $(FLAGS) -c utils.c

ls.o: ls.c ls.h
	gcc $(FLAGS) -c ls.c
