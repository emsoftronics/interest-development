
#CC := gcc
CC := /media/jagdish/JP1/embeddedRnd/buildroot/output/host/bin/arm-buildroot-linux-uclibcgnueabihf-gcc

SRC := pwmctrl/pwmctrl.c gpioctrl/gpioctrl.c roboctrl.c robo-main.c
INC := -I./ -I./gpioctrl/ -I./pwmctrl/
LIB :=
LDLIB := -lpthread
BIN := robo-demo

all:
	$(CC) $(SRC) $(INC) $(LIB) $(LDLIB) -o $(BIN)

clean:
	@rm -rf $(BIN)

