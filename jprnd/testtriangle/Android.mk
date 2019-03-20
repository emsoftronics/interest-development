
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := atdemo
LOCAL_MODULE_TAGS := optional
LOCAL_VENDOR_MODULE := true
#LOCAL_CFLAGS := 
LOCAL_CLANG := true
LOCAL_SRC_FILES := \
	tdemo.c \
	triangle.c \

LOCAL_SHARED_LIBRARIES := libEGL_ipc libGLESv2_ipc
include $(BUILD_EXECUTABLE)
