branches: branch.o header.o main.o err.o initialtree.o shortcuts.o
	gcc -std=c99 branch.o header.o main.o err.o initialtree.o shortcuts.o -o branches

branch.o: branch.h err.h shortcuts.h branch.c
	gcc -std=c99 -c branch.c

header.o: header.h header.c
	gcc -std=c99 -c header.c

err.o: err.h err.c
	gcc -std=c99 -c err.c

shortcuts.o: shortcuts.h shortcuts.c
	gcc -std=c99 -c shortcuts.c

initialtree.o: initialtree.h initialtree.c
	gcc -std=c99 -c initialtree.c

main.o: main.h header.h branch.h shortcuts.h err.h main.c
	gcc -std=c99 -c main.c
