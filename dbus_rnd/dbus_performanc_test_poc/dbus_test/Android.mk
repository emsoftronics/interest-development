LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= dbusPocServer
LOCAL_STRIP_MODULE := false
LOCAL_SRC_FILES := \
        DBusPocServer.cpp    \
        DBusService.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) 

LOCAL_CFLAGS := -Wall -Wno-missing-field-initializers -Wno-unused-variable -Wno-unused-parameter -lpthread
#-D__REV__=\"$(GIT_VERSION)-$(GIT_BUILD)\"
#LOCAL_CFLAGS += $(MY_C_DEFINES)
LOCAL_CFLAGS += -DLOG_TAG=\"dbusPocServer\"

LOCAL_SHARED_LIBRARIES := libdbus libcutils 

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_MODULE:= dbusPocClient
LOCAL_STRIP_MODULE := false
LOCAL_SRC_FILES := \
        DBusPocClient.cpp \
        DBusService.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) 

LOCAL_CFLAGS := -Wall -Wno-missing-field-initializers -Wno-unused-variable -Wno-unused-parameter -lpthread
#-D__REV__=\"$(GIT_VERSION)-$(GIT_BUILD)\"
#LOCAL_CFLAGS += $(MY_C_DEFINES)
LOCAL_CFLAGS += -DLOG_TAG=\"dbusPocClient\"

LOCAL_SHARED_LIBRARIES := libdbus libcutils 

include $(BUILD_EXECUTABLE)
