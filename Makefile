CC=gcc

OUTPUT="morse.run"

SRC=abp-morse.c
SRC_OBJ= $(SRC:.c=.o)

LIB_SRC= ABP/abp.c
LIB_SRC+= ABP/avl.c
LIB_OBJ = $(LIB_SRC:.c=.o)

all: libABP abp-morse.o
	$(CC) $(SRC_OBJ) libABP.a -o  $(OUTPUT)
	rm -rf build
	mkdir build
	mv *.run *.a *.o ABP/*.o build/ 

abp_morse.o:
	$(CC) -Wall -c $(SRC)

%.o: %.c
	$(CC) -Wall -c $< -o $@

libABP: $(LIB_OBJ)
	ar -cvq libABP.a $(LIB_OBJ)

clean:
	rm -rf build


