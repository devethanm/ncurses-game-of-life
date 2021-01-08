CC=gcc
FILES=main.c
FILES2 = main.h
OUT_EXE = Hello.o
all: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES) -lncurses
clean:
	rm -f *.o $(OUT_EXE)
run:
	./Hello.o
tar:
	tar -cv $(FILES) $(FILES2) README.txt > Damian-Armijo-HW1.tar