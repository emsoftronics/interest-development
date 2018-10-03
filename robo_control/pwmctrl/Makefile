
CC := gcc
#CC := /media/jagdish/JP1/embeddedRnd/buildroot/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc

SRC := pwmctrl.c testpwm.c
INC := -I./
LIB :=
LDLIB :=
BIN := testpwm

all:
	$(CC) $(SRC) $(INC) $(LIB) $(LDLIB) -o $(BIN)

clean:
	@rm -rf $(BIN)

