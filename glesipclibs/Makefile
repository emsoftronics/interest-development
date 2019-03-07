  # the compiler: gcc for C program, define as g++ for C++
  #CC = gcc
  CC = /home/user/Jacinto_Linux/ToolChain/gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc

  SYSROOT = /home/user/Jacinto_Linux/targetfs

  INC = -I./

#  LDLIBS = -pthread -lilmClient -lwayland-server -lwayland-client -lwayland-cursor -lilmControl -lilmCommon
#  LDLIBS += -lEGL -lGLESv2 -lpvr_wlegl
 
#  LIBDIR = 

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  CFLAGS  = -Wall  --sysroot=$(SYSROOT) $(INC) 
  CFLAGS += -D DEFAULT_CLIENT_CONTEXT=libgles

  # the build target executable:


all: libGLESv1_CM_ipc.so libGLESv2_ipc.so libEGL_ipc.so

libGLESv1_CM_ipc.so: cutil.o vmcutil.o GLESv1_CM.o
	$(CC) -shared $(CFLAGS) -o $@ -pthread cutil.o vmcutil.o GLESv1_CM.o

libGLESv2_ipc.so: cutil.o vmcutil.o GLESv2.o
	$(CC) -shared $(CFLAGS) -o $@ -pthread cutil.o vmcutil.o GLESv2.o

libEGL_ipc.so: cutil.o vmcutil.o EGL.o
	$(CC) -shared $(CFLAGS) -o $@ -pthread cutil.o vmcutil.o EGL.o

%.o: %.c
	$(CC) -fPIC -c $(CFLAGS) $< -o $@

clean:
	@rm *.o

fclean:
	@rm *.o *.so


