all:main

main: src/Main.c
	gcc src/*.c -o Executable/Main -lm
	./Executable/Main
