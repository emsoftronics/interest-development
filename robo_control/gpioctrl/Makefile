
CC := gcc
#CC := /media/jagdish/JP1/embeddedRnd/buildroot/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc

SRC := gpioctrl.c testgpio.c
INC := -I./
LIB :=
LDLIB :=
BIN := testgpio

all:
	$(CC) $(SRC) $(INC) $(LIB) $(LDLIB) -o $(BIN)

clean:
	@rm -rf $(BIN)

