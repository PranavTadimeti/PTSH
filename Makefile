FLAGS = -g -Wall 

ptsh: main.o cd.o prompt.o utils.o ls.o pinfo.o exec.o history.o nwatch.o
	gcc $(FLAGS) main.o cd.o prompt.o utils.o ls.o pinfo.o exec.o history.o nwatch.o

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

pinfo.o: pinfo.c pinfo.h
	gcc $(FLAGS) -c pinfo.c

exec.o: exec.c exec.h
	gcc $(FLAGS) -c exec.c

history.o: history.c history.h
	gcc $(FLAGS) -c history.c

nwatch.o: nwatch.c nwatch.h
	gcc $(FLAGS) -c nwatch.c
