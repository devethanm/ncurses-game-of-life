CC=gcc
FILES=main.c gameLogic.c cell.c 
#FILES2 = main.h 
OUT_EXE = main.o
all: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES) -lmenu -lncurses
clean:
	rm -f *.o $(OUT_EXE)
run:
	./main.o
