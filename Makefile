# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica1

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default :install  $(TARGETS) run

# regla de ejecucion
#
$(TARGETS) : user_code.o practica1.o file_ply_stl.o lampara.o
	$(CC) -o $@ $(CXXFLAGS) user_code.o practica1.o file_ply_stl.o lampara.o $(LDFLAGS)
#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#

# install
install:
	sudo apt-get install freeglut3 freeglut3-dev

#run executing the lamp
run:
	./practica1
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *

