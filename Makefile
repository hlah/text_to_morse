CC=gcc

OUTPUT="morse.run"

SRC=abp-morse.c
SRC_OBJ= $(SRC:.c=.o)

#LIB_OBJ = $(patsubst $(SRC), obj/$(SRC).o, $(SRC))

LIB_DIR= "ABP"

#LIB_OBJ = $(patsubst ABP/%.c, obj/%.o, $(LIB_SRC))

LIB_SRC= ABP/abp.c
LIB_SRC+= ABP/avl.c
LIB_OBJ = $(LIB_SRC:.c=.o)
#LIB_OBJ = $(patsubst %.o, %.c, $(LIB_SRC))
ODIR= "ABP"

all: libABP abp-morse.o
	$(CC) $(SRC_OBJ) libABP.a -o  $(OUTPUT)
	rm -rf build
	mkdir build
	mv *.run *.a *.o ABP/*.o build/ 

abp_morse.o:
	$(CC) -Wall -c $(SRC)

#$(ODIR)/%.o: $(ODIR)/%.c
%.o: %.c
	$(CC) -Wall -c $< -o $@

libABP: $(LIB_OBJ)
	ar -cvq libABP.a $(LIB_OBJ)

clean:
	rm -rf build


