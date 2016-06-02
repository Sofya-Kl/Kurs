.PHONY: clean prepare cformat 

bin/cformat: prepare obj/main.o obj/cformat.o
	gcc -Wall obj/main.o obj/cformat.o -o bin/cformat 

obj/main.o: prepare src/main.c
	gcc -Wall -c src/main.c -o obj/main.o 
	
obj/cformat.o: prepare src/cformat.c
	gcc -Wall -c src/cformat.c -o obj/cformat.o 

prepare: bin obj

cformat: bin/cformat
	bin/cformat

bin:
	mkdir bin

obj:
	mkdir obj

clean:
	rm -f bin/*
	rm -f obj/*