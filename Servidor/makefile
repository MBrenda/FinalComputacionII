servidor: servidor.o funciones.o
	mkdir -p bin
	mkdir -p obj
	mkdir -p db
	touch db/tickets.txt
	gcc -o bin/servidor servidor.o funciones.o
	mv servidor.o obj/
	mv funciones.o obj/

servidor.o: src/servidor.c src/funciones.c
	gcc -c src/servidor.c src/funciones.c -Iinclude

clean:
	rm -r bin/ obj/

install:
	sudo cp bin/servidor /bin

uninstall:
	sudo rm /bin/servidor



