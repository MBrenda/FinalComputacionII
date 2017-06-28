cliente: cliente.o funciones.o
	mkdir -p bin
	mkdir -p obj
	gcc -o bin/cliente cliente.o funciones.o
	mv cliente.o obj/
	mv funciones.o obj/

cliente.o: src/cliente.c src/funciones.c
	gcc -c src/cliente.c src/funciones.c -Iinclude

clean:
	rm -r bin/ obj/

install:
	sudo cp bin/cliente /bin

uninstall:
	sudo rm /bin/cliente



