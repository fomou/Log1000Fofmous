CC=gcc
exec=newton
LDFLAG=-lm
# default command, builds an executable called "newton".
# executable can be called with ./newton 49 4
all: $(exec)

# link the object files into the executable.
# the -lm option is to tell the linker to include math libraries.
$(exec): main.o newton.o comparison.o
	$(CC) -o $@ $^ $(LDFLAG)

# compile the main.c file into the main.o object file.
main.o: main.c newton.h comparison.h
	$(CC) -o $@ -c $<

# compile the newton.c file into the newton.o object file.
newton.o: newton.c newton.h
	$(CC) -o $@ -c $<
#compile the comparaison.c file into comparaison.o
comparaison.o: comparison.c comparison.h
	$(CC) -o $@ -c $<
# remove the executable and intermediary object files.
clean:
	rm -rf $(exec) *.o
# install
install:
	mkdir "install"
	make
	cp -f "newton" "install/newton"


