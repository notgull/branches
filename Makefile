branches: branch.o header.o main.o err.o
	gcc -std=c99 branch.o header.o main.o err.o -o branches

branch.o: branch.h err.h branch.c
	gcc -std=c99 -c branch.c

header.o: header.h header.c
	gcc -std=c99 -c header.c

err.o: err.h err.c
	gcc -std=c99 -c err.c

main.o: main.h header.h branch.h err.h main.c
	gcc -std=c99 -c main.c
