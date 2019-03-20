  # the compiler: gcc for C program, define as g++ for C++
  SRC = tdemo.c triangle.c

  #CC = gcc
  CC = /home/user/Jacinto_Linux/ToolChain/gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc

  SYSROOT = /home/user/Jacinto_Linux/targetfs

  INC = -I./
#  -I/home/user/Jacinto_Linux/ivi_dev/ozone-wayland/wayland/protocol -I./wlpf

#  LDLIBS = -pthread -lilmClient -lwayland-client -lwayland-cursor -lilmControl -lilmCommon
  LDLIBS = -lEGL_ipc -lGLESv2_ipc -L /home/user/Jacinto_Linux/glesipclibs
#-lwayland-server
#-lwayland-egl
#-ldl
 
#-lEGL -lIMGegl -ldrm_omap -ldrm -lGLESv2 -lsrv_um -lpvr_wlegl -lwayland-cursor -lwayland-client -lffi
#-lrt -lm -lpthread -lc


  LIBDIR = 

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  CFLAGS  = -Wall  --sysroot=$(SYSROOT) $(INC) $(LDLIBS) $(LIBDIR)
  CFLAGS += -D EXTERNAL_EGL_PROFILE     -D DEFAULT_FCALL_SERVER=libgles -D ENABLE_EGL

  # the build target executable:
  TARGET = tdemo

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	$(RM) $(TARGET)

