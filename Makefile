
OUTPUT="morse.run"
SRC="abp-morse.c"
SRC+="ABP/abp.c"
SRC+="ABP/avl.c"
CC=gcc

all:
	$(CC) $(SRC) -o  $(OUTPUT)

clean:
	rm -f $(OUTPUT)
