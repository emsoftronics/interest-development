

DEPLIBS  := 

LDLIBS  :=  -pthread

CC		:= gcc
CFLAGS  :=  -Wall 

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(dir $(mkfile_path))
#NAME    :=  $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
BINPATH := $(current_dir)../bin
# $(shell echo $(current_dir) | rev | cut -d'/' -f1 | rev )
PRODUCER :=  producer
ROUTER :=  router
CONSUMER :=  consumer
SRC		:=	singlyLinkedList/linklist.c cutil/cutil.c common/common.c
#-ansi -pedantic -Wall -Werror -W -g3
INC		:=  -I$(current_dir)/../ -I. -I./common  -I./cutil  -I./singlyLinkedList

CFLAGS += $(INC)

.PHONY: all clean fclean rebuild

all: producer consumer router 

producer :  $(BINPATH) 
	$(CC) $(SRC) $(PRODUCER).c $(LDLIBS) $(DEPLIBS) $(CFLAGS) -o $(BINPATH)/$(PRODUCER)

consumer:  $(BINPATH)
	$(CC) $(SRC) $(CONSUMER).c $(LDLIBS) $(DEPLIBS) $(CFLAGS) -o $(BINPATH)/$(CONSUMER)

router:  $(BINPATH)
	$(CC) $(SRC) $(ROUTER).c $(LDLIBS) $(DEPLIBS) $(CFLAGS) -o $(BINPATH)/$(ROUTER)

$(BINPATH) : 
	@mkdir -p $@



clean:
	@rm -r $(BINPATH)

print:
	@echo "SRC : $(SRC)"
	
rebuild: clean all

