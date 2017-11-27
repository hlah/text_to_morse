
OUTPUT="morse.run"
SRC="abp-morse.c"
SRC+="ABP/abp.c"
CC=gcc

all:
	$(CC) $(SRC) -o  $(OUTPUT)

clean:
	rm -f $(OUTPUT)
